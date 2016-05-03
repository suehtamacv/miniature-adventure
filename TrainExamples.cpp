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
 * @file TrainExamples.cpp
 * @brief Training Utils implemented as an cpp object
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "TrainExamples.h"
#include "commonUtil.h"
#include "detectUtil.h"

#define VERBOSE true
#define NEGATIVE 1
#define POSITIVE 0

using namespace std;

//delete blackListed entries and read in all the rest
//if there aren't enough negative examples, get some more from the negative image pool
TrainExamples::TrainExamples(
	const char * positiveExamples
,	long double positiveWeight
,	const char * negativeExamples
,	const char * negativeImages
,	int numberNegatives
,	vector<stumpRule> * cascade
,	Row<float> & tweaks
,	int layerCount
,	Row<int> * blackList
,	const char * toFile
,	bool trainMode
,	bool allInMemory
){
	//training or validation set
	inTrain = trainMode;

	//cull false negative
    Mat<float> ** positives = NULL;
	nPositives = readImagesFromPathFile(positiveExamples, positives, blackList, POSITIVE);
	int patchSize = positives[0][0].rows();

	//read in good negatives and get more if necessary
	negativeImagePaths = negativeImages;
	nNegatives = numberNegatives;
    Mat<float> ** negatives = sampleNegatives(patchSize, cascade, tweaks, layerCount, negativeExamples, blackList);

	//final account
	sampleCount = nPositives + nNegatives;

	if(inTrain){

		//initialize the other class attributes for the training set
		initialPositiveWeight = positiveWeight;
		positiveTotalWeight = positiveWeight;
		negativeTotalWeight = 1 - positiveWeight;
		long double posAverageWeight = positiveTotalWeight/(long double)nPositives;
		long double negAverageWeight = negativeTotalWeight/(long double)nNegatives;
		maxWeight = max(posAverageWeight, negAverageWeight);
		minWeight = min(posAverageWeight, negAverageWeight);
		exponentialRisk = 1;

		//set example labels and weights
		weights.setZero(sampleCount);
		labels.setZero(sampleCount);
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++){
			labels(exampleIndex) = exampleIndex < nPositives ? 1 : -1;
			weights(exampleIndex) = exampleIndex < nPositives ? posAverageWeight : negAverageWeight;
		}

		//compute features to form the training set
		//example index starts with positives and then negatives
		times("");

		//limit the feature count
		bool enforceShape = true;

		//single out the first example to get the featureCount
		//and avoid multiple writing: blackList only NULL at the first round (see calcEmpiricalError)
        Row<float> * featureVector = NULL;
	 	computeHaarLikeFeatures(positives[0][0], featureVector, toFile, enforceShape, blackList == NULL);
		delete [] positives[0];
		featureCount = featureVector[0].size();

		//choose between memory or disk for data storage
        RowRow<float> * formattedFeatureVectors = NULL;
		if(allInMemory){
            formattedFeatureVectors = new RowRow<float> [featureCount];
			for(int f = 0; f < featureCount; f++){
				formattedFeatureVectors[f].setZero(sampleCount);
				formattedFeatureVectors[f][0] = featureVector[0][f];
			}
		}else
			writeToDisk(featureVector[0], "FeatureVector", /*exampleIndex*/0);
		delete [] featureVector;

		//now that the featureCount is known, go parallel for the other examples
		#pragma omp parallel for schedule(static)
		for(int exampleIndex = 1; exampleIndex < sampleCount; exampleIndex++){
            Row<float> * featureVector = NULL;
			if(exampleIndex < nPositives){
	 			computeHaarLikeFeatures(positives[exampleIndex][0], featureVector, toFile, enforceShape, false);
				delete [] positives[exampleIndex];
			}else{
				computeHaarLikeFeatures(negatives[exampleIndex-nPositives][0], featureVector, toFile, enforceShape, false);
				delete [] negatives[exampleIndex-nPositives];
			}
			if(allInMemory){
				for(int f = 0; f < featureCount; f++)
					formattedFeatureVectors[f][exampleIndex] = featureVector[0][f];
			}else
				writeToDisk(featureVector[0], "FeatureVector", exampleIndex);
			delete [] featureVector;
		}

		times("computeFeatures");

		//feature sorting to facilitate the stump construction
		ascendingFeatures = writeOrganizedFeatures(featureCount, sampleCount, formattedFeatureVectors);
	}else{
		//here we deal with the validation set
		labels.setZero(sampleCount);
        validationExamples = new Mat<float>[sampleCount];
		//don't learn from the validation data, hence a simpler initialisation
		#pragma omp parallel for schedule(static)
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++){
			labels(exampleIndex) = exampleIndex < nPositives ? 1 : -1;
			validationExamples[exampleIndex] = exampleIndex < nPositives ? positives[exampleIndex][0] : negatives[exampleIndex-nPositives][0];
			if(exampleIndex < nPositives)
				delete [] positives[exampleIndex];
			else
				delete [] negatives[exampleIndex-nPositives];
		}
	}

	//release
	delete [] positives;
	delete [] negatives;
}

