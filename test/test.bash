#!/bin/bash

### Get rosbag ###
wget "https://drive.google.com/uc?export=download&id=1MtkzAMVezawFd92f-6CYOH20NQbUgHW3" -O rosbag.bag

### Run roscore in the background ###
roscore &

sleep 3

### Run test script ###
python ./test/test_scripts.py