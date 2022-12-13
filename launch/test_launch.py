import launch
import launch_ros.actions

def generate_launch_description():
    package_name = 'transform_pointcloud'
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package=package_name,
            executable='transform_pointcloud_node',
            name='transform_pointcloud_node',
            parameters=[{'target_frame':'base_link'},
                        {'topic_in':'/velodyne_points'},
                        {'topic_out':'/tf_cloud'}]
        ),
        launch_ros.actions.Node(
            package=package_name,
            executable='test.py',
            name='test',
            parameters=[{'topic_out':'/tf_cloud'}]
        )
    ])