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
 * @file TrainExamples.h
 * @brief header for TrainExamples.cpp
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#ifndef TRAINEXAMPLES_H
#define TRAINEXAMPLES_H

#include <vector>
#include <utility>
#include <armadillo>
#include "commonUtil.h"

using namespace std;
using namespace arma;

/**
 * @brief decision stump definition
 *
 * @param featureIndex
 * @param weightedError achieved weighted error
 * @param threshold
 * @param margin achieved margin
 * @param toggle +1 or -1
 */
struct stumpRule{
	int featureIndex;
	long double weightedError;
	double threshold;
	float margin;
	int toggle;
};

class TrainExamples{
public:
	/**
	 * @brief what's inside
	 *
	 * @param nPositives number of positive examples
	 * @param nNegatives number of negative examples
	 * @param sampleCount nPositives + nNegatives
	 * @param inTrain is this a training set or a validation set
	 * @param initialPositiveWeight how much weight we give to positives at the outset
	 * @param exponentialRisk exponential risk for training set
	 * @param positiveTotalWeight total weight received by positive examples currently
	 * @param negativeTotalWeight total weight received by negative examples currently
	 * @param minWeight minimum weight among all weights currently
	 * @param maxWeight maximum weight among all weights currently
	 * @param weights weight vector for all examples involved
	 * @param labels are they positive or negative examples
	 * @param ascendingFeatures for each feature, we have (float feature value, int exampleIndex)
	 * @param featureCount how many features are there
	 * @param committee what's the learned committee
	 */
	int nPositives;
	int nNegatives;
	int sampleCount;
	bool inTrain;
	long double initialPositiveWeight;
	long double exponentialRisk;
	long double positiveTotalWeight;
	long double negativeTotalWeight;
	long double minWeight;
	long double maxWeight;
    Row<double> weights;
    Row<int> labels;
	vector< pair<float, int> > * ascendingFeatures;
	int featureCount;
	vector<stumpRule> committee;
	const char * negativeImagePaths;
    Mat<float> * validationExamples;

	/**
	 * @brief constructor to use if you have enough memory
	 *
	 * @param positivePaths paths leading to positive examples
	 * @param negativePaths paths leading to negative examples
	 * @param toFile all the relevant information for building the detector
	 * @param blackList what are the examples to eliminate before starting training
	 * @param positiveWeight how much weight to give to positive examples at the beginning
	 * @param trainMode training or validation set
	 * @param allInMemory do everything in memory or on disk
	 */
	TrainExamples(
		const char * positivePaths
	,	long double positiveWeight
	,	const char * negativePaths
	,	const char * negativeImages
	,	int numberNegatives
	,	vector<stumpRule> * cascade
    ,	Row<float> & tweaks
	,	int layerCount
    ,	Row<int> * blackList
	,	const char * toFile
	,	bool trainMode
	,	bool allInMemory
	);

	~TrainExamples();

	/**
	 * @brief evaluate how the committee fares on a dataset
	 *
	 * @param cascade a given cascade of committees
	 * @param tweaks used for fulfill each layer's training target
	 * @param layerCount how many layers are there in the cascade
	 * @return falsePositive
	 * @return detectionRate
	 * @param hasReturn whether to return a blackList pointing to false negative and true negatives
	 */
    Row<int> * calcEmpiricalError(
		vector<stumpRule> const * cascade
    ,	Row<float> & tweaks
	,	int layerCount
	,	float & falsePositive
	,	float & detectionRate
	,	bool hasReturn
	);

	/**
	 * @brief perform one round of adaboost
	 */
	void adaboost();

private:
	/**
	 * @brief get some extra negatives if necessary
	 */
    Mat<float> ** sampleNegatives(
		int patchSize
	,	vector<stumpRule> * cascade
    ,	Row<float> & tweaks
	,	int layerCount
	,	const char * negativeExamples
    ,	Row<int> * blackList
	);
	/**
	 * @brief what makes one stump better than the other
	 */
	bool myStumpOrder(
		const stumpRule & one
	, 	const stumpRule & other
	);
	/**
	 * @brief return for an element pointed by iterator and featureIndex its exampleIndex
	 */
	int getExampleIndex(int featureIndex, int iterator){
		if(ascendingFeatures != NULL)
			return ascendingFeatures[featureIndex][iterator].second;
		else
			return readFromDisk("OrganizedSample", featureIndex, iterator);

	}
	/**
	 * @brief return for an element pointed by iterator and featureIndex its example value
	 */
	float getExampleFeature(int featureIndex, int iterator){
		if(ascendingFeatures != NULL){
			if(isnan(ascendingFeatures[featureIndex][iterator].first)){
				cerr<<"ERROR: nan feature "<<featureIndex<<" detected for example "<<getExampleIndex(featureIndex, iterator)<<endl;
				exit(EXIT_FAILURE);
			}
			return ascendingFeatures[featureIndex][iterator].first;
		}else
			return readFromDisk("OrganizedFeatures", featureIndex, iterator);

	}
	/**
	 * @brief best stump given a feature
	 */
	void decisionStump(
		int featureIndex
	, 	stumpRule & best
	);
	/**
	 * @brief best stump among all features
	 */
	stumpRule bestStump();
	/**
	 * @brief given a tweak and a committe, what prediction do you make as to the examples
	 *
	 * @param thresholdTweak tweak
	 * @return prediction
	 * @param onlyMostRecent use all the committee or its most recent member (a weak learner)
	 */
	void predictLabel(
		float thresholdTweak
    , 	Row<int> & prediction
	, 	bool onlyMostRecent
	);
};

#endif
