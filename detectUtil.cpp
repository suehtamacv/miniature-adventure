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
 * @file detectUtil.cpp
 * @brief common routines for face detection
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <functional>
#include "connected.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>
#include <streambuf>
#include <cstdio>
#include "commonUtil.h"
#include "detectUtil.h"
#include "Detector.h"

#define FOLLOW_VJ true
#define PEN_WIDTH 3
#define STD_NORM_CONST 1e4
#define FLAT_THRESHOLD 1
#define EXAMPLE_SIZE 24
#define ROTATE_DEGREE 5
#define WINDOW_SCALE_MULTIPLIER 1.5

using namespace std;
using namespace arma;

//smooth a square image by row and then by column
void gaussianSmoothing(Mat<float> *image
,		float sigma
){
    int nRows = image[0].n_rows;
	#pragma omp parallel for schedule(static)
	for(int row = 0; row < nRows; row++)
		gaussianRowSmoothing(image[0], sigma, row, nRows);
    Mat<float> imageMatrix = image[0].t();
	#pragma omp parallel for schedule(static)
	for(int row = 0; row < nRows; row++)
		gaussianRowSmoothing(imageMatrix, sigma, row, nRows);
    image[0] = imageMatrix.t();
}

inline float gaussianKernel(
		float sigmaSquare
,		int ref
,		int cur
){
	return exp(-1*pow((float)ref-cur, 2)/sigmaSquare);
}

//row-wise convolution
void gaussianRowSmoothing(Mat<float> &image
,		float sigma
,		int row
,		int nRows
){
	int width = ceil(sigma);
	float sigmaSquare = pow(sigma, 2)*2;
	//temporary storage for convolution
    Row<float> container(nRows);
	#pragma omp parallel for schedule(static)
	for(int k = 0; k < nRows; k++){
		//kernel position
		int left = max(0, k-width);
		int right = min(nRows-1, k+width);
		int vectSize = right-left+1;
		//kernel value
        Row<float> weights(vectSize);
		for(int i = left; i <= right; i++)
			weights(i-left) = gaussianKernel(sigmaSquare, k, i);
        weights /= accu(weights);
		//convolution
        container(k) = accu(image.row(row).cols(left, left+vectSize-1) % weights);
	}
	//modify
	image.row(row) = container;
}

//zoom out a square negative to the desired size and test if it remains a good negative
bool zoomOutNegative(Mat<float> *&image
,	int shrinkedSize
,	int defaultLayerNumber
,	vector<stumpRule> * cascade
,	Row<float> &tweaks
){
    int windowSize = image[0].n_rows;
	//if it's the right size, this is a good one
	if(shrinkedSize == windowSize)
		return true;
	//convolute with a Gaussian kernel and then downsample
	float ratio = (float)windowSize/(float)shrinkedSize;
	//this is an empirical formula
	float sigma = 0.6*sqrt(pow(ratio, 2) - 1);
	gaussianSmoothing(image, sigma);
    Mat<float> zoomed(shrinkedSize, shrinkedSize);
	int imSize = pow((float)shrinkedSize, 2);
	//an efficient parallelization for downsampling
	#pragma omp parallel for schedule(static)
	for(int count = 0; count < imSize; count++){
		int row = count/shrinkedSize;
		int col = count%shrinkedSize;
		float embedRowPos = (float)(windowSize-1)/(float)(shrinkedSize+1)*(float)(row+1);
		float embedColPos = (float)(windowSize-1)/(float)(shrinkedSize+1)*(float)(col+1);
		//let's see where it is
		int lowRow = max((int)floor(embedRowPos), 0);
		int upRow = min(lowRow+1, windowSize-1);
		int lowCol = max((int)floor(embedColPos), 0);
		int upCol = min(lowCol+1, windowSize-1);
		//take the average of its four neighbors
		zoomed(row, col) = (image[0](lowRow, lowCol) + image[0](lowRow, upCol) + image[0](upRow, lowCol) + image[0](upRow, upCol))/4;
	}
	//release
	delete [] image;
	//zoom isn't necessarily the same after imwrite() and imread()
	//because of the induced quantification and truncation
    image = new Mat<float> [1];
	image[0] = zoomed;
	imwrite("robustTest.png", image, 1);
	int nRows, nCols, nChannels;
	imread("robustTest.png", nRows, nCols, nChannels, image, true);
	//test
	if(exampleScan(image[0], defaultLayerNumber, cascade, tweaks))
		return true;
	else{
		delete [] image;
		return false;
	}
}

