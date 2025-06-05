import paho.mqtt.client as mqtt
import time
import threading

from config import (
    MQTT_TOPIC_SUB_BLUE,
    MQTT_TOPIC_SUB_RED,
    MQTT_TOPIC_SUB_BLACK,
    MQTT_TOPIC_SUB_BLUE_ROS,
    MQTT_TOPIC_SUB_RED_ROS,
    MQTT_TOPIC_SUB_BLACK_ROS
)

import config

is_connected = False

last_seen = {
    "blue": time.time(),
    "red": time.time(),
    "black": time.time()
}

last_ros_seen = {
    "blue": time.time(),
    "red": time.time(),
    "black": time.time()
}


car_status = {
    "blue": True,
    "red": True,
    "black": True
}

# === Background thread to check car timeouts ===
def monitor_car_status():
     while True:
        now = time.time()
        for color in ["blue", "red", "black"]:
            if now - last_seen[color] > 2:  # 2 seconds timeout
               car_status[color] = False
            else:
               car_status[color] = True
               
            if now - last_ros_seen[color] > 2:
                if color == "blue":
                    config.isBlueCarAutonomous = True
                elif color == "red":
                    config.isRedCarAutonomous = True
                elif color == "black":
                    config.isBlackCarAutonomous = True
        
        config.isBlueCar_live = car_status["blue"]
        config.isRedCar_live = car_status["red"]
        config.isBlackCar_live = car_status["black"]
        
        time.sleep(0.5)  # check every 500ms

# === Callback when connected ===
def on_connect(client, userdata, flags, reason_code, properties=None):
    global is_connected
    if reason_code == 0:
        print("✅ Connected to MQTT Broker!")
        is_connected = True
        client.subscribe(MQTT_TOPIC_SUB_BLUE)
        client.subscribe(MQTT_TOPIC_SUB_RED)
        client.subscribe(MQTT_TOPIC_SUB_BLACK)
        client.subscribe(MQTT_TOPIC_SUB_BLUE_ROS)
        client.subscribe(MQTT_TOPIC_SUB_RED_ROS)
        client.subscribe(MQTT_TOPIC_SUB_BLACK_ROS)
    else:
        print(f"❌ Failed to connect, return code {reason_code}")
        is_connected = False

# === Callback when a message is received ===
def on_message(client, userdata, msg):
    topic = msg.topic
    
    if topic in [MQTT_TOPIC_SUB_BLUE_ROS, MQTT_TOPIC_SUB_RED_ROS, MQTT_TOPIC_SUB_BLACK_ROS]:
        ros_takeOver(msg)
        return
    
    payload = msg.payload.decode('utf-8')
     
    try:
        value = int(payload)  # parse directly as int
    except ValueError:
        print(f"⚠️ Invalid payload: '{payload}'")
        return  

    if topic == MQTT_TOPIC_SUB_BLUE:
        if not config.isBlueCarAutonomous:
            return
        config.blueCar_data = value
        last_seen["blue"] = time.time()
        
    elif topic == MQTT_TOPIC_SUB_RED:
        if not config.isRedCarAutonomous:
            return
        config.redCar_data = value
        last_seen["red"] = time.time()

    elif topic == MQTT_TOPIC_SUB_BLACK:
        if not config.isBlackCarAutonomous:
            return
        config.blackCar_data = value
        last_seen["black"] = time.time()


# === Start the monitoring thread ===
threading.Thread(target=monitor_car_status, daemon=True).start()

def ros_takeOver(msg):
    payload = msg.payload
    topic = msg.topic
    
    try:
        value = int(payload)   
    except ValueError:
        print(f"⚠️ Invalid payload: '{payload}'")
        return 

    if topic == MQTT_TOPIC_SUB_BLUE_ROS:
        config.blueCar_data = value
        config.isBlueCarAutonomous = False
        config.isBlackCarAutonomous = True
        config.isRedCarAutonomous = True
        last_ros_seen["blue"] = time.time()
        
    elif topic == MQTT_TOPIC_SUB_RED_ROS:
        config.redCar_data = value
        config.isBlueCarAutonomous = True
        config.isBlackCarAutonomous = True
        config.isRedCarAutonomous = False
        last_ros_seen["red"] = time.time()

    elif topic == MQTT_TOPIC_SUB_BLACK_ROS:
        config.blackCar_data = value
        config.isBlueCarAutonomous = True
        config.isBlackCarAutonomous = False
        config.isRedCarAutonomous = True
        last_ros_seen["black"] = time.time()
