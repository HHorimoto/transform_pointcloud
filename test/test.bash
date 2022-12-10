#!/bin/bash

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

### Confirm ros distro ###
echo $ROS_DISTRO

### Get rosbag ###
wget "https://drive.google.com/uc?export=download&id=1MtkzAMVezawFd92f-6CYOH20NQbUgHW3" -O rosbag.bag

### Run roscore in the background ###
roscore &

sleep 3

### Run test script ###
if [ $ROS_DISTRO = 'melodic' ]; then
    python ./test/test_melodic.py
elif [ $ROS_DISTRO = 'noetic' ]; then
    python3 ./test/test_noetic.py
else
    echo "Other"
    echo 1
fi