from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    baud_rate = LaunchConfiguration('baud_rate')
    device = LaunchConfiguration('device')
    simulation = LaunchConfiguration('simulation')

    controlled_qube_xacro = PathJoinSubstitution([
        FindPackageShare('qube_bringup'),
        'urdf',
        'controlled_qube.urdf.xacro'
    ])

    robot_description = Command([
        'xacro ',
        controlled_qube_xacro,
        ' baud_rate:=', baud_rate,
        ' device:=', device,
        ' simulation:=', simulation
    ])

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': robot_description
        }]
    )

    rviz_config = PathJoinSubstitution([
        FindPackageShare('qube_description'),
        'rviz',
        'default.rviz'
    ])

    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', rviz_config]
    )

    qube_driver_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('qube_driver'),
                'launch',
                'qube_driver.launch.py'
            ])
        ),
        launch_arguments={
            'baud_rate': baud_rate,
            'device': device,
            'simulation': simulation
        }.items()
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'baud_rate',
            default_value='115200',
            description='Serial baud rate for Qube communication'
        ),
        DeclareLaunchArgument(
            'device',
            default_value='/dev/ttyACM0',
            description='Serial device for physical Qube'
        ),
        DeclareLaunchArgument(
            'simulation',
            default_value='false',
            description='Use simulator instead of physical Qube'
        ),
        qube_driver_launch,
        robot_state_publisher_node,
        rviz_node
    ])