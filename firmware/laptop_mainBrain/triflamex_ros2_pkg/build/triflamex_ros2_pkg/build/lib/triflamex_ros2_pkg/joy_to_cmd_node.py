import time
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from triflamex_ros2_pkg.UTIL import pack_payload, Car
from triflamex_ros2_pkg.UTIL import ENDC, COLOR_CODES
from triflamex_ros2_pkg.UTIL import reliable_publish
from triflamex_ros2_pkg.UTIL import MQTT_BROKER as MQTT_BROKER



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


        # Validate and clamp joystick axes
        raw_throttle = msg.axes[1]
        raw_angle = msg.axes[3]
        raw_sign = msg.axes[0]
    
        # Normalize and clamp
        raw_throttle = max(-1.0, min(1.0, raw_throttle))
        raw_angle = max(-1.0, min(1.0, raw_angle))

        # Convert to meaningful values
        throttle = int(abs(raw_throttle) * 32767)
        angle = int(abs(raw_angle) * 90)
        sign = 0 if raw_sign >= 0 else 1
        command = 1 if throttle > 50 else 0
        
        
        if command == 0:
            return  
        
        try:
            packed_data = pack_payload(command, throttle, sign, angle)
            payload = str(packed_data)
            topic = f"joyROS/{self.selected_car.name.lower()}car/cmd"
            
            reliable_publish(topic, payload)
            
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
    
