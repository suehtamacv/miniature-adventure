#! /bin/bash
echo -e "\ncommittee size = \n"
cat trainLog | grep committee | sed 's:.*is \(.*\):\1,:g'
echo -e "\ntweak = \n"
cat trainLog | grep current | grep valid | sed 's:.*tweak \(.*\) has.*:\1,:g'
echo -e "\n there remain " $(cat noFaces | wc -l) "training images and " $(cat validNoFaces | wc -l) " validation images\n"
cat trainLog | grep Acc
cat trainLog | grep ERROR
echo -e $(cat trainLog | grep committee | wc -l) " rounds!"
