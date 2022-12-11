// SPDX-FileCopyrightText: 2022 Hiroto Horimoto
// SPDX-License-Identifier: BSD-3-Clause

#ifndef TRANSFORM_POINTCLOUD_HPP_
#define TRANSFORM_POINTCLOUD_HPP_

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <pcl_ros/transforms.hpp>
#include <tf2_eigen/tf2_eigen.h>

namespace transform_pointcloud
{
    class TransformPointcloudNode : public rclcpp::Node
    {
        using PointCloud2 = sensor_msgs::msg::PointCloud2;

    public:
        TransformPointcloudNode();

    private:
        rclcpp::Subscription<PointCloud2>::SharedPtr subscription_;
        rclcpp::Publisher<PointCloud2>::SharedPtr publisher_;

        PointCloud2::SharedPtr out_cloud_;

        std::string target_frame_;
        std::string topic_in_;
        std::string topic_out_;

        std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;

        void topic_callback(const PointCloud2::SharedPtr in_cloud_);
    };
}

#endif
