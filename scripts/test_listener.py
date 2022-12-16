#!/usr/bin/env python

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

import rospy
from sensor_msgs.msg import PointCloud2
import os

def callback(msg):
    rospy.loginfo("Run test succeeded")

def listener():
    script_name = os.path.basename(__file__)
    node_name = os.path.splitext(script_name)[0]
    rospy.init_node(node_name)

    topic_name = rospy.get_param('~topic_name', 'tf_cloud')
    rospy.Subscriber(topic_name, PointCloud2, callback)
    rospy.spin()
        
if __name__ == '__main__':
    listener()