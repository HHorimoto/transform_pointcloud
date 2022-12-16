#!/usr/bin/env python

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

import rospy
from std_msgs.msg import Header
from sensor_msgs.msg import PointCloud2, PointField
import sensor_msgs.point_cloud2 as pc2
import os

class TestPublisher(object):
    def __init__(self, topic_name, frame_id, x, y, z):
        self.topic_name = topic_name
        self.frame_id = frame_id
        self.publisher = rospy.Publisher(self.topic_name, PointCloud2, queue_size=1)
        self.x = x
        self.y = y
        self.z = z

    def spin(self):
        header = Header(frame_id=self.frame_id)
        fields = [PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
                  PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
                  PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1),]
        points = [[self.x, self.y, self.z],]
        points_cloud = pc2.create_cloud(header, fields, points)
        self.publisher.publish(points_cloud)

def main():
    script_name = os.path.basename(__file__)
    node_name = os.path.splitext(script_name)[0]
    rospy.init_node(node_name)
    topic_name = rospy.get_param('~topic_name', 'points')
    reference_frame = rospy.get_param('~reference_frame', 'foo_link')
    point_x = rospy.get_param('~point_x', 1.0)
    point_y = rospy.get_param('~point_y', 1.0)
    point_z = rospy.get_param('~point_z', 1.0)
    rate = rospy.Rate(5)
    node = TestPublisher(topic_name, reference_frame, point_x, point_y, point_z)
    while not rospy.is_shutdown():
        node.spin()
        rate.sleep()

if __name__ == '__main__':
    main()