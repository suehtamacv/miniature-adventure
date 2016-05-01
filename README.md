
**The Viola Jones Face Detection Algorithm**

WANG Yi-Qing, yiqing.wang@polytechnique.edu, ENS Cachan


List of Source Files
====================

This source code creates five command line programs. 

* *train.cpp*:			Commandline program that performs cascade training 

* *detect.cpp*: 		Commandline program that performs face detection 

* *TrainExamples.{cpp,h}*:	Implements a class for Adaboosting main routine: adaboost() 

* *Detector.{cpp,h}*:  		Implements a class for storing the trained cascade for face detection 

* *detectUtil.{cpp,h}*: 	Implements the main routine for face detection: scan() 

* *commonUtil.{cpp,h}*:  	Implements general utilities such as an Eigen wrapper for PNG image IO 

* *boostUtil.{cpp,h}*: 		Implements the main routine for cascade construction: train() 

* *io_png.{c.h}*:		Image input and output for PNG

* *startTraining.sh*: 		a bash script for cascade training. It creates several input files for train()

* *getParameters.sh*:		a bash script for monitoring the training process


Compiling
=========
  
The code has been tested with g++ 4.6.3 under Ubuntu and no warning or error was issued.

*libpng* is required as well as the Eigen library. The latter will be automatically downloaded when the code is compiled for the first time, which, however, requires  *wget* to work properly on your system. If it is not the case, please manually download the latest Eigen from its official website *http://eigen.tuxfamily.org/index.php?title=Main_Page*, unpack it, rename it to *eigen* and move it in the current folder.

To compile, type `make OMP=1` should the parallelization be enabled. Otherwise, simply type `make`.

RELEASE is the default mode in the makefile. However, VERSION can be set to DEBUG for testing. 

How to train a cascade
======================

Unpack the tarballs and issue ./startTraining.sh which will download the required dataset

When asked at the prompt

> start training right away? y/n

type *n* to defer the training run to a later time, in which case run the same script again and the required data and folders already in place will be used. Otherwise, type *y*.  

The learned cascade will be stored in *Detector.cxx*. To use it, rename it *Detector.cpp* and compile again.


Usage 
================

* To run the executable *train*, issue

> ./train > trainLog 2>&1 &

so that the training process is logged to trainLog. It may also be accessed with getParameters.sh, intended to summarize the overall training progress, including accumulated false positive rates at each layer and the committee size per layer.

* To run the executable *detect*, issue

> ./detect example.png [number of layers] [threshold]

where the first optional parameter defines the number of layers to be used in the cascade and the second denotes the robustness threshold introduced in the post-processing section of the article. These parameters default to 31 and 3. example.png refers to the image subject to face detection.

These explanatory instructions are also given if one simply types 

> ./detect

Its output includes

* rotated.png: because two rotated versions of the input image are also used to increase the detection rate, it is one of them and does not constitute a vital part of the final output.

* detectedraw.png: raw detection without the post-processing phase.

* ppRobust.png: the detected windows resulting from the robustness test described in the article applied to detectedraw.png.

* ppSkin.png: the detected windows resulting from the skin test described in the article applied to detectedraw.png.

* ppBoth.png: the detected windows resulting from the two previous tests applied to detectedraw.png. 

Face Detector
================

This source code implements a detector that scans all the square subwindows inside a given image 
and highlights those presumably having a face

This is an outline of how the face detection is performed in detectUtil.cpp:


scan(), detectUtil.cpp:     

    readInCascade() reads in a trained cascade classifier.

    All the image subwindows are tested by tscan().

    highlight() marks those detected faces.


tscan(), detectUtil.cpp:

    imread() reads in a gray image. 
    In case of a color image, the RGB to grayscale conversion is performed. 

    buildIntegralImage() computes the integral image and squared integral image 
    of the image to scan so as to accelerate its local sum and variance evaluation.

    The main loop examines all the square subwindows inside the image 

	area contains three parameters that characterizes a subwindow with
	(pos_i, pos_j) denoting its upper left corner's coordinates 

	If the subwindow has a standard deviation smaller than FLAT_THRESHOLD, 
	it is considered to be flat and thus labelled as a non-face. Otherwise
	detectFace() runs the subwindow through the cascade. 
	
	
detectFace(), detectUtil.cpp:

      An empty cascade considers all the subwindows to have a face.
	
      Otherwise, computeFeature() calculates the subwindow's features required by the 
      decision stumps in the first layer and a weighted vote determines its label. If
      it is declared to be a face, let this subwindow go to the next layer. If not, 
      reject the subwindow.


      

TrainExamples class  
====================

This part of the code implements training example collection and the Adaboost algorithm 
using the decision stump as its base learner. Note that here Adaboost does not produce a 
committee, it only adds one more stump to the committee, given the example weights at the
time. How many stumps are needed to form a committee is left to boostUtil.cpp


adaboost(), TrainExamples.cpp:

    Construct a new decision stump with bestStump().

    predictLabel() evaluates how the decision stump fares.

    The training examples' weights are adjusted depending on the outcome. 

    
TrainExamples(), TrainExamples.cpp:

    Positive examples are provided as a supplementary material, indexed by a variable called 
    positiveExamples. readImagesFromPathFile() helps read them in after tossing out those 
    blacklisted as false negative by all the previous cascade layers. In absence of such a cascade,
    all provided positives are used.
 
    sampleNegatives() takes negative examples from a large image pool made up of grayscale images 
    without human faces, in addition to the negatives (or false positives) left by the previous layers. 

    The training and validation examples are prepared differently: 
           
	All the positive training examples are assigned equal weight, positiveTotalWeight/nPositives
        at the outset. Similarly, (1-positiveTotalWeight)/nNegatives for negative training examples.

	The main loop calls computeHaarLikeFeatures() to calculate the training examples' Haar features. 

	writeOrganizedFeatures() then sorts these training examples in ascending order for each feature.
	Sorting is carried out because a decision stump can then be built in linear time.

	Since there is no need to run Adaboost on the validation pool, to save memory, only their integral
	images are calculated to facilitate the generalization error estimation at a later stage. 


sampleNegatives(), TrainExamples.cpp:

      readImagesFromPathFile() retrieves the existing good negatives, that is, false positives from the 
      previous layers. If there are not enough, negativeImagePaths is read in from which we expect
      to collect new negative examples so that the total number of false positives gets o nNegatives.

      tscan() is hence called to examine these negative images, if a false positive window larger than the example
      size is found, zoomOutNegative() tries to reduce its size so as to make it an acceptable example. If this
      shrunk version turns out be true negative, this larger window is rejected and the search continues.

      To avoid repeated detections on the images no longer able to provide good negatives, their entries are
      deleted from negativeImagePaths if it is determined to be the case. This operation is performed in the 
      routine's final loop.



Cascade Construction
=====================

This source code implements the multi-layer cascade designed to reduce false positive rate in an iterative fashion.


train(), boostUtil.cpp:

      The inner loop focuses on constructing a new layer whose false positive rate should be maintained below a
      targeted level under one constraint on the layer committee's size. If its committee can no longer grow, 
      the false positive rate is then allowed to rise without sacrificing too much the false negative rate. The 
      highlight of this part is the classifier shift selection. See the accompanying IPOL article for more details.

      The outer loop records the constructed layers and creates Detector.cpp.	
