# HOW TO USE ON ROS1 (melodic and noetic)

## Set Up
1. Download necessary package for this package.

```shell
$ sudo apt-get install ros-$ROS_DISTRO-pcl-ros # for pcl_ros
```

2. Download `transform_pointcloud` package.

```shell
$ cd ~/catkin_ws/src/
$ git clone https://github.com/HHorimoto/transform_pointcloud.git
$ cd ~/catkin_ws
$ catkin_make
$ source ~/.bashrc
```

## Launch
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
This test confirms if msg is published or not.
You can also do this test on your computer by following this command.

```shell
$ roscd transform_pointcloud
$ bash -xv test/test.bash
$ echo $?
0 # It means success. if the number is "1", it means failure. 
```