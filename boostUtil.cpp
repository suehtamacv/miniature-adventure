/*
 * Copyright 2009-2013 Yi-Qing WANG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * @file boostUtil.cpp
 * @brief main training routines for the Viola-Jones algorithm
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <Eigen/Dense>
#include "TrainExamples.h"
#include "boostUtil.h"
#include "commonUtil.h"

#define POSITIVE 0		//some convention
#define NEGATIVE 1		//some convention
#define TWEAK_UNIT 1e-2  	//initial tweak unit
#define MIN_TWEAK 1e-5   	//tweak unit cannot go lower than this
#define GOAL 1e-7		//overall false positive target

using namespace std;
using namespace Eigen;

//given a training target, this function trains a cascade classifier
void train( trainParams const & target ){

	times("");

	//record stump count of each layer
	vector<int> layerMemory;

	//target rates which set the stop condition of boosting
	const float detectionRateTarget = target.layerTargetDetectionRate;
	const float falsePositiveTarget = target.layerTargetFalsePositiveRate;
	double accumulatedFalsePositive = 1;

	//estimate the number of rounds adaboost should go
	//+20 merely sets an upper bound of boosting rounds
	int nBoostingRounds = ceil(log(target.overallTargetFalsePositiveRate)/log(falsePositiveTarget)) + 20;
	cout << "\nINFO: " << nBoostingRounds << " rounds of boosting are expected!\n";

	//assign memory for tweaks and rules
	vector<stumpRule> * cascade = new vector<stumpRule> [nBoostingRounds];
	VectorXf tweaks;
	tweaks.setZero(nBoostingRounds);

	//make use of the remaining hard negative examples from previous rounds to reduce sampling load
	VectorXi * trainingBlackList = NULL;
	VectorXi * testBlackList = NULL;

	//start cascade training
	for(int round = 0; round < nBoostingRounds && accumulatedFalsePositive > GOAL; round++){

		//start afresh
		TrainExamples testSet(
			target.positiveTestExamples
		,	target.positiveTotalWeight	//positiveTotalWeight
		,	target.negativeTestExamples	//to be complemented with additional examples from negative images
		,	"validNoFaces"			//negative images with no human faces
		,	1e3				//numberNegatives for validation
		,	cascade				//cascade to get good negative examples
		,	tweaks				//tweaks
		,	round				//layerCount in the cascade
		,	testBlackList			//blackList: eliminate easy negatives and hard positives
		,	""    				//toFile
		,	false				//inTrain
		,	target.allInMemory		//allInMemory
		);
		//at the first round of training, negative examples are easy to come by
		//hence 2e4 is set to make the algorithm absorb as many negative patterns as possible
		//given the amount of memory in the machine I have access to
		TrainExamples trainSet(
			target.positiveExamples
		,	target.positiveTotalWeight	//positiveTotalWeight
		,	target.negativeExamples		//to be complemented with additional examples from negative images
		,	"noFaces"			//negative images with no human faces
		,	round == 0 ? 2e4 : 1e3		//numberNegatives for training
		,	cascade				//cascade to get good negative examples
		,	tweaks				//tweaks
		,	round				//layerCount in the cascade
		,	trainingBlackList		//blackList: eliminate easy negatives and hard positives
		,	target.toFile    		//toFile
		,	true				//inTrain
		,	target.allInMemory		//allInMemory
		);

		//print out some statistics
		cout << "\n####################################################################################################\n";
		cout << "\nLAYER " << round + 1 << ":\n\n";
		cout << "\t" << trainSet.nPositives << " positives and " << trainSet.nNegatives << " negatives remain.\n";


		//inner loop for adaboosting
		int committeeSizeGuide = min(20 + round * 10, 200);
		bool layerMissionAccomplished = false;
		while(!layerMissionAccomplished){

			trainSet.adaboost();
			cascade[round] = trainSet.committee;
			bool overSized = (int)cascade[round].size() > committeeSizeGuide ? true : false;
			bool finalTweak = overSized;

			//some parameters for tweaking exception handling
			int tweakCounter = 0;
			Vector2i oscillationObserver;
			//tweak to make do
			float tweak = 0;
			//if finalTweak, then try everything
			if(finalTweak)
				tweak = -1;
			float tweakUnit = TWEAK_UNIT;
			float ctrlFalsePositive, ctrlDetectionRate, falsePositive, detectionRate;

			while(abs(tweak) < 1.1){
				tweaks[round] = tweak;

				//tweak value depends on the worst detectionRate and falsePositive
				trainSet.calcEmpiricalError(cascade, tweaks, round + 1, falsePositive, detectionRate, false);
		 		testSet.calcEmpiricalError(cascade, tweaks, round + 1, ctrlFalsePositive, ctrlDetectionRate, false);
				float worstFalsePositive = max(falsePositive, ctrlFalsePositive);
				float worstDetectionRate = min(detectionRate, ctrlDetectionRate);

				//make sure that tweaking always leads to a good detection rate
				//finalTweak is enabled iff there's no viable tweak to reach the targets
				if(finalTweak){
					if(worstDetectionRate >= 0.99){
						cout << " final tweak settles to " << tweak << endl;
						break; //desperate break;
					}else{
						tweak += TWEAK_UNIT;
						continue;
					}
				}

				//if !finalTweak, examine four scenarios one by one
				if(worstDetectionRate >= detectionRateTarget && worstFalsePositive <= falsePositiveTarget){
					layerMissionAccomplished = true;
					break; //happy break
				}else if(worstDetectionRate >= detectionRateTarget && worstFalsePositive > falsePositiveTarget){
					tweak -= tweakUnit;
					tweakCounter++;
					oscillationObserver[tweakCounter%2] = -1;
				}else if(worstDetectionRate < detectionRateTarget && worstFalsePositive <= falsePositiveTarget){
					tweak += tweakUnit;
					tweakCounter++;
					oscillationObserver[tweakCounter%2] = 1;
				}else{
					finalTweak = true;
					cout << "INFO: no way out at this point. tweak goes from " << tweak;
					continue;
				}

				//it is possible that tweak vascillates
				if(!finalTweak && tweakCounter > 1 && oscillationObserver.sum() == 0){
					//one solution is to reduce tweakUnit
					tweakUnit /= 2;
					tweak += oscillationObserver[tweakCounter%2] == 1 ? -1 * tweakUnit : tweakUnit;
					cout << "backtracked at " << tweakCounter << " ! Modify tweakUnit to " << tweakUnit << endl;
					//if that doesn't work, let's enforce the urgency mode
					if(tweakUnit < MIN_TWEAK){
						finalTweak = true;
						cout << "tweakUnit too small. tweak goes from " << tweak << endl;
					}
				}
			}

			if(overSized)
				break;
		}

		cout << "\nCongratulations! Mission fulfilled for LAYER " << round + 1 << endl << endl;


		//record
		layerMemory.push_back(trainSet.committee.size());
		cout << "The committee size is " << trainSet.committee.size() << endl << endl;

		//blacklist examples
		if(round > 0){
			delete [] trainingBlackList;
			delete [] testBlackList;
		}
		float detectionRate, falsePositive;
		trainingBlackList = trainSet.calcEmpiricalError(cascade, tweaks, round + 1, falsePositive, detectionRate, true);
		cout << "The current tweak " << tweaks[round] << " has falsePositive " << falsePositive << " and detectionRate " << detectionRate << " on the training examples.\n";
		testBlackList = testSet.calcEmpiricalError(cascade, tweaks, round + 1, falsePositive, detectionRate, true);
		cout << "The current tweak " << tweaks[round] << " has falsePositive " << falsePositive << " and detectionRate " << detectionRate << " on the validation examples.\n";
		cout << "Target:  falsePositiveTarget " << falsePositiveTarget << " detectionRateTarget " << detectionRateTarget << endl;
		accumulatedFalsePositive *= falsePositive;
		cout << "Accumulated False Positive Rate is around " << accumulatedFalsePositive << endl;

		//set flags
		bool isFirst = round == 0 ? true : false;
		bool isLast = round == nBoostingRounds - 1 || accumulatedFalsePositive < GOAL ? true : false;


		//record the boosted rule into a target file
		recordRule(target.toFile, trainSet.committee, isFirst, isLast);

		//release at the last round
		//if not, blackList is returned to remove examples
		if(isLast){
			delete [] trainingBlackList;
			delete [] testBlackList;
			delete [] cascade;
			break;
		}
	}

	//record layerMemory
	ofstream output;
	output.open(target.toFile, ios_base::app);
	//layerMemory size is the most reliable indicator of layers
	int layerCount = (int)layerMemory.size();
	output << "int Detector::layerCount=" << layerCount << ";\n";
	output << "int Detector::layerCommitteeSize[]={";
	for(int k = 0; k < layerCount; k++){
		output << layerMemory[k];
		if(k < layerCount - 1)
			output << ",";
		else
			output << "};\n";
	}
	output << "float Detector::tweaks[]={";
	output.precision(10);
	output.setf(ios::fixed, ios::floatfield);
	for(int k = 0; k < layerCount; k++){
		output << tweaks[k];
		if(k < layerCount - 1)
			output << ",";
		else
			output << "};\n";
	}
	output.close();
	times("trainingSpent: ");
}


//record the multi-layer rule
void recordRule(
	const char * toFile
,	vector<stumpRule> const & rule
,	bool firstLayer
,	bool lastLayer
){
	ofstream output;
	output.open(toFile, ios_base::app);
	int memberCount = rule.size();
	//start a new item
	if(firstLayer)
		output << "\ndouble Detector::stumps[][4]={\n";
	output.precision(10);
	output.setf(ios::fixed, ios::floatfield);
	for(int member = 0; member < memberCount; member++){
		//a rule has 4 parameters
		output << "{" << rule[member].featureIndex << "," << rule[member].weightedError << "," << rule[member].threshold << "," << rule[member].toggle << "}";
		//handle the comma properly
		if(member == memberCount -1 && lastLayer)
			output << "\n};\n";
		else
			output << ",\n";
	}
	//ok
	output.close();
}


