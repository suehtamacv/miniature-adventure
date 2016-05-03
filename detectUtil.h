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
 * @file detectUtil.h
 * @brief header file for face detection routines
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

#include <armadillo>
#include <vector>
#include "TrainExamples.h"

using namespace arma;

struct rect
{
    int pos_i;
    int pos_j;
    int side;
};

/**
 * @brief convert a grayscale image to a RGB
 *
 * @param inputName which image
 * @param the return image's row numbers
 * @param the return image's column numbers
 * @return the converted image
 */
Mat<float> * convertToColor(
    const char * inputName
    ,	int & nRows
    ,	int & nCols
    ,	bool & isColor
);

/**
 * @brief cascade
 *
 * @param cascade returned cascade
 * @return tweaks that go with the cascade
 */
Row<float> readInCascade(
    vector<stumpRule> *& cascade
);

/**
 * @brief round the real number digit*scale
 *
 * @param digit
 * @param scale
 */
inline int round(
    int digit
    ,	double scale
);


/**
 * @brief toss out several more false positives and beautify the highlighting
 *
 * @param nRows
 * @param nCols
 * @param areas selected by the cascade and refined by postProcessing
 */
void postProcessing(
    int nRows
    ,	int nCols
    ,	float nFriends
    ,	vector<rect> & areas
);

/**
 * @brief highlight the faces so that we can see them
 *
 * @param inputName which image
 * @param areas where the found faces are
 */
void highlight(
    const char * inputName
    ,	vector<rect> & areas
    ,	int PPMode
    ,	float nFriends
);

/**
 * @brief detect face in an image subwindow
 *
 * @param area the subwindow's parameters
 * @param integralImage the whole image's integral image
 * @param varianceNormalizer for the image preprocessing
 * @param tweaks shifts applied to the cascade layers
 * @param cascade
 * @param defaultLayerNumber how many layers should be used
 * @return true if it's a face and false otherwise
 */
bool detectFace(
    rect const & area
    ,	Mat<double> & integralImage
    ,	double varianceNormalizer
    ,	Row<float> & tweaks
    ,	vector<stumpRule> const * cascade
    ,	int defaultLayerNumber
);

/**
 * @brief compute the feature from an image subwindow
 *
 * @param featureIndex which feature
 * @param area the subwindow in question
 * @param integralImage the whole image's integral image
 * @param removeMean in the preprocessing, shall we remove the subwindow's mean
 * @return the feature's numerical value
 */
double computeFeature(
    int featureIndex
    ,	rect const & area
    ,	Mat<double> & integralImage
    ,	bool removeMean
);

/**
 * @brief detect faces on an image
 *
 * @param file image name
 * @param defaultLayerNumber how many layers should be used
 */
void scan(
    const char * file
    ,	int defaultLayerNumber
    ,	float nFriends
);

/**
 * @brief convolute an image with a Gaussian kernel
 *
 * @param image
 * @param sigma the standard deviation of the kernel
 * @return via the image variable
 */
void gaussianSmoothing(
    Mat<float> * image
    ,		float sigma
);

/**
 * @brief calculate the gaussian density up to a constant
 *
 * @param 2 times Gaussian kernel's variance
 * @param ref the point on which the density is centered
 * @param cur the point for which the density shall be computed
 * @return the density up to a constant
 */
inline float gaussianKernel(
    float sigmaSquare
    ,		int ref
    ,		int cur
);

/**
 * @brief convolute row-wise an image with a Gaussian kernel
 *
 * @param image
 * @param Gaussian kernel's standard deviation
 * @param row which row
 * @param nRows the number of pixels in this row
 * @return the blurred image via the image variable
 */
void gaussianRowSmoothing(
    Mat<float> & image
    ,		float sigma
    ,		int row
    ,		int nRows
);

/**
 * @brief try to make an example out of a false positive window
 *
 * @param image a false positive window
 * @param default example size
 * @param defaultLayerNumber how many layers are there in the cascade
 * @param cascade
 * @param tweaks shifts applied to the cascade layers
 * @return true if image can be shrunk into a good sized false positive example (returned via the image variable) and false otherwise
 */
bool zoomOutNegative(
    Mat<float> *& image
    ,	int shrinkedSize
    ,	int defaultLayerNumber
    ,	vector<stumpRule> * cascade
    ,	Row<float> & tweaks
);

/**
 * @brief scan a standard example
 *
 * @param example a standard training or validation example
 * @param defaultLayerNumber how many layers are there in the cascade
 * @param cascade
 * @param tweaks shifts applied to the cascade layers
 * @return true if it's a face and false otherwise
 */
bool exampleScan(
    Mat<float> & example
    ,	int defaultLayerNumber
    ,	vector<stumpRule> const * cascade
    ,	Row<float> & tweaks
);

/**
 * @brief scan the whole image using a cascade
 *
 * @param file image
 * @param defaultLayerNumber how many layers are there in the cascade
 * @param cascade
 * @param tweaks shifts applied to the cascade layers
 * @param toMark the windows recognized as a face
 */
void tscan(
    const char * file
    ,	int & nRows
    ,	int & nCols
    ,	int defaultLayerNumber
    ,	vector<stumpRule> * cascade
    ,	Row<float> & tweaks
    ,	vector<rect> & toMark
);

/**
 * @brief compute Haar-like features with integral image
 *
 * @param integralImage its integral image
 * @param features all the features from this image
 * @param the order in which features are arranged are put in toFile
 * @param enforceShape the original Viola-Jones's proposal or more extensive definition of rectangle features (requires significantly more memory if disabled)
 * @param inTrain am I in the training mode
 */
void computeHaarLikeFeatures(
    Mat<float> & image
    ,		Row<float> *& features
    ,		const char * toFile
    ,		bool enforceShape
    ,		bool inTrain
);

void rotateCoordinate(
    int input_i
    ,	int input_j
    ,	int center_i
    ,	int center_j
    ,	float theta
    ,	int & output_i
    ,	int & output_j
);

void rotateImage(
    const char * infile
    ,	const char * outfile
    ,	float theta
    ,	int & center_i
    ,	int & center_j
);

bool isLegal(
    rect & area
    ,	int nRows
    ,	int nCols
);
