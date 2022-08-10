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
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/transform_pointcloud.cpp)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
