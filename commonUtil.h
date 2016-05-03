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
 * @file commonUtil.h
 * @brief header file for common image IO routines
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <string>
#include <vector>
#include <utility>
#include <armadillo>

using namespace std;
using namespace arma;

/**
 * @brief print an error message and then quit
 */
void fail(string const & message);

/**
 * @brief timer
 */
void times(const char * which);

/**
 * @brief read in fileName as it is or gray
 *
 * @param fileName path of the image to read in
 * @param nRows number of image rows
 * @param nCols number of image columns
 * @param nChannels number of image channels
 * @param outputGray read in as gray
 * @return image format image as a matrix
 */
void imread(
    const char * fileName
    ,	int & nRows
    ,	int & nCols
    ,	int & nChannels
    ,	Mat<float> *& image
    ,	bool outputGray
);

/**
 * @brief write out an image as PNG
 *
 * @param fileName path of the image to read in
 * @param nRows number of image rows
 * @param nCols number of image columns
 * @param nChannels number of image channels
 * @param outputGray read in as gray
 * @return image format image as a matrix
 */
void imwrite(
    const char * fileName
    , 		Mat<float> * image
    , 		int nChannels
);

/**
 * @brief integral image in linear time
 *
 * @param image original image
 * @return integralImage integral image
 */
void buildIntegralImage(
    Mat<float> & image
    ,	Mat<double> & integralImage
);

/**
 * @brief sum up the pixels in a sub-rectangle of the image
 *
 * @param integralImage its integral image
 * @param ui row index of this sub-rectangle's up left corner
 * @param uj column index of this sub-rectangle's up left corner
 * @param ir number of rows of this sub-rectangle
 * @param jr number of columns of this sub-rectangle
 * @return the sum
 */
long double sumImagePart(
    Mat<double> & integralImage
    ,	int ui
    ,	int uj
    ,	int ir
    ,	int jr
);


/**
 * @brief format pathFile so that it's more readable
 *
 * @param pathFile paths to images
 * @param addr char array
 * @param blackList delete those in the blackList before formatting
 * @param sign POSITIVE or NEGATIVE
 * @return number of samples collected
 */
int pathFile2charArray(
    const char * pathFile
    ,	char **& addr
    ,	Row<int> * blackList
    ,	int sign
);

/**
 * @brief read in images in the pathFile
 *
 * @param pathFile paths to images
 * @param blackList delete those in the blackList before formatting
 * @param sign POSITIVE or NEGATIVE
 * @return images
 * @return number of samples collected
 */
int readImagesFromPathFile(
    const char * pathFile
    ,	Mat<float> ** & images
    ,	Row<int> * blackList
    ,	int sign
);

/**
 * @brief write a vector to the external disk
 *
 * @param dataVector the vector itself
 * @param prefix
 * @param index which
 */
void writeToDisk(
    Row<float> & dataVector
    ,	char const * prefix
    ,	int index
);

/**
 * @brief read a vector entry from data files
 *
 * @param prefix which vector content
 * @param index which vector
 * @param entry which entry in the vector
 * @return feature value of this example
 */
float readFromDisk(
    char const * prefix
    ,	int index
    ,	int entry
);

/**
 * @brief an auxiliary function for pair ordering
 */
bool myPairOrder(
    const pair<float, int>& one
    ,	const pair<float, int>& other
);

/**
 * @brief test whether fname's already there
 *
 * @param fname which file
 * @param del delete this unexpected file
 * @return true if so, false otherwise
 */
bool fileExist(
    const char * fname
    ,	bool del = true
);

/**
 * @brief sort every feature and write them out in ascending order
 *
 * @param featureCount
 * @param sampleCount
 * @param if you choose to read features from memory instead of disk
 */
vector< pair<float, int> > * writeOrganizedFeatures(
    int featureCount
    ,	int sampleCount
    ,	Row<float> * & featureVectors
);

/**
 * @brief remove all the traces
 *
 * @param featureCount
 * @param sampleCount
 */
void removeFeatures(
    int featureCount
    ,	int sampleCount
);

void removeFile(const char * fname);

/**
 * @brief print some additional information about this feature
 */
void whatFeature(int feature);

#endif
