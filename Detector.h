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
 * @file Detector.h
 * @brief face detector class
 * @author Yi-Qing WANG <yiqing.wang@polytechnique.edu>
 */

class Detector
{
    static int featureMap[][7];
    static int featureCount;
    static int sampleSize;
    static double stumps[][4];
    static int layerCount;
    static int layerCommitteeSize[];
    static float tweaks[];

public:
    Detector() {}
    ~Detector() {}

    static int * getFeature(int which)
    {
        return featureMap[which];
    }

    static int getFeatureCount()
    {
        return featureCount;
    }

    static int getSampleSize()
    {
        return sampleSize;
    }

    static double * getStumps(int which)
    {
        return stumps[which];
    }

    static int getLayerCount()
    {
        return layerCount;
    }

    static int getCommitteSize(int which)
    {
        return layerCommitteeSize[which];
    }

    static float getTweak(int which)
    {
        return tweaks[which];
    }

};