TrainExamples::~TrainExamples(){
	if(inTrain && ascendingFeatures != NULL)
		delete [] ascendingFeatures;
	if(!inTrain)
		delete [] validationExamples;
}


//sample negative examples from images without human subjects
Mat<float> ** TrainExamples::sampleNegatives(
	int patchSize
,	vector<stumpRule> * cascade
,	Row<float> & tweaks
,	int layerCount
,	const char * negativeExamples
,	Row<int> * blackList
){
    Mat<float> ** existingNegatives = NULL;
	int nExistingNegatives = readImagesFromPathFile(negativeExamples, existingNegatives, blackList, NEGATIVE);
    Mat<float> ** goodNegatives = NULL;
	if(nNegatives <= nExistingNegatives){
		nNegatives = nExistingNegatives;
		return existingNegatives;
	}else{
		//sample some negatives to add to the negative pool
        goodNegatives = new Mat<float> * [nNegatives];
		for(int i = 0; i < nExistingNegatives; i++)
			goodNegatives[i] = existingNegatives[i];
		delete [] existingNegatives;
	}

	//prepare the negative images to draw examples from
	char ** addr = NULL;
	int nImages = pathFile2charArray(negativeImagePaths, addr, NULL, NEGATIVE);

	//record those sampled negatives
	ofstream output;
	//discard everything before writing
	output.open(negativeExamples, ios_base::app);

	int enough = nExistingNegatives;
	//those images with no more good negatives to draw
    Row<int> * uselessImages = new Row<int> [2];
	uselessImages[NEGATIVE].setZero(nImages);
	for(int k = 0; k < nImages && enough < nNegatives; k++){
		const char * file = addr[k];
        vector<rect> toMark;
		int nRows, nCols, nChannels;
		tscan(file, nRows, nCols, layerCount, cascade, tweaks, toMark);
		int falsePositiveRemaining = toMark.size();
		if(falsePositiveRemaining == 0){
			cout << "Wonderfully, not a single false positive window remains in " << file << endl;
			uselessImages[NEGATIVE](k) = 1;
			continue;
		}
		if(VERBOSE)
			cout << "Looking at " << file << " with " << falsePositiveRemaining << " false positive windows.\n";
		//let's try to make these false negatives into good examples
        Mat<float> * gray = NULL;
		imread(file, nRows, nCols, nChannels, gray, true);
		for(int s = 0; s < falsePositiveRemaining && enough < nNegatives; s++){
            Mat<float> * candidate = new Mat<float> [1];
            rect window = toMark[s];
			candidate[0] = gray[0].block(window.pos_i, window.pos_j, window.side, window.side);
			if(zoomOutNegative(candidate, patchSize, layerCount, cascade, tweaks)){
				goodNegatives[enough] = candidate;
				//write out
				char buffer[100];
				const char * testFlag = inTrain ? "training" : "validation";
				sprintf(buffer, "%s/%s_%d_%d.png", "newlyCollectedNegatives", testFlag, layerCount, enough);
                Mat<float> * acceptedCandidate = new Mat<float> [1];
				acceptedCandidate[0] = candidate[0];
				imwrite(buffer, acceptedCandidate, 1);
				string line(buffer);
				output << line << endl;
				enough++;
			}
		}
		//it has done its part, hence deleted after this round
		if(enough < nNegatives)
			uselessImages[NEGATIVE](k) = 1;
		delete [] gray;
	}
	output.close();
	if(enough < nNegatives)
		fail("Not enough negative images for training or validation");


	//release
	for(int c = 0; c < 2; c++){
		for(int i = 0; i < nImages; i++ )
			delete [] addr[i];
		delete [] addr;
		//delete those unhelpful image paths so that they won't be looked at again.
		if(c == 0){
			nImages = pathFile2charArray(negativeImagePaths, addr, uselessImages, NEGATIVE);
			delete [] uselessImages;
		}
	}

	return goodNegatives;
}

