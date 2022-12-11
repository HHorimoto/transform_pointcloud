// SPDX-FileCopyrightText: 2022 Hiroto Horimoto
// SPDX-License-Identifier: BSD-3-Clause

#include <transform_pointcloud/transform_pointcloud_node.hpp>

namespace transform_pointcloud
{
  TransformPointcloudNode::TransformPointcloudNode() : Node("transform_pointcloud_node")
  {
    target_frame_ = declare_parameter("target_frame", "base_link");
    topic_in_ = declare_parameter("topic_in", "/velodyne_points");
    topic_out_ = declare_parameter("topic_out", "/tf_cloud");

    publisher_ = this->create_publisher<PointCloud2>(topic_out_, 10);
    subscription_ = this->create_subscription<PointCloud2>(topic_in_, 10, std::bind(&TransformPointcloudNode::topic_callback, this, std::placeholders::_1));

    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    out_cloud_.reset(new PointCloud2());
  }
  void TransformPointcloudNode::topic_callback(const PointCloud2::SharedPtr in_cloud_)
  {
    geometry_msgs::msg::TransformStamped transform_stamped;
    try
    {
      transform_stamped = tf_buffer_->lookupTransform(target_frame_, in_cloud_->header.frame_id, tf2::TimePointZero);
    }
    catch (tf2::TransformException &ex)
    {
      RCLCPP_WARN(this->get_logger(), "Could not transform %s to %s: %s", target_frame_.c_str(), in_cloud_->header.frame_id.c_str(), ex.what());
      return;
    }
    Eigen::Matrix4f mat = tf2::transformToEigen(transform_stamped.transform).matrix().cast<float>();
    pcl_ros::transformPointCloud(mat, *in_cloud_, *out_cloud_);
    out_cloud_->header.frame_id = target_frame_;
    publisher_->publish(*out_cloud_);
  }
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<transform_pointcloud::TransformPointcloudNode>());
  rclcpp::shutdown();
  return 0;
}
