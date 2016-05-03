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
 * @file commonUtil.cpp
 * @brief common routines for image IO
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sys/time.h>
#include <string>
#include <limits>
#include <utility>
#include <vector>
#include "io_png.h"
#include "commonUtil.h"
#include "Detector.h"

#define VERBOSE true
#define UNIT 1e2
#define STORAGE "trainData"

using namespace std;
using namespace arma;

//fail and messaging
void fail(string const & message){
	cerr << "ERROR: " << message << endl;
	exit(EXIT_FAILURE);
}

//timer for routines
void times(const char * which){
	/* If which is not empty, print the times since the previous call. */
	static double last_wall = 0.0, last_cpu = 0.0;
	double wall, cpu;
	struct timeval tv;
	clock_t stamp = 0;

	wall = last_wall;
	cpu = last_cpu;
	if (gettimeofday(&tv,NULL) != 0 || (stamp = clock()) == (clock_t)-1){
		string message("Unable to get times for ");
	    	fail(message + which);
	}
	last_wall = tv.tv_sec+1.0e-6*tv.tv_usec;
	last_cpu = stamp/(double)CLOCKS_PER_SEC;
	if (strlen(which) > 0){
	    wall = last_wall-wall;
	    cpu = last_cpu-cpu;
	    cout << endl << which << " time = " << wall << " seconds, CPU = " << cpu << " seconds" << endl << endl;
	}
}

//read in an image in two modes
//selectable with outputGray flag
void imread(const char * fileName
,	int & nRows
,	int & nCols
,	int & nChannels
,	Mat<float> *&image
,	bool outputGray
){
	//readin mode selection
	size_t nx, ny, nc;
	float * pixelStream = NULL;
	pixelStream = outputGray ? read_png_f32_gray(fileName, &nx, &ny) : read_png_f32(fileName, &nx, &ny, &nc);
	if(pixelStream == NULL){
		string message("Unable to get the image ");
		fail(message+fileName);
	}

	//return these parameters
	nCols = (int)nx;
	nRows = (int)ny;
	const char * end = outputGray ? " as gray." : ".";
	nChannels = outputGray ? 1 : (int)nc;
	//reduce log
	if(VERBOSE && false)
		cout << "INFO: read in " << fileName << " of dimension: (" << ny << " , " << nx << " , " << nChannels << ")" << end << endl;

    //input stream assumes row-major while Eigen defaults to column-major
    Mat<float> parallel(pixelStream, nCols, nRows*nChannels);
    image = new Mat<float> [nChannels];
	for( int ch = 0; ch < nChannels; ch++ )
        image[ch] = parallel(span(0, nCols-1),span(ch*nRows, ch*nRows + nRows - 1)).t();

	//release
	free(pixelStream);
}

//image write in MATLAB style, after which MatrixXf * image is released
void imwrite(const char * fileName
, 	Mat<float> *image
, 	int nChannels
){
	//allocate
    int nCols = image[0].n_cols;
    int nRows = image[0].n_rows;
	int pixelsPerChannel = nCols*nRows;
	float * output = new float [pixelsPerChannel*nChannels];

	//this part should be straightforward but still be careful with the order
	#pragma omp parallel for schedule( static )
	for(int j = 0; j < nCols; j++)
		for(int i = 0; i < nRows; i++)
			for(int ch = 0; ch < nChannels; ch++)
				output[ch*pixelsPerChannel + i*nCols + j] = image[ch](i,j);

	//output image
	write_png_f32(fileName, output, (size_t) nCols, (size_t) nRows, (size_t) nChannels);
	//reduce log
	if(VERBOSE && false)
		cout << "INFO: write the image " << fileName << " to local folder." << endl;

	//release
	delete [] output;
	delete [] image;
}

//compute an integral image in linear time
void buildIntegralImage(
    Mat<float> & image
,	Mat<double> & integralImage
){
    int nRows = image.n_rows;
    int nCols = image.n_cols;
	//O(n) complexity: however no parallel should be used
	for(int i = 0; i < nRows; i++)
		for(int j = 0; j < nCols; j++){
			integralImage(i,j) = image(i,j);
			integralImage(i,j) += i > 0 ? integralImage(i-1,j) : 0;
			integralImage(i,j) += j > 0 ? integralImage(i,j-1) : 0;
			integralImage(i,j) -= min(i,j) > 0 ? integralImage(i-1,j-1) : 0;
	}
}