void TrainExamples::predictLabel(float decisionTweak
,	Row<int> &prediction
,	bool onlyMostRecent
){
	int committeeSize = committee.size();
	//no need to weigh a single member's decision
	onlyMostRecent = committeeSize == 1 ? true : onlyMostRecent;
	int start = onlyMostRecent ? committeeSize - 1 : 0;
	//double to be more precise
	MatrixXd memberVerdict(committeeSize, sampleCount);
	RowVectorXd memberWeight(committeeSize);
	//members, go ahead
	for(int member = start; member < committeeSize; member++){
		//sanity check
		if(committee[member].weightedError == 0 && member != 0)
			fail("Boosting Error Occured!");
		//0.5 does not count here
		//if member's weightedError is zero, member weight is nan, but it won't be used anyway
		memberWeight[member] = log(1./committee[member].weightedError -1);
		int feature = committee[member].featureIndex;
		#pragma omp parallel for schedule(static)
		for(int iterator = 0; iterator < sampleCount; iterator++){
			int exampleIndex = getExampleIndex(feature, iterator);
			memberVerdict(member, exampleIndex) = (getExampleFeature(feature, iterator) > committee[member].threshold ? 1 : -1)*committee[member].toggle + decisionTweak;
		}
	}
	//joint session
	if(!onlyMostRecent){
		RowVectorXd finalVerdict = memberWeight*memberVerdict;
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++)
			prediction[exampleIndex] = finalVerdict[exampleIndex] > 0 ? 1 : -1;
	}else{
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++)
			prediction[exampleIndex] = memberVerdict(start, exampleIndex) > 0 ? 1 : -1;
	}
}

//why's one stump better than the other
bool TrainExamples::myStumpOrder(
	const stumpRule & one
,	const stumpRule & other
){
	if(one.weightedError < other.weightedError)
		return true;
	if(one.weightedError == other.weightedError && one.margin > other.margin)
		return true;
	return false;
}


