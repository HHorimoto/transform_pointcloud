cmake_minimum_required(VERSION 3.5)
project(transform_pointcloud)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#-- Dependencies
find_package(ament_cmake REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_ros REQUIRED)


#--- for C++
add_executable(transform_pointcloud_node src/transform_pointcloud_node.cpp)
ament_target_dependencies(transform_pointcloud_node pcl_ros geometry_msgs sensor_msgs rclcpp tf2 tf2_eigen tf2_ros)
install(TARGETS transform_pointcloud_node DESTINATION lib/${PROJECT_NAME})
target_include_directories(transform_pointcloud_node
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)
#--- end C++

#-- for Python
ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/test.py
  DESTINATION lib/${PROJECT_NAME}
)
#--- end Python

ament_package()
