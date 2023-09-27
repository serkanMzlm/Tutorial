from launch import LaunchDescription
from launch_ros.actions import Node 

publisher_node = Node(
    package="cpp_topic",
    executable="publisher_node",
)

subscriber_node = Node(
    package="cpp_topic",
    executable="subscriber_node",
)

def generate_launch_description():
    # ld = LaunchDescription()
    # ld.add_action(publisher_node)
    # ld.add_action(subscriber_node)
    # return ld
    return LaunchDescription([
        publisher_node,
        subscriber_node
    ])