#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import PointCloud2


class Subscriber(Node):
    def __init__(self):
        super().__init__('subscriber')
        self.declare_parameter('topic_out', '/tf_cloud')
        self.subscription = self.create_subscription(
            PointCloud2,
            self.get_parameter('topic_out').get_parameter_value().string_value,
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.cnt = 0

    def listener_callback(self, msg):
        self.get_logger().info('I heard PointCloud2 msg. frame_id:[%s]' % msg.header.frame_id)
        self.get_logger().info('count=%d' % self.cnt)
        self.cnt += 1

def main(args=None):
    rclpy.init(args=args)

    subscriber = Subscriber()

    rclpy.spin(subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()