//inverse of buildIntegralImage()
long double sumImagePart(Mat<double> &integralImage
,	int ui
,	int uj
,	int ir 	//column length
,	int jr 	//row length
){
	//rectangle's other pair of coordinates
	int di = ui + ir - 1;
	int dj = uj + jr - 1;
	//standard operation
    return integralImage(di,dj) -
            (ui > 0 ? integralImage(ui-1,dj) : 0) -
            (uj > 0 ? integralImage(di,uj-1) : 0) +
            (((ui > 0) && (uj > 0)) ? integralImage(ui-1,uj-1) : 0);
}

//convert the pathFile to char array and return path count
//if a valid blackList is provided, delete blackListed (1) samples
//update the second argument while others are purely inputs
int pathFile2charArray(const char * pathFile
,	char **& addr
,	Row<int> *blackList
,	int sign
){
	//delete these blackListed paths
	bool doNothing = blackList == NULL ? true : false;
	int listSize = blackList == NULL ? 0 : blackList[sign].size();

	//a temporary file storing sample to retain
	char buffer [100];
	sprintf(buffer, "temporary%s", pathFile);
	const char * keeped = buffer;
	//sanity check
	fileExist(keeped);
	//actually create this file if !doNothing
	if(!doNothing){
		FILE * pFile;
	  	pFile = fopen(keeped, "w");
	 	if( pFile == NULL ){
			string path("Unable to create an empty ");
			fail(path+keeped);
		}else
	 		fclose(pFile);
	}



	//initialize the returned value
	int pathCount = 0;

	//meat
	//if doNothing first loop determines file size, second loop reads in paths
	//if not doNothing, first loop deletes blackListed lines, second loop reads in paths
	for( int loop = 0; loop < 2; loop++ ){

		//read in pathFile
		ifstream myfile(pathFile);
		if(!myfile.is_open()){
			string path("Please provide a valid ");
			fail(path+pathFile);
		}

		string line;
		//an offset to make the line count (total) right
		//this will also be reflected the condition 5 lines later
		int total = -1;
		while( myfile.good() ){

			//count lines
			getline( myfile, line );
			total += 1;

			if(!doNothing && total < listSize && loop == 0){
				//not blackListed
				if(blackList[sign][total] == 0){
					ofstream output;
					output.open(keeped, ios_base::app);
					output << line << endl;
					output.close();
				}
			}

			//only do this at the second loop
			if( loop == 1 && total < pathCount ){
				//convert string to char array
				addr[total] = new char [line.size()+1];
				addr[total][line.size()] = 0;
				memcpy(addr[total], line.c_str(), line.size());
			}
		}

		myfile.close();

		//first loop just count the number of lines in the file
		if( loop == 0 ){
			//remove those blackListed
            pathCount = blackList == NULL ? total : total - accu(blackList[sign]);

			//now delete samples if necessary
			if(!doNothing){
				removeFile(pathFile);
				if(rename(keeped, pathFile)){
					string message("Unable to rename ");
					fail(message+keeped+" to "+pathFile);
				}
			}


			//now if there's a problem, I'll be able to track it down
			if(pathCount < 1){
				cout << "pathCount = " << pathCount << " No grayscale PNG examples available in " << pathFile << endl;
				return 0;
			}

			//allocate
			addr = new char * [pathCount];
		}
	}
	return pathCount;
}

