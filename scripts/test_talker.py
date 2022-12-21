#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

import rclpy
from rclpy.node import Node
from std_msgs.msg import Header
from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs_py import point_cloud2


class TestPublisher(Node):
    def __init__(self):
        super().__init__('test_publisher')
        self.topic_name = self.declare_parameter('topic_name', 'points').get_parameter_value().string_value
        self.frame_id = self.declare_parameter('frame_id', 'foo_link').get_parameter_value().string_value
        self.x = self.declare_parameter('x', 1.0).get_parameter_value().double_value
        self.y = self.declare_parameter('y', 1.0).get_parameter_value().double_value
        self.z = self.declare_parameter('z', 1.0).get_parameter_value().double_value
        self.publisher_ = self.create_publisher(PointCloud2, self.topic_name, 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        header = Header(frame_id=self.frame_id)
        fields = [PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
                  PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
                  PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1),]
        points = [[self.x, self.y, self.z],]
        points_cloud = point_cloud2.create_cloud(header, fields, points)
        self.publisher_.publish(points_cloud)

def main(args=None):
    rclpy.init(args=args)
    node = TestPublisher()
    rclpy.spin(node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()