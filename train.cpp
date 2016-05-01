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
 * @file train.cpp
 * @brief command line for training a viola jones cascade detector
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <iostream>
#include <string>
#include "boostUtil.h"

#define LAYER_DETECTION_RATE 0.995
#define LAYER_FALSE_POSITIVE 0.5
#define OVERALL_DETECTION_RATE 0.80
#define OVERALL_FALSE_POSITIVE 1e-6

using namespace std;

int main( int argc, char *const *argv ){

	const char * defaultOutput = "Detector.cxx";

	if( !(argc == 6 || argc == 1) ){
		cerr << endl << "\t Usage : to train a face detector, you might want to set a target" << endl << endl;
		cerr << "\t\t 1. overall detection rate (defaults to " << OVERALL_DETECTION_RATE << ")\n";
		cerr << "\t\t 2. overall false positive rate (defaults to " << OVERALL_FALSE_POSITIVE << ")\n";
		cerr << "\t\t 3. layer detection rate (defaults to " << LAYER_DETECTION_RATE << ")\n";
		cerr << "\t\t 4. layer false positive rate (defaults to " << LAYER_FALSE_POSITIVE << ")\n";
		cerr << "\t\t 5. output file (defaults to " << defaultOutput << ")\n";
		cerr << "\t\t Example: " << endl << endl;
		cerr <<  "\t\t\t\t ./train 0.94 0.00001 0.995 0.3 Detector.cxx" << endl << endl;
		cerr << "\t\t or simply" << endl << endl;
		cerr <<  "\t\t\t\t ./train" << endl << endl;
        	return EXIT_FAILURE;
	}

	trainParams param;
	int i = 1;
	param.overallTargetDetectionRate = argc == 1 ? OVERALL_DETECTION_RATE : atof(argv[i++]);
	param.overallTargetFalsePositiveRate = argc == 1 ? OVERALL_FALSE_POSITIVE : atof(argv[i++]);
	param.layerTargetDetectionRate = argc == 1 ? LAYER_DETECTION_RATE : atof(argv[i++]);
	param.layerTargetFalsePositiveRate = argc == 1 ? LAYER_FALSE_POSITIVE : atof(argv[i++]);
	param.toFile = argc == 1 ? defaultOutput : argv[i];

	//my defaults
	param.positiveTotalWeight = 0.5;
	param.allInMemory = true;
	param.positiveExamples = "positives.txt";
	param.negativeExamples = "negatives.txt";
	param.positiveTestExamples = "test_positives.txt";
	param.negativeTestExamples = "test_negatives.txt";

	//sanity check
	string usr_str(argv[5]);
	string exist_str("Detector.cpp");
	if(exist_str == usr_str){
		cerr << "ERROR: change to Detector.cpp is disallowed for safety reasons.\n";
		return EXIT_FAILURE;
	}
	if(abs(param.overallTargetDetectionRate - 0.5) > 0.5){
		cerr << "ERROR: overall targeted detection rate is out of range." << endl;
		return EXIT_FAILURE;
	}
	if(abs(param.overallTargetFalsePositiveRate - 0.5) > 0.5){
		cerr << "ERROR: overall targeted false positive rate is out of range." << endl;
		return EXIT_FAILURE;
	}
	if(abs(param.layerTargetDetectionRate - 0.5) > 0.5){
		cerr << "ERROR: layer targeted detection rate is out of range." << endl;
		return EXIT_FAILURE;
	}
	if(abs(param.layerTargetFalsePositiveRate - 0.5) > 0.5){
		cerr << "ERROR: layer targeted false positive rate is out of range." << endl;
		return EXIT_FAILURE;
	}
	if(param.layerTargetDetectionRate <= param.overallTargetDetectionRate){
		cerr << "ERROR: the chosen detection rates are not viable." << endl;
		return EXIT_FAILURE;
	}
	if(param.layerTargetFalsePositiveRate <= param.overallTargetFalsePositiveRate){
		cerr << "ERROR: the chosen false positive rates are not viable." << endl;
		return EXIT_FAILURE;
	}
	if(log(param.overallTargetDetectionRate)/log(param.layerTargetDetectionRate) - 1 < log(param.overallTargetFalsePositiveRate)/log(param.layerTargetFalsePositiveRate)){
		cerr << "ERROR: target and overall rates are not consistent!" << endl;
		return EXIT_FAILURE;
	}

	train(param);
	return EXIT_SUCCESS;

}