//collect training image set provided by a pathFile
//plus a blackList
//and return these images in matrix form
int readImagesFromPathFile(const char * pathFile
,	Mat<float> ** & images
,	Row<int> *blackList
,	int sign
){
	char ** addr = NULL;
	int sampleCount = pathFile2charArray(pathFile, addr, blackList, sign);
	if(sampleCount == 0)
		return sampleCount;
	//now read in all the images in grayscale
	//their addresses are stored in addr[]
	//rnRows and rnCols are the reference's size
	//all samples should have the same size
	//otherwise, the algorithm will abort
	int nRows, nCols, nChannels;
	//g++ complains about uninitialized values
	int rnRows = 0;
	int rnCols = 0;
    images = new Mat<float> * [sampleCount];
	for(int sample = 0; sample < sampleCount; sample++){
		const char * file = addr[sample];
		imread(file, nRows, nCols, nChannels, images[sample], true);
		//sanity check
		if(sample == 0){
			rnRows = nRows;
			rnCols = nCols;
			if(VERBOSE)
				cout << "INFO: this is the size reference image (" << rnRows << ", " << rnCols << ")." << endl;
		}
		if(abs(rnRows-nRows)+abs(rnCols-nCols)){
			string message("Sample size should not vary.");
			fail(message);
		}
	}

	//release
	for(int sample = 0; sample < sampleCount; sample++)
		delete [] addr[sample];
	delete [] addr;

	//return
	return sampleCount;
}

//write out a vector to disk if there isn't enough memory available
void writeToDisk(Row<float> &dataVector
,	char const * prefix
,	int index
){
	//cut the dataVector into pieces so that it won't be costly to retrieve the coordinate values later
	//each piece shall be no greater than UNIT
	int size = dataVector.size();
	int unit = UNIT;
	int pieceCount = ceil(size/(float)unit);
	int remainder = size%unit;

	//flush out
	#pragma omp parallel for schedule(static)
	for(int piece = 0; piece < pieceCount; piece++){
		char buffer[100];
		sprintf(buffer, "%s/%s_%d_%d", STORAGE, prefix, index, piece);
		const char * fname = buffer;
		//sanity check
		fileExist(fname);
		//write out a segment of the feature vector
		ofstream output;
		//start anew so that I don't have to delete them
		output.open(fname, ios_base::trunc);
		output.precision(10);
		output.setf(ios::fixed, ios::floatfield);
		int start = piece * unit;
		int length = unit;
		if(piece == pieceCount - 1 && remainder)
			length = remainder;
        output << dataVector.rows(start, start + length - 1) << endl;
        output.close();
	}
}

//test where a file exists
bool fileExist(
	const char * fname
,	bool del
){
	ifstream test(fname);
	if(test){
		cerr << "ERROR: curiously already a " << fname << " here in the folder!" << endl;
		if(del)
			removeFile(fname);
		return true;
	}else{
		test.close();
		return false;
	}
}

//usually one cannot expect a lot memory available for the training task
//so instead I write every feature onto the disk and then read in
//whenever necessary
float readFromDisk(
	char const * prefix
,	int index
,	int entry
){
	//hash
	char buffer[100];
	int unit = UNIT;
	sprintf(buffer, "%s/%s_%d_%d", STORAGE, prefix, index, entry/unit);
	const char * fname = buffer;
	ifstream fileIn(fname);
	string line;

	//with a reduced file size, it's ok to do this
	if(fileIn.is_open()){
		int localCoordinate = entry%unit;
	   	fileIn.seekg(ios_base::beg);
	   	for(int i = 0; i < localCoordinate; i++)
	   	    fileIn.ignore(numeric_limits<streamsize>::max(),'\n');
		//read in
		fileIn >> line;
		fileIn.close();
	}else{
		string message("unable to open ");
		fail(message+fname);
	}

	return atof(line.c_str());
}

//order definition for this type of pairs
//compare only the feature values
bool myPairOrder(
	const pair<float, int>& one
,	const pair<float, int>& other
){
	return one.first < other.first;
}