//base learner is a stump, a decision tree of depth 1
//decisionStump has to look at feature and return rule
void TrainExamples::decisionStump(
	int featureIndex
,	stumpRule & best
){
	//a stump is determined by threshold and toggle, the other two attributes measures its performance
	//initialize with some crazy values
	best.featureIndex = featureIndex;
	best.weightedError = 2;
	best.threshold = getExampleFeature(featureIndex, 0) - 1;
	best.margin = -1;
	best.toggle = 0;

	stumpRule current = best;

	//error_p and error_n allow to set the best toggle
	long double error_p, error_n;

	//initialize: r denotes right hand side and l left hand side
	//convention: in TrainExamples nPositives positive samples are followed by negatives samples
	long double rPositiveWeight = positiveTotalWeight;
	long double rNegativeWeight = negativeTotalWeight;
	//yes, nothing to the left of the sample with the smallest feature
	long double lPositiveWeight = 0;
	long double lNegativeWeight = 0;

	//go through all these observations one after another
	int iterator = -1;

	//to build a decision stump, you need a toggle and an admissible threshold
	//which doesn't coincide with any of the observations
	while(true){

		//We've got a threshold. So determine the best toggle based on two types of error
		//toggle = 1, positive prediction if and only if the observed feature > the threshold
		//toggle = -1, positive prediction if and only if the observed feature < the threshold

		//error_p denotes the error introduced by toggle = 1, error_n the error by toggle = -1
		error_p = rNegativeWeight + lPositiveWeight;
		error_n = rPositiveWeight + lNegativeWeight;
		current.toggle = error_p < error_n ? 1 : -1;

		//sometimes shit happens, prevent error from being negative
		long double smallerError = min(error_p, error_n);
		//this prevents some spurious nonzero: for currentError must be at least equal to minWeight
		current.weightedError = smallerError < minWeight * 0.9 ? 0 : smallerError;

		//update if necessary
		if(myStumpOrder(current, best))
			best = current;

		//move on
		iterator++;

		//we don't actually need to look at the sample with the largest feature
		//because its rule is exactly equivalent to those produced
		//by the sample with the smallest feature on training observations
		//but it won't do any harm anyway
		if(iterator == sampleCount)
			break;

		//handle duplicates, update lr weights and find a new threshold
		while(true){

			//take this guy's attributes
			int exampleIndex = getExampleIndex(featureIndex, iterator);
			int label = labels[exampleIndex];
			long double weight = weights[exampleIndex];

			//update weights
			if(label < 0){
				lNegativeWeight += weight;
				rNegativeWeight -= weight;
			}else{
				lPositiveWeight += weight;
				rPositiveWeight -= weight;
			}

			//if a new threshold can be found, break
			//two cases are possible: either it is the last observation
			if(iterator == sampleCount - 1)
				break;
			//or no duplicate. If there is a duplicate, repeat
			if(getExampleFeature(featureIndex, iterator) != getExampleFeature(featureIndex, iterator + 1)){
				double test = ((double)getExampleFeature(featureIndex, iterator) + (double)getExampleFeature(featureIndex, iterator + 1))/2;
				//well that's a bit frustrating: I want to keep float because of memory constraint, but apparently
				//features are so close, sometimes, numerical precision arises as an unexpected problem, so I decide
				//to use a double threshold so as to separate float features
				if(getExampleFeature(featureIndex, iterator) < test && test < getExampleFeature(featureIndex, iterator + 1))
					break;
				else{
					#pragma omp critical
					{
						cout << "ERROR: numerical precision breached: problem feature values " << getExampleFeature(featureIndex, iterator) << " : " << getExampleFeature(featureIndex, iterator+1) << ". Problem feature " << featureIndex << " and problem example " << getExampleIndex(featureIndex, iterator) << " : " << getExampleIndex(featureIndex, iterator+1) << endl;
					}
					fail("fail to find a suitable threshold.");
				}
			}
			iterator++;
		}

		//update threshold
		if(iterator < sampleCount - 1){
			current.threshold = ((double)getExampleFeature(featureIndex, iterator) + (double)getExampleFeature(featureIndex, iterator + 1))/2;
			current.margin = getExampleFeature(featureIndex, iterator + 1) - getExampleFeature(featureIndex, iterator);
		}else{
			//slightly to the right of the biggest observation
			current.threshold = getExampleFeature(featureIndex, iterator) + 1;
			current.margin = 0;
		}
	}
}

//implement the feature selection's outer loop
//return the most discriminative feature and its rule
stumpRule TrainExamples::bestStump(
){
	vector<stumpRule> candidates;
	candidates.resize(featureCount);
	#pragma omp parallel for schedule(static)
	for(int featureIndex = 0; featureIndex < featureCount; featureIndex++)
		decisionStump(featureIndex, candidates[featureIndex]);

	//loop over all the features
	//the best rule has the smallest weighted error and the largest margin
	stumpRule best = candidates[0];
	for(int featureIndex = 1; featureIndex < featureCount; featureIndex++){
		if(myStumpOrder(candidates[featureIndex], best))
			best = candidates[featureIndex];
	}

	//if shit happens, tell me
	if( best.weightedError >= 0.5 )
		fail("Decision Stump failed: base error >= 0.5");

	//return
	return best;
}


