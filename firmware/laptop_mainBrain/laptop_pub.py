import time
import paho.mqtt.client as mqtt
from config import MQTT_TOPIC

def on_publish(client, userdata, mid):
    print("message published")

def publish_message(client):
    while True:
        msg = "Hello from Ubuntu"

        pubMsg = client.publish(
            topic=MQTT_TOPIC,
            payload=msg.encode('utf-8'),
            qos=0,
        )
        pubMsg.wait_for_publish()

        if pubMsg.is_published():
            print(f"📤 Published: {msg}")
        else:
            print("⚠️ Publish failed or queued")

        time.sleep(5)