//build a cascade from Detector object
Row<float> readInCascade(
	vector<stumpRule> *& cascade
){
	//allocate
	int layerCount = Detector::getLayerCount();
	cascade = new vector<stumpRule> [layerCount];
    Row<float> tweaks = zeros<Row<float>>(layerCount);
    int linearCounter = 0;
	//this should be done in a linear fashion
	for(int layer = 0; layer < layerCount; layer++){
		int committeeSize = Detector::getCommitteSize(layer);
		tweaks[layer] = Detector::getTweak(layer);
		for(int member = 0; member < committeeSize; member++){
			double * rule = Detector::getStumps(linearCounter);
			//set a new stump
			stumpRule newcomer;
			newcomer.featureIndex = rule[0];
			newcomer.weightedError = rule[1];
			newcomer.threshold = rule[2];
			newcomer.toggle = rule[3];
			cascade[layer].push_back(newcomer);
			linearCounter++;
		}
	}
	return tweaks;
}

//convert a gray to a RGB for highlighting
Mat<float> *convertToColor(
	const char * inputName
,	int & nRows
,	int & nCols
,	bool & isColor
){
	int nChannels;
    Mat<float> * original = NULL;
	imread(inputName, nRows, nCols, nChannels, original, false);
	//always output a color image
	isColor = true;
	if(nChannels == 1){
		isColor = false;
        Mat<float> copy(nRows, nCols);
		copy = original[0];
		delete [] original;
        original = new Mat<float> [3];
		for(int ch = 0; ch < 3; ch++)
			original[ch] = copy;
	}
	return original;
}

//check whether the pixel is part of skin
bool isSkinPixel(
	int row
,	int col
,	Mat<float> * image
){
	int R = image[0](row, col);
	int G = image[1](row, col);
	int B = image[2](row, col);
    int diff = std::max(R, max(G, B))- std::min(R, min(G, B));
	return R > 95 && G > 40 && B > 20 && R > G && R > B && R-G > 15 && diff > 15;
}

bool hasEnoughSkin(
    Mat<float> * image
,	rect area
){
	int cornerI = area.pos_i;
	int cornerJ = area.pos_j;
	int side = area.side;
	int nSkinPixels = 0;
	for(int i = cornerI; i < cornerI + side; i++)
		for(int j = cornerJ; j < cornerJ + side; j++)
			if(isSkinPixel(i, j, image))
				nSkinPixels++;
	//threshold set according to the reference
	return nSkinPixels/(float)(side*side) > 0.4;
}

//four post-processing mode:
//0: no post-processing
//1: only robustness test
//2: only skin color test
//3: both robustness and skin color test
void augmentedPostProcessing(
    Mat<float> * image
,	int nRows
,	int nCols
,	bool isColor
,	float required_nFriends
,	vector<rect> & areas
,	int ppMode
){
	if(ppMode == 0)
		return;
	if(ppMode == 1 || !isColor)
		postProcessing(nRows, nCols, required_nFriends, areas);
	else{
		//both
		if(ppMode == 3)
			postProcessing(nRows, nCols, required_nFriends, areas);
		//skin test
		int nWindows = areas.size();
        vector<rect> temp;
		for(int i = 0; i < nWindows; i++)
			if(hasEnoughSkin(image, areas[i]))
				temp.push_back(areas[i]);
		areas = temp;
	}
}

//highlight a rectangle part of an image
void highlight(
	const char * inputName
,	vector<rect> & areas
,	int ppMode
,	float required_nFriends
){
	int nRows, nCols;
	bool isColor;
    Mat<float> * original = convertToColor(inputName, nRows, nCols, isColor);
	int nSquares = areas.size();
	//no detection, no post-processing
	ppMode = nSquares == 0 ? 0 : ppMode;
	augmentedPostProcessing(original, nRows, nCols, isColor, required_nFriends, areas, ppMode);
	nSquares = areas.size();
	for(int k = 0; k < nSquares; k++){

		//take the parameters
		int cornerI = areas[k].pos_i;
		int cornerJ = areas[k].pos_j;
		int side = areas[k].side;

		//I'm working with a color image, and always highlight with green
		for(int i = cornerI; i < cornerI + side; i++)
			for(int j = cornerJ; j < cornerJ + side; j++){
				bool paint = false;
				if( abs(cornerI + PEN_WIDTH/2 -i) <= PEN_WIDTH/2 && abs(cornerJ + side/2 - j) <= side/2 )
					paint = true;
				else if(abs(cornerI + side - 1 - PEN_WIDTH/2 - i) <= PEN_WIDTH/2 && abs(cornerJ + side/2 - j) <= side/2)
					paint = true;
				else if( abs(cornerJ + PEN_WIDTH/2 -j) <= PEN_WIDTH/2 && abs(cornerI + side/2 - i) <= side/2)
					paint = true;
				else if(abs(cornerJ + side - 1 - PEN_WIDTH/2 - j) <= PEN_WIDTH/2 && abs(cornerI + side/2 - i) <= side/2)
					paint = true;
				if(paint){
					original[0](i,j) = 0;
					original[1](i,j) = 255;
					original[2](i,j) = 0;
				}
			}
	}

	//output
	if(ppMode == 0)
		imwrite("detectedraw.png", original, 3);
	else if(ppMode == 1)
		imwrite("ppRobust.png", original, 3);
	else if(ppMode == 2)
		imwrite("ppSkin.png", original, 3);
	else
		imwrite("ppBoth.png", original, 3);
}