void TrainExamples::adaboost(){
	//try to be friendly here
	static int trainPhase = 0;
	if(VERBOSE && trainPhase == 0){
		cout << "\n#############################ADABOOST MESSAGE EXPLAINED####################################################\n\n";
		cout << "INFO: Adaboost starts. Exponential Risk is expected to go down steadily and strictly," << endl;
		cout << "INFO: and Exponential Risk should bound the (weighted) Empirical Error from above." << endl;
		cout << "INFO: Train Phase is the current boosting iteration." << endl;
		cout << "INFO: Best Feature is the most discriminative feature selected by decision stump at this iteration." << endl;
		cout << "INFO: Threshold and Toggle are two parameters that define a real valued decision stump.\n" << endl;
	}
	trainPhase++;

	//get and store the rule
	stumpRule rule = bestStump();
	committee.push_back(rule);

	//how it fares
    RowRow<int> prediction(sampleCount);
	predictLabel(
		/*decisionTweak*/ 0
	,	prediction
	,	/*onlyMostRecent*/ true);
    Row<int> agree = labels.cwiseProduct(prediction.transpose());

	//update weights
    Row<double> weightUpdate;
	weightUpdate.setOnes(sampleCount);
	bool errorFlag = false;
	for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++){
		//more weight for a difficult example
		if(agree[exampleIndex] < 0){
			weightUpdate[exampleIndex] = 1/rule.weightedError - 1;
			errorFlag = true;
		}
	}
	//update weights only if there is an error
	if(errorFlag){
		weights = weights.cwiseProduct(weightUpdate);
		weights /= weights.sum();
		positiveTotalWeight = weights.head(nPositives).sum();
		negativeTotalWeight = 1-positiveTotalWeight;
		minWeight = weights.minCoeff();
		maxWeight = weights.maxCoeff();
	}

	//exponentialRisk can be zero at the first boosting
	exponentialRisk *= 2*sqrt((1-rule.weightedError)*rule.weightedError);

	//print some statistics
	if(VERBOSE){
        Row<float> tweaks;
		tweaks.setZero(1);
		float falsePositive = 0;
		float detectionRate = 0;
		calcEmpiricalError(&committee, tweaks, 1, falsePositive, detectionRate, false);
		float empError = falsePositive*(1-initialPositiveWeight)+initialPositiveWeight*(1-detectionRate);
		cout << "Training Performance Explanation (before threshold tweaking): falsePositive " << falsePositive << " detectionRate " << detectionRate << endl;
		cout <<"###########################################################################################################\n";
		cout << "\nTrain Phase " << trainPhase << endl << endl;
		whatFeature(rule.featureIndex);
		cout << "\tExponential Risk " << setw(12) << exponentialRisk << setw(19) << "Weighted Error " << setw(11) << rule.weightedError << setw(14) << "Threshold " << setw(10) << rule.threshold << setw(13) <<"Toggle " << setw(12) << rule.toggle <<  endl;
		cout << "\tPositive Weight" << setw(14) << positiveTotalWeight << setw(14) << "MinWeight " << setw(16) << minWeight << setw(14) << "MaxWeight " << setw(10) << maxWeight << setw(22) << "Empirical Error " << setw(10) << empError << endl << endl;
	}
}

//validation procedure mainly for test case
Row<int> * TrainExamples::calcEmpiricalError(
	vector<stumpRule> const * cascade
,	Row<float> & tweaks
,	int layerCount
,	float & falsePositive
,	float & detectionRate
,	bool hasReturn
){
	int nFalsePositive = 0;
	int nFalseNegative = 0;
    Row<int> * blackList = hasReturn ? new Row<int>[2] : NULL;
	if(hasReturn){
		blackList[POSITIVE].setZero(nPositives);
		blackList[NEGATIVE].setOnes(nNegatives);
	}
	if(inTrain){
		//initially let all be positive
        RowRow<int> verdicts, layerPrediction;
		verdicts.setOnes(sampleCount);
		layerPrediction.setZero(sampleCount);
		for(int layer = 0; layer < layerCount; layer++){
			//set committee
			committee = cascade[layer];
			predictLabel(tweaks[layer], layerPrediction, false);
			//those at -1, remain where you are
			verdicts = verdicts.cwiseMin(layerPrediction);
		}

		//evaluate prediction errors
        Row<int> agree = labels.cwiseProduct(verdicts.transpose());
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++){
			if(agree[exampleIndex] < 0){
				if(exampleIndex < nPositives){
					//remove difficult positives
					if(hasReturn)
						blackList[POSITIVE][exampleIndex] = 1;
					nFalseNegative += 1;
				}else{
					//keep difficult negatives
					if(hasReturn)
						blackList[NEGATIVE][exampleIndex-nPositives] = 0;
					nFalsePositive += 1;
				}
			}
		}
	}else{
		for(int exampleIndex = 0; exampleIndex < sampleCount; exampleIndex++){
			bool hasFace = exampleScan(validationExamples[exampleIndex], layerCount, cascade, tweaks);
			if(!hasFace && exampleIndex < nPositives){
				if(hasReturn)
					blackList[POSITIVE][exampleIndex] = 1;
				nFalseNegative += 1;
			}
			if(hasFace && exampleIndex >= nPositives){
				if(hasReturn)
					blackList[NEGATIVE][exampleIndex-nPositives] = 0;
				nFalsePositive += 1;
			}
		}

	}
	//set the returned values
	falsePositive = nFalsePositive/(float)nNegatives;
	detectionRate = 1 - nFalseNegative/(float)nPositives;

	return blackList;
}
