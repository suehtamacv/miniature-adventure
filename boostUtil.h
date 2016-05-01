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
 * @file boostUtil.h
 * @brief header file for the Viola-Jones algorithm's training routines
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#ifndef BOOSTUTIL_H
#define BOOSTUTIL_H

#include <vector>
#include "TrainExamples.h"

using namespace std;
using namespace Eigen;

/**
 * @brief human interface for adaboost training
 *
 * @param layerTargetDetectionRate layer wide target detection rate
 * @param layerTargetFalsePositiveRate layer wide target false positive rate
 * @param overallTargetDetectionRate overall target detection rate
 * @param overallTargetFalsePositiveRate overall target false positive rate
 * @param positiveTotalWeight total weight for positives
 * @param positiveExamples pathFile to positive samples
 * @param negativeExamples pathFile to negative samples
 * @param positiveTestExamples pathFile to positive samples for testing
 * @param negativeTestExamples pathFile to negative samples for testing
 * @param toFile filename for all the additional recording (the constructed cascade for example)
 * @param allInMemory do everything in memory
 */
struct trainParams{
	float layerTargetDetectionRate;
	float layerTargetFalsePositiveRate;
	float overallTargetDetectionRate;
	float overallTargetFalsePositiveRate;
	long double positiveTotalWeight;
	const char * positiveExamples;
	const char * negativeExamples;
	const char * positiveTestExamples;
	const char * negativeTestExamples;
	const char * toFile;
	bool allInMemory;
};


/**
 * @brief train a cascade, see the definition of trainParams
 */
void train(trainParams const & target);

/**
 * @brief record a strong learner to toFile
 *
 * @param toFile where
 * @param rule the strong learner
 * @param firstLayer is it a firstLayer in the cascade
 * @param lastLayer is it a last layer in the cascade
 */
void recordRule(
	const char * toFile
,	vector<stumpRule> const & rule
,	bool firstLayer
,	bool lastLayer
);


#endif
