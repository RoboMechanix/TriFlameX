import rclpy
import time
from rclpy.node import Node
from sensor_msgs.msg import Joy
from triflamex_ros2_pkg.UTIL import pack_payload, Car
from triflamex_ros2_pkg.UTIL import ENDC, COLOR_CODES
from triflamex_ros2_pkg.UTIL import reliable_publish
from triflamex_ros2_pkg.UTIL import MQTT_BROKER as MQTT_BROKER

speed_array = [20, 40, 199] 
angle_array = [100, 110, 125]

class JoyToCmd(Node):
    def __init__(self):
        super().__init__('joy_to_cmd')
        self.selected_car = None
        self.first_run = True
        self.speed = speed_array[0]
        self.index = 0
        self.prev_rb_state = 0  
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
            self.index = 0
            self.speed = speed_array[self.index]
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
        
        current_rb_state = msg.buttons[5]
        if current_rb_state and not self.prev_rb_state:
            # Button was just pressed (rising edge)
            self.index = (self.index + 1) % len(speed_array)
            self.speed = speed_array[self.index]
            self.get_logger().info(f'Speed level:  {self.index+1}')
        self.prev_rb_state = current_rb_state

        
        if prev_selected_car != self.selected_car:
            color = COLOR_CODES.get(self.selected_car, "")
            self.get_logger().info(f'{color}Selected car: {self.selected_car.name}{ENDC}')
            self.get_logger().info(f'Speed level:  {self.index+1}')
            

        # Validate and clamp joystick axes
        raw_throttle = msg.axes[1]
        raw_angle = msg.axes[3]
        
        # Dead zone
        if abs(raw_throttle) < 0.1:
            raw_throttle = 0.0
        if abs(raw_angle) < 0.1:
            raw_angle = 0.0
    
        # Convert to meaningful values
        throttle = int((raw_throttle) * 8500)
        angle = int(abs(raw_angle) * 90)
        sign = 0 if raw_angle >= 0 else 1
        dir = 0 if raw_throttle >= 0 else 1
        command = 1 if abs(raw_throttle) > 0.1  or abs(raw_angle) > 0.1 else 0
                
        throttle = speed_array[self.index] if command == 1 else 0
        angle = angle_array[self.index] if angle > 10 else 0
        
        angle = angle-90 if sign else angle
        
        throttle = 10 if throttle == 0 else throttle
        
        try:
            packed_data = pack_payload(command, dir, throttle, sign, angle)
            payload = str(packed_data)
            topic = f"joyROS/{self.selected_car.name.lower()}car/cmd"
            
            if command:
                time.sleep(0.4)
            else:
                time.sleep(0.3)
                
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
    
