#!/bin/bash

###################################################################
## this script downloads the dataset, compiles the code base
## and launches the adaboost learning algorithm.
## It is intended to be run in the bash environment.
###################################################################


# a utility function that checks duplicate entries shared by two files

function showCommon {

	result=$(diff $1 $2 --new-line-format="" --old-line-format="" --unchanged-line-format="%L" | wc -l)
	if [ $result -gt 0 ]
	then
		echo "Error: there is an example used by both $1 and $2."
		exit
	fi

}

# download the whole dataset from my webpage
# this dataset comprises many images without human faces, from which we draw negative examples
# and two existing positive and negative example base obtained from University of Washington

if [ ! -d facedata ]
then
	echo -e "\nI'm going to download the required dataset. It may take several minutes...\n"
	echo -e "\nIf wget doesn't work on your system, please download the tarball manually by following the link.\n"
	wget http://dev.ipol.im/~yiqing/facedata.tar.gz
	tar xfz facedata.tar.gz
fi

# noFaces and validNoFaces document those images without human faces
# for training and validation purposes respectively

find $PWD/facedata/trainImages -type f | sort > noFaces
find $PWD/facedata/validImages -type f | sort > validNoFaces

# all the rest deals with the existing examples, not images
# split those existing examples for training and validation

if [ ! -d examples ]
then
	mkdir faces
	mv $(ls facedata/faces/*png | sort | head -3000) faces
	mkdir nonfaces
	mv $(ls facedata/nonfaces/*png | sort | head -5000) nonfaces
	mkdir train
	mv nonfaces faces train

	mkdir test
	mv facedata/faces facedata/nonfaces test

	mkdir examples
	mv test train examples
fi

# bookkeeping which results in four text files with the suffix allIhave
# this won't change. The next step allows you to decide who will be used in the training

testP="test_positives"
testN="test_negatives"
trainP="positives"
trainN="negatives"
original="allIhave"
toUse="txt"

if [ ! -f "$trainP.$original" ]
then
	for set in $(find $PWD -maxdepth 2 -mindepth 2 -type d | grep examples)
	do
		if [[ $set == *test* ]]
		then
			negative="$testN.$original"
			positive="$testP.$original"
		else
			negative="$trainN.$original"
			positive="$trainP.$original"
		fi
		for dir in $(find $set -mindepth 1 -type d)
		do
			echo -e "\nI'm now in $dir"
			if [[ $dir == *non* ]]
			then
				echo -e "Creating Negative Paths ..."
				find $dir -type f | sort > $negative
				echo -e "$(cat $negative | wc -l) samples recorded in $negative!\n"
			else
				echo -e "Creating Positive Paths ..."
				find $dir -type f | sort > $positive
				echo -e "$(cat $positive | wc -l) samples recorded in $positive!"
			fi
		done
	done
fi

# create pathfiles actually required by my cpp code
# so that the algorithm knows where to get data if it is needed

psize=1000
nsize=1000
tpsize=1000
tnsize=1000

# you can comment out the next four lines to have a say on the previous four parameters

# read -p "how many positives among $(cat $trainP.$original | wc -l) for learning in training? " psize
# read -p "how many negatives among $(cat $trainN.$original | wc -l) for learning in training? " nsize
# read -p "how many positives among $(cat $testP.$original | wc -l) for validation in training? " tpsize
# read -p "how many negatives among $(cat $testN.$original | wc -l) for validation in training? " tnsize

# extract a few lines

sed -n 1,${psize}p $trainP.$original > $trainP.$toUse
sed -n 1,${nsize}p $trainN.$original > $trainN.$toUse
sed -n 1,${tpsize}p $testP.$original > $testP.$toUse
sed -n 1,${tnsize}p $testN.$original > $testN.$toUse

#sanity check so there's no example with two or more roles

showCommon $trainN.$toUse $testN.$toUse
showCommon $trainN.$toUse $trainP.$toUse
showCommon $trainN.$toUse $testP.$toUse
showCommon $trainP.$toUse $testP.$toUse
showCommon $trainP.$toUse $testN.$toUse
showCommon $testN.$toUse $testP.$toUse

# create a folder for negative example storage

read -p "start training right away? y/n " answer

if [[ $answer == *y* ]]
then
	ncn=newlyCollectedNegatives
	echo -e "\nCreate an empty $ncn to record negatives seen in the training process."
	if [ -d "$ncn" ]
	then
		rm -rf $ncn
	fi
	mkdir $ncn

	# the environment is ok now. Let's compile

	echo -e "\nStart Compiling\n"
	make clean
	make OMP=1
	echo -e "\nready to go. The training process is logged to trainLog\n"
	./train > trainLog 2>&1 &
else
	echo -e "\ndataset ready. If you want to start training, run ./startTraining.sh again\n"
fi
