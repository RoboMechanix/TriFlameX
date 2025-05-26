import paho.mqtt.client as mqtt

from config import MQTT_TOPIC_SUB, MQTT_BROKER, MQTT_PORT, blueCar_data, redCar_data, blackCar_data


is_connected = False

# === Callback when connected ===
def on_connect(client, userdata, flags, reason_code, properties=None):
   global is_connected
   if reason_code == 0:
        print("✅ Connected to MQTT Broker!")
        is_connected = True
        client.subscribe(MQTT_TOPIC_SUB)
   else:
        print(f"❌ Failed to connect, return code {reason_code}")
        is_connected = False

# === Callback when a message is received ===
def on_message(client, userdata, msg):
     msg = msg.payload.decode('utf-8')
     
     if msg.startswith("ESP32_BlueCar: "):
         blueCar_data = int(msg.split(": ")[1])
     
     if msg.startswith("ESP32_RedCar: "):
         redCar_data = int(msg.split(": ")[1])
     
     if msg.startswith("ESP32_BlackCar: "):
          blackCar_data = int(msg.split(": ")[1])
         
     
     print(f"📩 Received from ESP32 on topic '{msg.topic}': {msg.payload.decode()}")
 