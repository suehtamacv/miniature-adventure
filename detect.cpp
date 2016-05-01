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
 * @file detect.cpp
 * @brief command line for the viola jones face detector
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <iostream>
#include <sstream>
#include <string>
#include "detectUtil.h"
using namespace std;

#define MIN_FRIENDS 3
int main( int argc, char * const * argv){

	bool stop = false;

	//sanity check
	if(!(argc == 2 || argc == 4)){
		cerr << "\n\t Usage: please provide a PNG image for face detection.\n";
		cerr << "\t If the number of layers is specified, only those are used in detection.\n";
		cerr << "\t The robustness threshold for postprocessing can also be set here.\n\n";
		stop = true;
	}else{
		string imageName(argv[1]);
		string legalSuffix(".png");
		if(imageName.find(legalSuffix)==string::npos){
			cerr << "\n\tOnly PNG is supported. If your input is a PNG, please include its suffix.\n\n";
			stop = true;
		}
	}

	//what to do
	if(stop){
		cerr << "\t\t Example: \n\n";
		cerr << "\t\t\t\t ./detect example.png <number of layers> <threshold>\n\n";
        	return EXIT_FAILURE;
	}

	//if defaultLayerNumber = -1, the detector shall base its decision on all the cascade layers
	int defaultLayerNumber = argc == 4 ? atoi(argv[2]) : -1;
	float required_nFriends = argc == 4 ? atoi(argv[3]) : MIN_FRIENDS;
	const char * image = argv[1];
	scan(image, defaultLayerNumber, required_nFriends);
}
