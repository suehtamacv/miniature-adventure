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

#define ARMA_NO_DEBUG

#include <iostream>
#include <sstream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "detectUtil.h"

using namespace std;

#define MIN_FRIENDS 3
#define MAX_COLS 240
#define MAX_ROWS 320

int main()
{
    int defaultLayerNumber = -1;
    float required_nFriends = MIN_FRIENDS;

    cv::Mat image = cv::imread("test.png");
    int nCols = 0, nRows = 0;

    if (image.cols > image.rows)
        {
        nCols = std::min(image.cols, MAX_COLS);
        nRows = (image.rows / (double) image.cols) * nCols;
        }
    else
        {
        nRows = std::min(image.rows, MAX_ROWS);
        nCols = (image.cols / (double) image.rows) * nRows;
        }

    cv::resize(image, image, cv::Size(nCols, nRows), 0, 0, CV_INTER_CUBIC);
    cv::imwrite("resize.png", image);

    scan("resize.png", defaultLayerNumber, required_nFriends);

    return 0;
}
