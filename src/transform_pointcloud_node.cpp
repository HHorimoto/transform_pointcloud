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

    RCLCPP_INFO(this->get_logger(), "target_frame:[%s], topic_i:[%s], topic_out:[%s]", target_frame_.c_str(), topic_in_.c_str(), topic_out_.c_str());

    publisher_ = this->create_publisher<PointCloud2>(topic_out_, 10);
    subscription_ = this->create_subscription<PointCloud2>(topic_in_, 10, std::bind(&TransformPointcloudNode::topic_callback, this, std::placeholders::_1));

    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    out_cloud_.reset(new PointCloud2());
  }
  void TransformPointcloudNode::topic_callback(const PointCloud2::SharedPtr in_cloud_)
  {
    try
    {
      if (target_frame_.empty() == false)
      {
        if (pcl_ros::transformPointCloud(target_frame_, *in_cloud_, *out_cloud_, *tf_buffer_) == false)
        {
          RCLCPP_ERROR(this->get_logger(), "Failed pcl_ros::transformPointCloud target_frame:[%s]", target_frame_.c_str());
          return;
        }
        out_cloud_->header.frame_id = target_frame_;
        publisher_->publish(*out_cloud_);
      }
    }
    catch (std::exception &e)
    {
      RCLCPP_ERROR(this->get_logger(), "%s", e.what());
    }
  }
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<transform_pointcloud::TransformPointcloudNode>());
  rclcpp::shutdown();
  return 0;
}