//look at a subwindow and use the trained cascade to reject or accept it
bool detectFace(rect const & area
,	Mat<double> &integralImage
, 	double varianceNormalizer
,	Row<float> &tweaks
,	vector<stumpRule> const * cascade
,	int defaultLayerNumber
){
	//everything is a face if no layer is involved
	if(defaultLayerNumber == 0)
		return true;
	//now to the cascade: you may choose the number of layers used in the detection
	int layerCount = defaultLayerNumber < 0 ? tweaks.size() : defaultLayerNumber;
	for(int layer = 0; layer < layerCount; layer++){
		vector<stumpRule> committee = cascade[layer];
		double prediction = 0;
		int committeeSize = committee.size();
		for(int rule = 0; rule < committeeSize; rule++){
			double featureValue = computeFeature(committee[rule].featureIndex, area, integralImage, true)/varianceNormalizer;
			double vote = (featureValue > committee[rule].threshold ? 1 : -1)*committee[rule].toggle+tweaks[layer];
			if(committee[rule].weightedError == 0){
				//very well then
				if(rule == 0)
					return vote > 0 ? true : false;
				else
					fail("Find an invalid rule.");
			}
			//no 0.5 since only sign matters
			prediction += vote*log(1/committee[rule].weightedError -1);
		}
		if(prediction < 0)
			return false;
	}
	return true;
}

inline int round(
	int digit
,	double scale
){
	return digit*scale+0.5;
}

