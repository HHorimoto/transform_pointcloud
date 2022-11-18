cmake_minimum_required(VERSION 3.0.2)
project(transform_pointcloud)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  pcl_ros
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(transform_pointcloud_node src/transform_pointcloud_node.cpp)
target_link_libraries(transform_pointcloud_node
  ${catkin_LIBRARIES}
)
