// SPDX-FileCopyrightText: 2022 Hiroto Horimoto
// SPDX-License-Identifier: BSD-3-Clause

// Some lines are derived from https://github.com/KMiyawaki/rsj_pointcloud_test.
// Here is the original LICENSE for rsj_pointcloud_test.
// SPDX-FileCopyrightText: 2018 Atsushi Watanabe, Kenzaburo Miyawaki
// SPDX-License-Identifier: BSD-3-Clause

#include <transform_pointcloud/transform_pointcloud_node.h>

#include <pcl_ros/transforms.h>

namespace transform_pointcloud
{
    TransformPointcloudNode::TransformPointcloudNode() : nh_(), pnh_("~")
    {
        pnh_.param("topic_in", topic_in, std::string(""));
        pnh_.param("topic_out", topic_out, std::string(""));
        pnh_.param("target_frame", target_frame_, std::string(""));

        ROS_INFO("topic_in:[%s]", topic_in.c_str());
        ROS_INFO("topic_out:[%s]", topic_out.c_str());
        ROS_INFO("target_frame:[%s]", target_frame_.c_str());

        sub_points_ = nh_.subscribe(topic_in, 5, &TransformPointcloudNode::pcCallback, this);
        pub_transformed_ = nh_.advertise<PointCloud>(topic_out, 1);
        cloud_tranformed_.reset(new PointCloud());
    }
    TransformPointcloudNode::~TransformPointcloudNode(){}
    void TransformPointcloudNode::pcCallback(const PointCloud::ConstPtr &msg)
    {
        try
        {
            if (target_frame_.empty() == false)
            {
                if (pcl_ros::transformPointCloud(target_frame_, *msg, *cloud_tranformed_, tf_listener_) == false)
                {
                    ROS_ERROR("Failed pcl_ros::transformPointCloud target_frame:[%s]", target_frame_.c_str());
                    return;
                }
                pub_transformed_.publish(cloud_tranformed_);
            }
        }
        catch (std::exception &e)
        {
            ROS_ERROR("%s", e.what());
        }
    }
}

int main(int argc, char **argv)
{
    ROS_INFO("Started transform pointcloud");
    ros::init(argc, argv, "transform_pointcloud");

    transform_pointcloud::TransformPointcloudNode node;

    ros::spin();

    return 0;
}