//return feature computed on a scaled image
double computeFeature(int featureIndex
,	rect const & area
,	Mat<double> &integralImage
,	bool removeMean
){
	static int sampleSize = Detector::getSampleSize();
	double scale = area.side/(double)sampleSize;
	double mean = removeMean ? sumImagePart(integralImage, area.pos_i, area.pos_j, area.side, area.side)/pow((float)area.side, 2) : 0;

	//all about this feature
	int * featureInfo = Detector::getFeature(featureIndex);
	//it can be shown that (i,j) remains in area
	//cout << "feature info " << featureInfo[1] << " , " << featureInfo[2] << endl;
	int i = round(featureInfo[1], scale);
	int j = round(featureInfo[2], scale);
	//cout << "i " << i << " j " << j << endl;
	//translated coordinate
	int absolute_i = area.pos_i + i;
	int absolute_j = area.pos_j + j;
	int pattern = featureInfo[0];
	//learned feature dimension
	//pattern 1 and pattern 2 norHeight featureInfo[3]
	//pattern 5 norHeight featureInfo[3] + featureInfo[4]
	//pattern 3 and pattern 4 norHeight featureInfo[3] + featureInfo[4] + featureInfo[5]
	int norHeight = pattern <= 2 ? featureInfo[3] : featureInfo[3] + featureInfo[4];
	norHeight += pattern > 2 && pattern < 5 ? featureInfo[5] : 0;
	//pattern 3 and pattern 4 norWidth featureInfo[6]
	//pattern 5 norHeight featureInfo[5] + featureInfo[6]
	//pattern 1 and pattern 2 norWidth featureInfo[4] + featureInfo[5] + featureInfo[6]
	int norWidth = pattern <= 2 ? featureInfo[4] + featureInfo[5] + featureInfo[6] : featureInfo[6];
	norWidth += pattern == 5 ? featureInfo[5] : 0;
	//original pattern size
	double originalFeatureSurface = norHeight*norWidth;
	//scaled dimension which may still undergo some change
	int height = round(norHeight, scale);
	int width = round(norWidth, scale);

	//compute the feature
	double feature = 0;
	if(pattern == 1){
		//some adjustment to height and width
        height = std::min(height, area.side - i);
		width = width % 2 == 0 ? width : width + 1;
		while(width + j > area.side)
			width -= 2;
		int increment = width/2;
		//cout << absolute_i << ", " << absolute_j << " height " << height << " width " << width << endl;
		feature += sumImagePart(integralImage, absolute_i, absolute_j, height, increment);
		feature -= sumImagePart(integralImage, absolute_i, absolute_j+increment, height, increment);
		//scale the feature
		double scaleAgain = (double)(height*width)/originalFeatureSurface;
		feature /= scaleAgain;
	}else if(pattern == 2){
		//some adjustment
        height = std::min(height, area.side - i);
		int remainder = width % 3;
		width = remainder == 0 ? width : width + 3 - remainder;
		while(width + j > area.side)
			width -= 3;
		int increment = width/3;
		feature += sumImagePart(integralImage, absolute_i, absolute_j, height, increment);
		feature -= sumImagePart(integralImage, absolute_i, absolute_j+increment, height, increment);
		feature += sumImagePart(integralImage, absolute_i, absolute_j+2*increment, height, increment);
		//add mean back
		feature -= mean*height*increment;
		//scale the feature
		double scaleAgain = (double)(height*width)/originalFeatureSurface;
		feature /= scaleAgain;
	}else if(pattern == 3){
		//some adjustment
        width = std::min(width, area.side - j);
		height = height % 2 == 0 ? height : height + 1;
		while(height + i > area.side)
			height -= 2;
		int increment = height/2;
		feature += sumImagePart(integralImage, absolute_i, absolute_j, increment, width);
		feature -= sumImagePart(integralImage, absolute_i+increment, absolute_j, increment, width);
		//scale the feature
		double scaleAgain = (double)(height*width)/originalFeatureSurface;
		feature /= scaleAgain;
	}else if(pattern == 4){
		//some adjustment
        width = std::min(width, area.side - j);
		int remainder = height % 3;
		height = remainder == 0 ? height : height + 3 - remainder;
		while(height + i > area.side)
			height -= 3;
		int increment = height/3;
		feature += sumImagePart(integralImage, absolute_i, absolute_j, increment, width);
		feature -= sumImagePart(integralImage, absolute_i+increment, absolute_j, increment, width);
		feature += sumImagePart(integralImage, absolute_i+2*increment, absolute_j, increment, width);
		//add mean back
		feature -= mean*width*increment;
		//scale the feature
		double scaleAgain = (double)(height*width)/originalFeatureSurface;
		feature /= scaleAgain;
	}else{
		//some adjustment
		width = width % 2 == 0 ? width : width + 1;
		height = height % 2 == 0 ? height : height + 1;
		while(height + i > area.side)
			height -= 2;
		while(width + j > area.side)
			width -= 2;
		int iIncrement = height/2;
		int jIncrement = width/2;
		feature += sumImagePart(integralImage, absolute_i, absolute_j, iIncrement, jIncrement);
		feature -= sumImagePart(integralImage, absolute_i+iIncrement, absolute_j, iIncrement, jIncrement);
		feature -= sumImagePart(integralImage, absolute_i, absolute_j+jIncrement, iIncrement, jIncrement);
		feature += sumImagePart(integralImage, absolute_i+iIncrement, absolute_j+jIncrement, iIncrement, jIncrement);
		//scale the feature
		double scaleAgain = (double)(height*width)/originalFeatureSurface;
		feature /= scaleAgain;
	}
	return feature;
}

//a simplified interface for detectFace()
bool exampleScan(
    Mat<float> & example
,	int defaultLayerNumber
,	vector<stumpRule> const * cascade
,	Row<float> & tweaks
){
	//look at this example's variance
    int nRows = example.n_rows;
    double std = sqrt(accu(example % example)/pow((float)nRows, 2) - pow(accu(example)/pow((float)nRows, 2), 2));
    if(std::isnan(std) || std < FLAT_THRESHOLD)
		return false;
	//compute its integral image if this image is not flat
    Mat<double> integralImage(nRows, nRows);
	buildIntegralImage(example, integralImage);
	//it's about the whole thing
    rect area;
	area.pos_i = 0;
	area.pos_j = 0;
	area.side = nRows;
	//now up to the cascade
 	return detectFace(area, integralImage, std/STD_NORM_CONST, tweaks, cascade, defaultLayerNumber);
}


