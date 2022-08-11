/**
 * transform_pointcloud
 *
 * Copyright 2018 Atsushi Watanabe, Kenzaburo Miyawaki
 * Copyright 2022 Hiroto Horimoto
 *
 * LICENSE is BSD
 **/

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

class TransformPointcloud
{
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;

    ros::Subscriber sub_points_;
    ros::Publisher pub_transformed_;
    tf::TransformListener tf_listener_;

    std::string target_frame_;
    PointCloud::Ptr cloud_tranformed_;

    void pcCallback(const PointCloud::ConstPtr &msg)
    {
        try
        {
            if (target_frame_.empty() == false)
            {
                if (pcl_ros::transformPointCloud(target_frame_, *msg, *cloud_tranformed_, tf_listener_) == false)
                {
                    ROS_ERROR("Failed pcl_ros::transformPointCloud target_frame:[%s]",target_frame_.c_str());
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

public:
    TransformPointcloud()
        : nh_()
        , pnh_("~")
    {
        std::string topic_in;
        std::string topic_out;
        pnh_.param("topic_in", topic_in, std::string(""));
        pnh_.param("topic_out", topic_out, std::string(""));
        pnh_.param("target_frame", target_frame_, std::string(""));

        ROS_INFO("topic_in:[%s]", topic_in.c_str());
        ROS_INFO("topic_out:[%s]", topic_out.c_str());
        ROS_INFO("target_frame:[%s]", target_frame_.c_str());

        sub_points_ = nh_.subscribe(topic_in, 5, &TransformPointcloud::pcCallback, this);
        pub_transformed_ = nh_.advertise<PointCloud>(topic_out, 1);
        cloud_tranformed_.reset(new PointCloud());
    }
};

int main(int argc, char** argv)
{
    ROS_INFO("Started transform pointcloud");
    ros::init(argc, argv, "transform_pointcloud");

    TransformPointcloud transform_pointcloud;

    ros::spin();

    return 0;
}