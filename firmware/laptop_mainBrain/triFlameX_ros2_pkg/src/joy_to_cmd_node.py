import os
import sys
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import UInt32
import paho.mqtt.publish as publish
from UTIL import pack_payload, Car

from UTIL import ENDC, COLOR_CODES


sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../")))
from config import MQTT_BROKER



class JoyToCmd(Node):
    def __init__(self):
        super().__init__('joy_to_cmd')
        self.selected_car = None
        self.first_run = True
        self.get_logger().info('JoyToCmd Node has been started.')
       
        self.subscription = self.create_subscription(
            Joy,
            '/joy',
            self.joy_callback,
            10)
        self.subscription  
    
    def joy_callback(self, msg):
        
        if self.selected_car is None and self.first_run: 
            self.get_logger().info('No car selected. Press LB to select a car.')
            self.first_run = False
        
        if not msg.buttons[4]: #LB
            self.selected_car = None
            #self.get_logger().info('Car selection has been cleared.')
            return
        
        prev_selected_car = self.selected_car
        # Button mapping
        if msg.buttons[2]:  # X
            self.selected_car = Car.BLUE
        elif msg.buttons[0]:  # A
            self.selected_car = Car.RED
        elif msg.buttons[1]:  # B
            self.selected_car = Car.BLACK
            
        if self.selected_car is None:
            return 
        
        if prev_selected_car != self.selected_car:
            color = COLOR_CODES.get(self.selected_car, "")
            self.get_logger().info(f'{color}Selected car: {self.selected_car.name}{ENDC}')


        # Axes to movement
        throttle = int(abs(msg.axes[1]) * 1000)  # Distance
        angle = int(abs(msg.axes[0]) * 90)       # Angle
        sign = 0 if msg.axes[0] >= 0 else 1
        command = 1 if abs(throttle) > 50 else 0

        packed_data = pack_payload(command, throttle, sign, angle)
        payload = str(packed_data)
        topic = f"joyROS/{self.selected_car.name.lower()}car/cmd"
        try:
            publish.single(topic, payload=payload, hostname=MQTT_BROKER)
        except Exception as e:
            self.get_logger().error(f"Failed to connect to MQTT broker '{MQTT_BROKER}': {e}")
       
            


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
    
