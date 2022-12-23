# HOW TO USE ON ROS2 (foxy)

## Set Up
1. Download necessary package for this package.

```shell
$ cd ~/ros2_ws/src/
$ git clone https://github.com/ros-perception/perception_pcl.git -b foxy-devel
$ cd ~/ros2_ws
$ colcon build
$ source ~/.bashrc
```

2. Download `transform_pointcloud` package.

```shell
$ cd ~/ros2_ws/src/
$ git clone https://github.com/HHorimoto/transform_pointcloud.git -b foxy-devel
$ cd ~/ros2_ws
$ colcon build --allow-overriding pcl_conversions
$ source ~/.bashrc
```

## Launch 
Launch `transform_pointcloud.launch.xml`

```shell
$ ros2 launch transform_pointcloud transform_pointcloud.launch.xml
```

### Parameters

+ ***topic_in*** : topic (`PointCloud2`) name that you want to transfom.
    default : `velodyne_points`

+ ***topic_out*** : topic name after transform.
    default : `tf_cloud`

+ ***target_frame*** : link name of transform target.
    default : `base_link`

## Test
This package provides test bash for use with `Github Actions`.
This test confirms if msg is published or not.
You can also do this test on your computer by following this command.

```shell
$ cd ros2_ws/src/transform_pointcloud/
$ bash -xv test/test.bash
$ echo $?
0 # It means success. if the number is "1", it means failure. 
```
