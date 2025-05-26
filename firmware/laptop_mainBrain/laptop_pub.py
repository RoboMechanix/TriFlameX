import time
import paho.mqtt.client as mqtt
from config import MQTT_TOPIC_PUB

def on_publish(client, userdata, mid):
    print("message published")

def publish_message(client):
    i = 1
    while True:
        msg = f"Hello from Ubuntu : {i} "
        i += 1
        if i >25:
            i = 1
        pubMsg = client.publish(
            topic=MQTT_TOPIC_PUB,
            payload=msg.encode('utf-8'),
            qos=0,
        )
        pubMsg.wait_for_publish()

        if pubMsg.is_published():
            print(f"📤 Published: {msg}")
        else:
            print("⚠️ Publish failed or queued")

        time.sleep(5)