//read in a feature and put them in ascending order
//and record at the same time the permuted example order
vector< pair<float, int> > * writeOrganizedFeatures(int featureCount
,	int sampleCount
,	Row<float> *&featureVectors
){
	bool allInMemory = featureVectors == NULL ? false : true;
	vector< pair<float, int> > * toReturn = NULL;
	if(allInMemory){
		toReturn = new vector< pair<float, int> > [featureCount];
		cout << "INFO: store sorted ascending features in memory." << endl;
	}else
		cout << "INFO: store sorted ascending features in disk." << endl;

	//start sorting examples according to individual feature values
	times("");
	for(int feature = 0; feature < featureCount; feature++){
		vector< pair<float, int> > ascendingFeatures;
		//read in features from the disk or memory
		for(int sample = 0; sample < sampleCount; sample++){
			if(allInMemory)
				ascendingFeatures.push_back(make_pair(featureVectors[feature][sample], sample));
			else
				ascendingFeatures.push_back(make_pair(readFromDisk("FeatureVector", sample, feature), sample));
		}
		//sort
		sort(ascendingFeatures.begin(), ascendingFeatures.end(), myPairOrder);
		if(allInMemory){
			featureVectors[feature].resize(0);
			toReturn[feature] = ascendingFeatures;
		}else{
			//transfer to disk
            Row<float> permutedFeatures = zeros<Row<float>>(sampleCount);
            Row<float> permutedSamples = zeros<Row<float>>(sampleCount);
            for(int k = 0; k < sampleCount; k++){
				permutedFeatures(k) = ascendingFeatures[k].first;
				permutedSamples(k) = ascendingFeatures[k].second;
			}
			//write
			writeToDisk(permutedSamples, "OrganizedSample", feature);
			writeToDisk(permutedFeatures, "OrganizedFeatures", feature);
		}
	}
	times("featureReadingSorting");
	if(allInMemory)
		delete [] featureVectors;
	else
		removeFeatures(featureCount, sampleCount);
	return toReturn;
}

//remove either feature vectors
void removeFeatures(
	int featureCount
,	int sampleCount
){
	//here we delete feature vectors
	int unit = UNIT;
	int pieceCount = ceil(featureCount/(float)unit);
	for(int k = 0; k < sampleCount; k++){
		char buffer[100];
		const char * fname = buffer;
		for(int piece = 0; piece < pieceCount; piece++){
			sprintf(buffer, "%s/%s_%d_%d", STORAGE, "FeatureVector", k, piece);
			removeFile(fname);
		}
	}
}

void removeFile(const char * fname){
	if(remove(fname)){
		string message("Unable to delete ");
		fail(message+fname);
	}
}

//print some info of the feature
void whatFeature(int featureIndex){
	int * patternParam = Detector::getFeature(featureIndex);
	int pattern = patternParam[0];
	cout << "\tFeature: " << featureIndex;
	string graphicPattern;
	if(pattern == 1){
		cout << " Vertical Range: " << patternParam[3];
		cout << "  Horizontal Range: " << patternParam[4]+patternParam[5]+patternParam[6];
		graphicPattern = "\n\t11111111111111111100000000000000000\n\t11111111111111111100000000000000000\n";
	}else if(pattern == 2){
		cout << " Vertical Range: " << patternParam[3];
		cout << "  Horizontal Range: " << patternParam[4]+patternParam[5]+patternParam[6];
		graphicPattern = "\n\t11111111111100000000000011111111111\n\t11111111111100000000000011111111111\n";
	}else if(pattern == 3){
		cout << " Vertical Range: " << patternParam[3]+patternParam[4]+patternParam[5];
		cout << "  Horizontal Range: " << patternParam[6];
		graphicPattern = "\n\t11111111111111111111111111111111111\n\t00000000000000000000000000000000000\n";
	}else if(pattern == 4){
		cout << " Vertical Range: " << patternParam[3]+patternParam[4]+patternParam[5];
		cout << "  Horizontal Range: " << patternParam[6];
		graphicPattern = "\n\t11111111111111111111111111111111111\n\t00000000000000000000000000000000000\n\t11111111111111111111111111111111111\n";
	}else if(pattern == 5){
		cout << " Vertical Range: " << patternParam[3]+patternParam[4];
		cout << "  Horizontal Range: " << patternParam[6]+patternParam[5];
		graphicPattern = "\n\t11111111111111111000000000000000000\n\t00000000000000000111111111111111111\n";
	}else{
		graphicPattern = "ERROR  ERROR  ERROR";
	}
	int i = patternParam[1];
	int j = patternParam[2];
	cout << "  Computed at (" << i << ", " << j << ")\n" << graphicPattern << endl;
}