//main routine
void scan(
	const char * file
,	int defaultLayerNumber
,	float required_nFriends
){
	//read in cascade
	vector<stumpRule> * cascade = NULL;
    Row<float> tweaks = readInCascade(cascade);
    vector<rect> toMark, combined;
	//scan the file
	int nRows, nCols;
	tscan(file, nRows, nCols, defaultLayerNumber, cascade, tweaks, combined);
	float theta = ROTATE_DEGREE/180.*M_PI;
	int center_i, center_j;
	for(int bf = 1; bf < 3; bf++){
		float curTheta = pow(-1.,bf)*theta;
		rotateImage(file, "rotated.png", curTheta, center_i, center_j);
		tscan("rotated.png", nRows, nCols, defaultLayerNumber, cascade, tweaks, toMark);
		int num = toMark.size();
		for(int k = 0; k < num; k++)
			rotateCoordinate(toMark[k].pos_i, toMark[k].pos_j, center_i, center_j, curTheta, toMark[k].pos_i, toMark[k].pos_j);
		combined.reserve(combined.size() + toMark.size());
		combined.insert(combined.end(), toMark.begin(), toMark.end());
		toMark.resize(0);
	}
	delete [] cascade;
	//due to rotation, the coordinates might not be legal
	for(int i = 0; i < (int)combined.size(); i++)
		if(isLegal(combined[i], nRows, nCols))
			toMark.push_back(combined[i]);
	//four modes of post-processing
	for(int ppMode = 0; ppMode < 4; ppMode++){
		combined = toMark;
		highlight(file, combined, ppMode, required_nFriends);
	}
}

void tscan(const char * file
,	int & nRows
,	int & nCols
,	int defaultLayerNumber
,	vector<stumpRule> * cascade
,	Row<float> &tweaks
,	vector<rect> & toMark
){
	//build integral image and squared integral image
	int nChannels;
    Mat<float> * toDetect = NULL;
	imread(file, nRows, nCols, nChannels, toDetect, true);
    Mat<double> integralImage(nRows, nCols);
	buildIntegralImage(toDetect[0], integralImage);
    Mat<float> toDetectSquared = toDetect[0] % toDetect[0];
	delete [] toDetect;
    Mat<double> integralImageSquare(nRows, nCols);
	buildIntegralImage(toDetectSquared, integralImageSquare);
	//get down to the business
	int sampleSize = Detector::getSampleSize();
	int possibleULCorners = (nRows - sampleSize + 1)*(nCols - sampleSize + 1);
	#pragma omp parallel for schedule (static)
	for(int ij = 0; ij <= possibleULCorners; ij++){
		int i = ij/(nCols - sampleSize + 1);
		int j = ij%(nCols - sampleSize + 1);
		double scale = 1;
        rect area;
		area.pos_i = i;
		area.pos_j = j;
		area.side = sampleSize;
		//multiple scale detection
		while(i+area.side <= nRows && j+area.side <= nCols){
			//compute variance
			double variance = sumImagePart(integralImageSquare, i, j, area.side, area.side)/pow((float)area.side, 2);
			variance -= pow(sumImagePart(integralImage, i, j, area.side, area.side)/pow((float)area.side, 2), 2);
			double std = sqrt(variance);
            if(!(std::isnan(std) || std < FLAT_THRESHOLD)){
 				if(detectFace(area, integralImage, std/STD_NORM_CONST, tweaks, cascade, defaultLayerNumber)){
					#pragma omp critical
					{
 						toMark.push_back(area);
					}
				}
			}
			//next scale
			scale *= WINDOW_SCALE_MULTIPLIER;
			area.side = round(sampleSize, scale);
		}
	}
}

bool isLegal(
    rect & area
,	int nRows
,	int nCols
){
	int i = area.pos_i;
	int j = area.pos_j;
	if(i < 0 || i > nRows-1 || j < 0 || j > nCols-1)
		return false;
	i += area.side - 1;
	j += area.side - 1;
	if(i < 0 || i > nRows-1 || j < 0 || j > nCols-1)
		return false;
	else
		return true;
}

bool windowOrder(
    rect window1
,	rect window2
){
	return window1.side < window2.side;
}

bool isInside(
    rect window1
,	rect window2
){
	int iy = window1.pos_i + window1.side/2;
	int ix = window1.pos_j + window1.side/2;
	return ( iy > window2.pos_i && iy < window2.pos_i + window2.side && ix > window2.pos_j && ix < window2.pos_j + window2.side );
}

