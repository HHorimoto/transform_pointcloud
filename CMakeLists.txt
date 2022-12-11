cmake_minimum_required(VERSION 3.5)
project(transform_pointcloud)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_executable(${PROJECT_NAME} src/transform_pointcloud_node.cpp include/transform_pointcloud/transform_pointcloud_node.hpp)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_auto_package()
