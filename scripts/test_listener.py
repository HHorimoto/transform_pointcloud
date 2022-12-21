#!/usr/bin/env python3

# SPDX-FileCopyrightText: 2022 Hiroto Horimoto
# SPDX-License-Identifier: BSD-3-Clause

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2

class TestSubscriber(Node):
    def __init__(self):
        super().__init__('test_subscriber')
        self.topic_name = self.declare_parameter('topic_name', 'tf_cloud').get_parameter_value().string_value
        self.subscription = self.create_subscription(PointCloud2, self.topic_name, self.listener_callback, 10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info("Run test succeeded")

def main(args=None):
    rclpy.init(args=args)
    node = TestSubscriber()
    rclpy.spin(node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()