//post-processing. Based on several robustness criteria, this shall manage
//to further remove a number of false positives and beautify the final result
void postProcessing(
	int nRows
,	int nCols
,	float required_nFriends
,	vector<rect> & areas
){
    Mat<int> partition = zeros<Mat<int>>(nRows, nCols);
    int nWindows = areas.size();
	//already a decision has been made
	sort(areas.begin(), areas.end(), windowOrder);
	for(int w = 0; w < nWindows; w++)
		partition(areas[w].pos_i, areas[w].pos_j) = areas[w].side;
	//let a connected component algorithm run
	int nPixels = nRows*nCols;
	int * connectedParts = new int [nPixels];
	ConnectedComponents cc(10);
        cc.connected( partition.mem, connectedParts, nRows, nCols, std::equal_to<int>(), true );
	//how many disconnected parts and how big are they
	vector<int> myVector(connectedParts, connectedParts+nPixels);
	sort(myVector.begin(), myVector.end());
	vector<int> partCount;
	partCount.push_back(1);
	vector<int> partIndex;
	partIndex.push_back(myVector[0]);
	int nowAt = myVector[0];
	int count = 0;
	for(int i = 1; i < nPixels; i++)
		if(nowAt != myVector[i]){
			nowAt = myVector[i];
			partIndex.push_back(nowAt);
			partCount.push_back(1);
			count += 1;
		}else
			partCount[count] += 1;
	//work out the indexed square's size and eliminate windows at the same time
	nowAt += 1;
	vector<bool> flags;
	flags.resize(nowAt);
	for(int i = 0; i < nowAt; i++)
		flags[i] = true;
    Mat<int> fineParts(connectedParts, nRows, nCols);
    vector<rect> representatives;
	vector<float> ratios;
	for(int w = 0; w < nWindows; w++){
		int part = fineParts(areas[w].pos_i, areas[w].pos_j);
		if(flags[part]){
			//inverse mapping
			for(count = 0; partIndex[count] != part; count++) ;
			int nFriends = partCount[count];
			if(nFriends > required_nFriends*areas[w].side/(float)EXAMPLE_SIZE){
				representatives.push_back(areas[w]);
				ratios.push_back((float)nFriends/areas[w].side);
			}
			flags[part] = false;
		}
	}
	delete [] connectedParts;
	//now remove the duplicates, a worst case polynominal process but not expensive
	//note that representatives are still ordered
	int nRepresentatives = representatives.size();
	flags.resize(nRepresentatives);
	//everyone is assumed to be a good representative at this stage
	for(int r = 0; r < nRepresentatives; r++)
		flags[r] = true;
	for(int r = 0; r < nRepresentatives; r++)
		for(int br = r+1; br < nRepresentatives; br++){
			if(flags[br] && isInside(representatives[r], representatives[br])){
				if(ratios[r] > ratios[br]){
					flags[br] = false;
				}else{
					flags[r] = false;
					break;
				}
			}
		}
	//gather the good ones
	areas.resize(0);
	for(int r = 0; r < nRepresentatives; r++)
		if(flags[r])
			areas.push_back(representatives[r]);
}


