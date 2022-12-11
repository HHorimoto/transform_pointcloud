import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='transform_pointcloud',
            executable='transform_pointcloud_node',
            name='transform_pointcloud_node',
            parameters=[{'target_frame':'base_link'},
                        {'topic_in':'/velodyne_points'},
                        {'topic_out':'/tf_cloud'}]
        )
    ])