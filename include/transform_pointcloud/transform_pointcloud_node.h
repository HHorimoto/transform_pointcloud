// SPDX-FileCopyrightText: 2022 Hiroto Horimoto
// SPDX-License-Identifier: BSD-3-Clause

#ifndef TRANSFORM_POINTCLOUD_H__
#define TRANSFORM_POINTCLOUD_H__

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

namespace transform_pointcloud
{
    class TransformPointcloudNode
    {
    public:
        TransformPointcloudNode();
        ~TransformPointcloudNode();

        std::string topic_in;
        std::string topic_out;

    private:
        ros::NodeHandle nh_;
        ros::NodeHandle pnh_;

        ros::Subscriber sub_points_;
        ros::Publisher pub_transformed_;
        tf::TransformListener tf_listener_;

        std::string target_frame_;
        PointCloud::Ptr cloud_tranformed_;

        void pcCallback(const PointCloud::ConstPtr &msg);
    };
}

#endif // TRANSFORM_POINTCLOUD_H__