//compute features using integral image technique
//feature order doesn't matter for all training samples
//because they will be calculated in eactly the same way
//also create the featureMap in a file named cppName
//inTrain sets training phase apart from testing phase
void computeHaarLikeFeatures(
        Mat<float> & image
,		Row<float> *& features
,		const char * cppName
,		bool enforceShape
,		bool firstTime
){
	if(firstTime){
		cout << "\n#############################ABOUT THE FEATURES TO SELECT FROM################################################\n\n";
		if(FOLLOW_VJ){
			cout << "\nINFO: Follow Viola-Jones strictly in feature computation: 2 vertical, 2 horizontal and 1 mixed features\n";
			cout << "INFO: Moreover black white rectangles in a pattern are always set to the same size\n\n";
		}else{
			cout << "\nINFO: Follow my way in feature computation: 2 horizontal, 1 vertical and 1 mixed features\n";
			cout << "INFO: But black white rectangles are not necessarily of the same size as long as the pattern is symmetric as a whole.\n\n";
		}
		ofstream output(cppName);
		output << "#include \"Detector.h\"" << endl;
		output << "int Detector::featureMap[][7]={\n";
		output.close();
	}


	//integral image
    int nRows = image.n_rows;
    int nCols = image.n_cols;
	//first normalize the example, this might prove key to learning success
    float mean = accu(image)/(float)(nRows*nCols);
    image -= mean;
    float std = sqrt(accu(image % image)/(float)(nRows*nCols));
	if(std < FLAT_THRESHOLD || isnan(std)){
		std = FLAT_THRESHOLD;
		cout << "Find one completely flat example. Don't worry. It'll be treated as an outlier presumably." << endl;
	}
	//fully use the float range
	image *= STD_NORM_CONST;
	image /= std;
    Mat<double> integralImage(nRows, nCols);
	buildIntegralImage(image, integralImage);

	//determine the size of a feature vector
	//as well as the features with a stack
	stack<float> stack;

	//this portion should not use OPENMP for the order matters
	//the used patterns follow from the doc
	//no optimisation is done here, though it's certainly possible.
	//two horizontal patterns
	int pattern_no = 0;
	for(int portions = 2; portions < 4; portions++){
		//pattern starts from 1
		pattern_no++;
		//up left coordinate
		for(int i = 0; i < nRows; i++)
		for(int j = 0; j < nCols; j++){
			//how long can l1 be
			int l1MIN = portions == 2 ? 0 : 1;
			int l1MAX = portions == 2 ? 0 : nCols - j;
			//height
			for(int ir = 1; ir <= nRows - i; ir++)
				for(int l1 = l1MIN; l1 <= l1MAX; l1++)
				for(int l2 = 1; l2 <= nCols-j-l1; l2++)
				for(int l3 = 1; l3 <= nCols-j-l1-l2; l3++){
					//make these lengths more intelligible
                    Row<int> lengths;
                    lengths << l1 << l2 << l3;

					//now go for the feature
					float feature = 0;
					if(portions == 2){
						if(enforceShape && l2 != l3)
							continue;
						feature += (float)sumImagePart(integralImage, i, j, ir, l2);
						feature -= (float)sumImagePart(integralImage, i, j+l2, ir, l3);
					}else{
						if(enforceShape && FOLLOW_VJ && !(l1 == l3 && l1 == l2))
							continue;
						if(enforceShape && !FOLLOW_VJ && !(l1 == l3 && l1 >= l2))
							continue;
						for(int k = 0; k < 3; k++){
							int factor = pow(-1., k);
                            int advance = k == 0 ? 0 : accu(lengths.head(k));
							feature += factor*(float)sumImagePart(integralImage, i, j+advance, ir, lengths[k]);
						}
					}

					//store
					stack.push(feature);
					if(firstTime){
						ofstream output;
						output.open(cppName, ios_base::app);
						output << "{"<<pattern_no <<","<<i<<","<<j<<","<<ir<<","<<lengths[0]<<","<<lengths[1]<<","<<lengths[2]<<"},\n";
						output.close();
					}
				}
		}
		if(firstTime)
			cout << "INFO: Pattern 1 to Pattern " << pattern_no << " accumulate " << stack.size() << " features." << endl;
	}

	//two vertical patterns: if you go my way, only one vertical pattern
	for(int portions = 2; portions < 4; portions++){
		pattern_no++;
		//up left coordinate
		for(int i = 0; i < nRows; i++)
		for(int j = 0; j < nCols; j++){
			int l1MIN = portions == 2 ? 0 : 1;
			int l1MAX = portions == 2 ? 0 : nRows - i;
			//width
			for(int jr = 1; jr <= nCols-j; jr++)
				for(int l1 = l1MIN; l1 <= l1MAX; l1++)
				for(int l2 = 1; l2 <= nRows-i-l1; l2++)
				for(int l3 = 1; l3 <= nRows-i-l1-l2; l3++){
					//make these lengths more intelligible
                    Row<int> lengths;
                    lengths << l1 << l2 << l3;

					//now go for the feature
					float feature = 0;
					if(portions == 2){
						if(enforceShape && !(l2 == l3))
							continue;
						feature += (float)sumImagePart(integralImage, i, j, l2, jr);
						feature -= (float)sumImagePart(integralImage, i+l2, j, l3, jr);
					}else{
						if(enforceShape && FOLLOW_VJ && !(l1 == l2 && l1 == l3))
							continue;
						//if(enforceShape && FOLLOW_VJ)
						if(enforceShape && !FOLLOW_VJ)
							continue;
						for(int k = 0; k < 3; k++){
							int factor = pow(-1., k);
                            int advance = k == 0 ? 0 : accu(lengths.head(k));
							feature += factor*(float)sumImagePart(integralImage, i+advance, j, lengths[k], jr);
						}
					}

					//store
					stack.push(feature);
					if(firstTime){
						ofstream output;
						output.open(cppName, ios_base::app);
						output << "{"<<pattern_no <<","<<i<<","<<j<<","<<lengths[0]<<","<<lengths[1]<<","<<lengths[2]<<","<<jr<<"},\n";
						output.close();
					}
				}
		}
		if(firstTime)
			cout << "INFO: Pattern 1 to Pattern " << pattern_no << " accumulate " << stack.size() << " features." << endl;
	}

	//a mixed pattern
	pattern_no++;
	for(int i = 0; i < nRows; i++)
	for(int j = 0; j < nCols; j++)
		for(int i_l1 = 1; i_l1 < nRows - i; i_l1++)
		for(int i_l2 = 1; i_l2 <= nRows - i - i_l1; i_l2++)
		for(int j_l1 = 1; j_l1 < nCols - j; j_l1++)
		for(int j_l2 = 1; j_l2 <= nCols - j - j_l1; j_l2++){
			if(enforceShape && !(i_l1 == i_l2 && j_l1 == j_l2))
				continue;
			float feature = 0;
			feature += (float)sumImagePart(integralImage, i, j, i_l1, j_l1);
			feature -= (float)sumImagePart(integralImage, i, j + j_l1, i_l1, j_l2);
			feature -= (float)sumImagePart(integralImage, i + i_l1, j, i_l2, j_l1);
			feature += (float)sumImagePart(integralImage, i + i_l1, j + j_l1, i_l2, j_l2);

			//record
			stack.push(feature);
			if(firstTime){
				ofstream output;
				output.open(cppName, ios_base::app);
				output << "{"<<pattern_no <<","<<i<<","<<j<<","<<i_l1<<","<<i_l2<<","<<j_l1<<","<<j_l2<<"},\n";
				output.close();
			}
		}

	int featureCount = stack.size();
	if(firstTime){
		cout << "INFO: Pattern 1 to Pattern " << pattern_no << " accumulate " << stack.size() << " features." << endl;
		//tell you what, there is no other portable way to delete the last comma than this
		ifstream fileIn(cppName);
		//read in
		string content((istreambuf_iterator<char>(fileIn)),istreambuf_iterator<char>());
		fileIn.close();
		//no longer needed
		removeFile(cppName);
		//remove the last comma
		content.erase(content.size()-2);
		//write again
		ofstream fileOut(cppName);
		fileOut << content << "\n};";
		fileOut << "\nint Detector::featureCount=" << featureCount << ";";
		fileOut << "\nint Detector::sampleSize=" << nRows << ";";
		fileOut.close();
	}

	//put all the features into a single vector
    features = new Row<float>[1];
    features[0] = zeros<Row<float>>(featureCount);
	//count down rather than up because of stack
	for(int k = featureCount -1; k >= 0; k-- ){
		features[0](k) = stack.top();
		stack.pop();
	}
}

