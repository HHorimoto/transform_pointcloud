# transform_pointcloud

**This package transforms point cloud from one link to the other link.**

![melodic workflow](https://github.com/HHorimoto/transform_pointcloud/actions/workflows/melodic.yml/badge.svg)
![noetic workflow](https://github.com/HHorimoto/transform_pointcloud/actions/workflows/noetic.yml/badge.svg)

## Requirement
+ ROS Melodic (on Ubuntu 18.04 LTS, build and run test on [Github Actions](./.github/workflows/melodic.yml))
+ ROS Noetic (on Ubuntu 20.04 LTS, build and run test on [Github Actions](./.github/workflows/noetic.yml))

## Set Up
1. Download `transform_pointcloud` package.

```shell
$ cd ~/catkin_ws/src/
$ git clone https://github.com/HHorimoto/transform_pointcloud.git
$ cd ~/catkin_ws
$ catkin_make
```

2. Download necessary package for this package.

```shell
$ sudo apt-get install ros-melodic-pcl-ros # for pcl_ros
```

## How to Use
Launch `transform_pointcloud.launch`

```shell
$ roslaunch transform_pointcloud transform_pointcloud.launch
```

### Parameters

+ ***topic_in*** : topic (`PointCloud2`) name that you want to transfom.
    default : `/camera/depth/color/points` (Realsense D435i)

+ ***topic_out*** : topic name after transform.
    default : `/tf_cloud`

+ ***target_frame*** : link name of transform target.
    default : `/base_link`

## Test
This package provides test bash for use with `Github Actions`.
This test confirms if `topic_out` is published or not by rosbag.
You can also do this test on your computer by following this command.
I belive that you can see `Success` not `Fail`.

```shell
$ roscd transform_pointcloud
$ bash -xv test/test_melodic.bash # or test_noetic.bash
# You can see result.
$ killall -9 rosmaster # kill roscore
```

## License

Distributed under the BSD-3-Clause License. See `LICENSE` for more information.