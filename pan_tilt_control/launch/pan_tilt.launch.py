from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from launch.substitutions import Command
import os


def generate_launch_description():

    xacro_file = os.path.join(
        os.getenv('HOME'),
        'pan_tilt_ws/src/pan_tilt_description/urdf/pan_tilt.urdf.xacro'
    )

    robot_description = {
        'robot_description': Command(['xacro ', xacro_file])
    }

    return LaunchDescription([

        # Start Gazebo
        ExecuteProcess(
            cmd=['gz', 'sim', '-r'],
            output='screen'
        ),

        # Publish robot
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[robot_description],
            output='screen'
        ),

        # 🔥 CRITICAL: spawn robot
        Node(
            package='ros_gz_sim',
            executable='create',
            arguments=[
                '-topic', 'robot_description',
                '-name', 'pan_tilt'
            ],
            output='screen'
        ),

    ])