#!/bin/bash

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

### Run test launch.py ###
timeout 10 ros2 launch transform_pointcloud test_launch.py > test.log

### Confirme Test ###
cat test.log | grep 'count=10'