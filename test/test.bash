#!/bin/bash

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

# Run Test #
timeout 10 roslaunch transform_pointcloud test.launch > test.log

## Test ##
grep "Run test succeeded" test.log