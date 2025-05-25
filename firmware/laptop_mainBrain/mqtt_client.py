import paho.mqtt.client as mqtt
from paho.mqtt.client import CallbackAPIVersion
print(CallbackAPIVersion)
from config import MQTT_TOPIC, MQTT_BROKER, MQTT_PORT, MQTT_CLIENT_ID
from laptop_pub import publish_message, on_publish
from laptop_sub import on_connect, on_message


# === Setup MQTT Client ===
client = mqtt.Client(
    client_id=MQTT_CLIENT_ID,
    protocol=mqtt.MQTTv311,
)
client.on_connect = on_connect
client.on_message = on_message
client.on_publish = on_publish

client.connect(MQTT_BROKER, MQTT_PORT, 60)


# === Loop and Publish ===
client.loop_start()

try:
    publish_message(client)
    
except KeyboardInterrupt:
    print("🛑 Exiting...")
    print("\nStopping MQTT client due to KeyboardInterrupt")
    client.loop_stop()
    client.disconnect()

except Exception as e:
    print(e)
