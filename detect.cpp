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
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "detectUtil.h"
#include "train_neural.h"
#include <floatfann.h>

using namespace std;

#define MIN_FRIENDS 3
#define MAX_COLS 300
#define MAX_ROWS 400

float *identify_face(cv::Mat frame, rect fL);

int main()
{
    //train_neural();

    int defaultLayerNumber = -1;
    float required_nFriends = MIN_FRIENDS;

    cv::namedWindow("FrameOriginal");
    cv::namedWindow("RostosDetectados");
    cv::startWindowThread();

    while (true)
        {
        cv::Mat frame;

            {
            cv::VideoCapture stream1(0);
            stream1.read(frame);
            stream1.read(frame);
            stream1.release();
            }
        frame = cv::imread("test4.jpg");

#ifdef MUST_RESIZE
        int nCols = 0, nRows = 0;

        if (frame.cols > frame.rows)
            {
            nCols = std::min(frame.cols, MAX_COLS);
            nRows = (frame.rows / (double) frame.cols) * nCols;
            }
        else
            {
            nRows = std::min(frame.rows, MAX_ROWS);
            nCols = (frame.cols / (double) frame.rows) * nRows;
            }

        cv::resize(frame, frame, cv::Size(nCols, nRows), 0, 0, CV_INTER_CUBIC);
#endif
        cv::imwrite("frame.png", frame);

        vector<rect> faces = scan("frame.png", defaultLayerNumber, required_nFriends);

        for (rect face : faces)
            {
            cv::rectangle(frame, cv::Point(face.pos_j, face.pos_i),
                          cv::Point(face.pos_j+face.side, face.pos_i+face.side),
                          cv::Scalar(0, 255, 0), 2);
            float* id = identify_face(frame, face);
            std::cout << id[0] << "\t" << id[1] << "\t" << id[2] << std::endl;

            if ((id[0] > id[1]) && (id[0] > id[2]) && (id[0] > 0))
                {
                cv::putText(frame, "Matheus", cv::Point(face.pos_j, face.pos_i-3), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
                }
            else if ((id[1] > id[0]) && (id[1] > id[2]) && (id[1] > 0))
                {
                cv::putText(frame, "Sara", cv::Point(face.pos_j, face.pos_i-3), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
                }
            else if ((id[2] > id[0]) && (id[2] > id[1]) && (id[2] > 0))
                {
                cv::putText(frame, "Outro", cv::Point(face.pos_j, face.pos_i-3), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
                }
            }

        cv::imshow("FrameOriginal", cv::imread("frame.png"));
        cv::imshow("RostosDetectados", frame);
        }
    return 0;
}

float* identify_face(cv::Mat frame, rect fL)
{
    if ((fL.pos_i + fL.side < frame.cols) && (fL.pos_j+fL.side < frame.rows))
        {
        cv::Mat face = frame(cv::Range(fL.pos_i,fL.pos_i+fL.side),
                             cv::Range(fL.pos_j,fL.pos_j+fL.side)).t();
        cv::cvtColor(face, face, CV_RGB2GRAY);
        cv::resize(face, face, cv::Size(32,32), 0, 0, CV_INTER_CUBIC);
        face.reshape(1, 1024);

        std::vector<float> image;
        image.assign(face.datastart, face.dataend);

        double summ = 0;
        for (auto &pixel : image)
            {
            summ += pixel;
            }
        for (auto &pixel : image) pixel /= summ;

        struct fann *ann = fann_create_from_file("Neural.net");
        return fann_run(ann, image.data());
        }
    else
        {
        float *a = new float[3];
        a[0] = a[1] = a[2] = -1;
        return a;
        }
}
