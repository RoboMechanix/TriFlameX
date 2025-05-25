import paho.mqtt.client as mqtt

from config import MQTT_TOPIC, MQTT_BROKER, MQTT_PORT


is_connected = False

# === Callback when connected ===
def on_connect(client, userdata, flags, rc):
   if rc == 0:
        print("✅ Connected to MQTT Broker!")
        is_connected = True
        client.subscribe(MQTT_TOPIC)
   else:
        print(f"❌ Failed to connect, return code {rc}")
        is_connected = False

# === Callback when a message is received ===
def on_message(client, userdata, msg):
    print(f"📩 Received from ESP32 on topic '{msg.topic}': {msg.payload.decode()}")
 