import paho.mqtt.client as mqtt
import time
import threading

from config import (
    MQTT_TOPIC_SUB_BLUE,
    MQTT_TOPIC_SUB_RED,
    MQTT_TOPIC_SUB_BLACK
)

import config

is_connected = False

last_seen = {
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
            if now - last_seen[color] > 2:
               car_status[color] = False
            else:
               car_status[color] = True
        
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
    else:
        print(f"❌ Failed to connect, return code {reason_code}")
        is_connected = False

# === Callback when a message is received ===
def on_message(client, userdata, msg):
     payload = msg.payload.decode('utf-8')
     topic = msg.topic

     if topic == MQTT_TOPIC_SUB_BLUE:
        data_str = payload.split(": ")[1].strip()  #  "100 cm"
        config.blueCar_data = int(data_str.split()[0])    # "100"
        last_seen["blue"] = time.time()

     elif topic == MQTT_TOPIC_SUB_RED:
        data_str = payload.split(": ")[1].strip()
        config.redCar_data = int(data_str.split()[0])
        last_seen["red"] = time.time()

     elif topic == MQTT_TOPIC_SUB_BLACK:
        data_str = payload.split(": ")[1].strip()
        config.blackCar_data = int(data_str.split()[0])
        last_seen["black"] = time.time()

     #print(f"📩 Received from ESP32 on topic '{msg.topic}': {payload}")

# === Start the monitoring thread ===
threading.Thread(target=monitor_car_status, daemon=True).start()