void rotateCoordinate(
	int input_i
,	int input_j
,	int center_i
,	int center_j
,	float theta
,	int & output_i
,	int & output_j
){
    Mat<float> rotMatrix(2,2);
    rotMatrix << cos(theta) << sin(theta) << endr
              << -1*sin(theta) << cos(theta);
    Col<float> coordinate;
    coordinate << input_j - center_j << input_i - center_i;
	coordinate = rotMatrix*coordinate;
	output_i = coordinate(1) + center_i;
	output_j = coordinate(0) + center_j;
}

void rotateImage(
	const char * infile
,	const char * outfile
,	float theta
,	int & center_i
,	int & center_j
){
	int nRows, nCols, nChannels;
    Mat<float> * image = NULL;
	imread(infile, nRows, nCols, nChannels, image, true);
	int imsize = nRows*nCols;
    Mat<float> * rotated = new Mat<float> [1];
    rotated[0] = zeros<Mat<float>>(nRows, nCols);
	center_i = nRows/2;
	center_j = nCols/2;
	#pragma omp parallel for schedule(static)
	for(int ij = 0; ij < imsize; ij++){
		int i = ij/nCols;
		int j = ij%nCols;
		int si, sj;
		rotateCoordinate(i, j, center_i, center_j, theta, si, sj);
		if(!(i < 0 || i > nRows-1 || j < 0 || j > nCols-1 || si < 0 || si > nRows-1 || sj < 0 || sj > nCols-1))
			rotated[0](i,j) = image[0](si, sj);
	}
	//write out
	imwrite(outfile, rotated, 1);
	delete [] image;
}

