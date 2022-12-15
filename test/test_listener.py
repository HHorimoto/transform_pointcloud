#!/usr/bin/env python

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

import rospy
from sensor_msgs.msg import PointCloud2
from geometry_msgs.msg import PointStamped
from sensor_msgs.point_cloud2 import read_points
import math
import os
import tf

def transform_position(ps_list, source_link, target_link):
    listener = tf.TransformListener()
    ps = PointStamped() 
    ps.header.frame_id = target_link
    ps.header.stamp = rospy.Time()
    ps.point.x = ps_list[0]
    ps.point.y = ps_list[1]
    ps.point.z = ps_list[2]
    try:
        listener.waitForTransform(source_link, target_link, rospy.Time(), rospy.Duration(10))
        tf_ps = listener.transformPoint(source_link, ps)
    except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException) as e:
        raise e
    return tf_ps

def callback(msg):
    point = list(read_points(msg, skip_nans=False, field_names = ("x", "y", "z")))
    x = point[0][0]
    y = point[0][1]
    z = point[0][2]
    if not math.isnan(x) or not math.isnan(y) or not math.isnan(z):
        tf_ps = transform_position([rospy.get_param('~point_x'),rospy.get_param('~point_y'),rospy.get_param('~point_z')], 
                                    rospy.get_param('~target_frame'), rospy.get_param('~reference_frame'))
        if (round(tf_ps.point.x,4) == round(x,4) and round(tf_ps.point.y,4) == round(y,4) and round(tf_ps.point.z,4) == round(z,4)):
            rospy.loginfo("Run test succeeded")
        else:
            rospy.loginfo("Run test failed")

def listener():
    script_name = os.path.basename(__file__)
    node_name = os.path.splitext(script_name)[0]
    rospy.init_node(node_name)

    topic_name = rospy.get_param('~topic_name', 'tf_cloud')
    rospy.Subscriber(topic_name, PointCloud2, callback)
    rospy.spin()
        
if __name__ == '__main__':
    listener()