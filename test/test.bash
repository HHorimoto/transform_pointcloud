#!/bin/bash

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

# Run Test #
timeout 10 roslaunch transform_pointcloud test.launch > test.log

## Test 1 ##
grep "Run test failed" test.log
reslt=(`echo $?`)
if [ $reslt = 0 ]; then
    echo "Run test failed"
    exit 1
fi

## Test 2 ##
grep "Run test succeeded" test.log
reslt=(`echo $?`)
if [ $reslt = 0 ]; then
    echo "Run test succeeded"
    exit 0
else
    echo "Run test failed"
    exit 1
fi