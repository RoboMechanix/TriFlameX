import os
import sys
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import UInt32
import paho.mqtt.publish as publish


sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../")))


from config import MQTT_BROKER

class JoyToCmd(Node):
    def __init__(self):
        super().__init__('joy_to_cmd')
        self.create_subscription(Joy, '/joy', self.joy_callback, 10)
        self.selected_car = None
        
        self.get_logger().info('JoyToCmd Node has been started.')
        
        self.subscription = self.create_subscription(
            Joy,
            '/joy',
            self.joy_callback,
            10)
        self.subscription  
    
    def joy_callback(self, msg):
        
        if not msg.buttons[6]:
            return
        
        prev_selected_car = self.selected_car
        # Button mapping
        if msg.buttons[2]:  # X
            self.selected_car = Car.BLUE
        elif msg.buttons[3]:  # Y
            self.selected_car = Car.RED
        elif msg.buttons[4]:  # LB
            self.selected_car = Car.BLACK
            
        if prev_selected_car != self.selected_car:
            self.get_logger().info(f'Selected car: {self.selected_car.name}')

        # Axes to movement
        throttle = int(abs(msg.axes[1]) * 1000)  # Distance
        angle = int(abs(msg.axes[0]) * 90)       # Angle
        sign = 0 if msg.axes[0] >= 0 else 1
        command = 1 if abs(throttle) > 50 else 0

        packed_data = pack_payload(command, throttle, sign, angle)
        topic = f'car{self.selected_car}/cmd'
        publish.single(topic, payload=packed_data.to_bytes(3, 'big'), hostname=MQTT_BROKER)
        self.get_logger().info(f'Sent to {topic}: {packed_data:#08x}')


def main(args=None):
    rclpy.init(args=args)
    node = JoyToCmd()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
    
    

def pack_payload(command, distance, sign, angle):
    payload = (command << 23) | (distance << 8) | (sign << 7) | angle
    return payload


from enum import Enum

class Car(Enum):
    BLUE = 1
    RED = 2                                                                                                                                 
    BLACK = 3
