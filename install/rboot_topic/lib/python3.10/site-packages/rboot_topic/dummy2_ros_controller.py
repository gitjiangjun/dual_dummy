#!/usr/bin/env python3

import rclpy
import rclpy.action
from rclpy.node import Node
from control_msgs.action import FollowJointTrajectory, GripperCommand
from trajectory_msgs.msg import JointTrajectoryPoint
from sensor_msgs.msg import JointState
import time
from std_msgs.msg import UInt8
from sensor_msgs.msg import JointState
from rboot_libs import rbootlibs
from rboot_interface.msg import RbootPosition
import struct
import math


class Dummy2ArmControllerServer(rclpy.action.ActionServer):
    def __init__(self, node):
        super().__init__(node, FollowJointTrajectory, 'dummy2_arm_controller/follow_joint_trajectory', self.execute_callback)
        self._node = node
        self._node.get_logger().info("Dummy2 Arm Controller Server started")

        self.client = rbootlibs.UDPClient('192.168.8.88', 9999)
        self.client.connect()
        self.pub = self._node.create_publisher(RbootPosition, "/controller_status", 10)
        self.sub = self._node.create_subscription(
            RbootPosition, "/position", self.send_position, 10)
        self.sub = self._node.create_subscription(
            UInt8, "/loop", self.set_loop, 10)

        self.client.start_receive_thread()
        self.register_cb()

        # Create a publisher for /joint_states
        self.joint_state_publisher = self._node.create_publisher(JointState, '/joint_states', 10)

        # Store the joint names from the first received goal
        self.joint_names = ['joint2', 'joint1', 'joint4', 'joint5', 'joint6', 'joint3', 'figer1', 'figer2']

        # Initialize current point with eight zeros
        self.current_point = JointTrajectoryPoint()
        self.current_point.positions = [0.0] * 8
        self.current_point.velocities = [60.0] * 8
        # self.current_point.efforts = [float('nan')] * 8

        # Create a timer to publish joint states every 10 ms
        self.timer = self._node.create_timer(0.01, self.timer_callback)

        # Initialize GripperActionServer
        self.gripper_action_server = GripperActionServer(self._node)

    async def execute_callback(self, goal_handle):
        self._node.get_logger().info("Received new goal")
        feedback_msg = FollowJointTrajectory.Feedback()

        # Start time for calculating delays
        start_time = self._node.get_clock().now()

        # Extract joint names from the first point
        if goal_handle.request.trajectory.points:
            self.joint_names = goal_handle.request.trajectory.joint_names

        # Process the goal here (e.g., move the robot joints to the desired positions)
        for point in goal_handle.request.trajectory.points:
            # Print the joint angles
            self._node.get_logger().info(f"Moving to joint angles: {point.positions} at time {point.time_from_start}")

            # Set the current point for the timer callback
            self.send_to_dummy2(point)
            time.sleep(0.05)  # Sleep for 50 ms
            self.current_point = point
            # Update feedback message
            feedback_msg.joint_names = self.joint_names
            feedback_msg.actual.positions = point.positions
            feedback_msg.desired.positions = point.positions
            feedback_msg.error.positions = [0.0] * len(point.positions)  # Example error calculation

            # Publish feedback
            goal_handle.publish_feedback(feedback_msg)

        goal_handle.succeed()
        result = FollowJointTrajectory.Result()
        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
        return result

    def timer_callback(self):
        self.publish_joint_state(self.current_point.positions, self.current_point.velocities)

    def publish_joint_state(self, positions, velocities):
        joint_state = JointState()
        joint_state.header.stamp = self._node.get_clock().now().to_msg()
        joint_state.header.frame_id = ''
        joint_state.name = self.joint_names
        joint_state.position = positions
        joint_state.velocity = velocities
        # joint_state.effort = efforts
        self.joint_state_publisher.publish(joint_state)

    def udp_callback(self, data):
        self.update(data)

    def send_msg(self, id, type, cmd1, cmd2) -> None:
        self.client.send_message(id, type, struct.pack('<I', cmd1), struct.pack('<I', cmd2), rbootlibs.Message_type['short'])

    def register_cb(self):
        self.client.register_callback(self.udp_callback)
        self.send_msg(1, rbootlibs.Command_id['Set_Axis_State'], rbootlibs.AxisState['IDLE'], rbootlibs.Message_type['short'])
        self._node.get_logger().info('Rboot CAN BUS: enabled controller status updates')

    def unregister_cb(self):
        self.client.unregister_callback()
        self._node.get_logger().info('Rboot CAN BUS: controller status is disabled')

    def update(self, data):
        if data is None:
            self._node.get_logger().info('Rboot CAN BUS: disabled as no more available data')
        else:
            int_values = [int(x, 16) for x in data.split()]
            byte_array = struct.pack('12B', *int_values)
            if len(byte_array) == 12:
                msg = rbootlibs.pack_can_message(byte_array)
                id = msg.get('id')
                if id >= 0x30:
                    self._node.get_logger().info('CAN BUS ID MUST be less than 48(0x30)!!!')
                type = msg.get('type')
                body = msg.get('body')
                if type == rbootlibs.Command_id['Get_Encoder_Estimates']:
                    pos, vel = struct.unpack('<ff', body)
                    pub_msg = RbootPosition()
                    pub_msg.nodeid = id
                    pub_msg.position = pos
                    pub_msg.velocity = vel
                    pub_msg.torque = 1.0

    def get_reduction(self, i):
        motor_keys = list(rbootlibs.motors_cfg.keys())
        motor_name = motor_keys[i]
        return rbootlibs.motors_cfg[motor_name]['reduction']

    def get_ccw(self, i):
        motor_keys = list(rbootlibs.motors_cfg.keys())
        motor_name = motor_keys[i]
        return rbootlibs.motors_cfg[motor_name]['ccw']

    def toggle_sign(self, x):
        if x > 0:
            return -x
        elif x < 0:
            return abs(x)
        else:
            return x

    def send_6d_msg(self, id, type, cmd1, cmd2):
        for i in range(6):
            cid = i + 1
            self.client.send_message(cid, type, struct.pack('<I', cmd1), struct.pack('<I', cmd2), rbootlibs.Message_type['short'])

    def set_loop(self, msg):
        if msg.data == 1:
            self.send_6d_msg(0, rbootlibs.Command_id['Set_Axis_State'], rbootlibs.AxisState['CLOSED_LOOP_CONTROL'], 0)
            self._node.get_logger().info('loop state is set up! %d ' % (msg.data))
        else:
            self.send_6d_msg(0, rbootlibs.Command_id['Set_Axis_State'], rbootlibs.AxisState['IDLE'], 0)
            self._node.get_logger().info('loop state is clean up! %d ' % (msg.data))

    def send_to_dummy2(self, msg):
        for i in range(6):
            p = msg.positions[i]
            reduction_value = self.get_reduction(i)
            motorCnt = (p * (180 / math.pi)) / 360.0 * reduction_value
            self._node.get_logger().info('node %d and pos %f cnt %f' % (i, p, (360.0 * motorCnt) / reduction_value))
            ccw = self.get_ccw(i)
            if ccw == 1:
                p1 = motorCnt * 1
            else:
                p1 = motorCnt * -1
            pos = struct.pack('<f', float(p1))
            cmd2 = struct.pack('<HH', 60, 10)
            self.client.send_message(i + 1, rbootlibs.Command_id['Set_Input_Pos'], pos, cmd2, rbootlibs.Message_type['short'])

    def send_position(self, msg):
        reduction_value = self.get_reduction(msg.nodeid - 1)
        motorCnt = msg.position / 360.0 * reduction_value
        ccw = self.get_ccw(msg.nodeid - 1)
        if ccw == 1:
            p = self.toggle_sign(motorCnt)
        else:
            p = motorCnt
        pos = struct.pack('<f', float(p))
        cmd2 = struct.pack('<HH', 0x1f, 0)
        self.client.send_message(msg.nodeid, rbootlibs.Command_id['Set_Input_Pos'], pos, cmd2, rbootlibs.Message_type['short'])
        self._node.get_logger().info('sent node: %d position: %f degree: %f' % (msg.nodeid, msg.position, p))


class GripperActionServer(Node):
    def __init__(self, node):
        super().__init__('hand_controller')
        self._action_server = rclpy.action.ActionServer(
            node,
            GripperCommand,
            '/hand_controller/gripper_cmd',
            self.execute_callback)

    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')

        feedback_msg = GripperCommand.Feedback()
        feedback_msg.position = 0.0
        feedback_msg.effort = 0.0

        target_position = goal_handle.request.command.position
        max_effort = goal_handle.request.command.max_effort
        self.get_logger().info(f'target position: {target_position}, max effort: {max_effort}')

        goal_handle.succeed()

        result = GripperCommand.Result()
        result.reached_goal = True
        return result


def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node('dummy2_arm_controller')
    server = Dummy2ArmControllerServer(node)

    rclpy.spin(node)

    server.destroy()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()