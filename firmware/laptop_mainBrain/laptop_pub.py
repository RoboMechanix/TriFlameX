import time
import paho.mqtt.client as mqtt
from config import MQTT_TOPIC_PUB_BLACK, blackCar_data, MQTT_TOPIC_PUB_RED ,redCar_data, MQTT_TOPIC_PUB_BLUE, blueCar_data

def on_publish(client, userdata, mid):
    print("message published")

def publish_message(client):
    while True:
        if (blueCar_data < redCar_data and blueCar_data < blackCar_data):
            msg = "GO"
            pubMsg(msg, MQTT_TOPIC_PUB_BLUE, client)
        else:
            msg = "STOP"
            pubMsg(msg, MQTT_TOPIC_PUB_BLUE, client)
        if (redCar_data < blueCar_data and redCar_data < blackCar_data):
            msg = "GO"
            pubMsg(msg, MQTT_TOPIC_PUB_RED, client)
        else:
            msg = "STOP"
            pubMsg(msg, MQTT_TOPIC_PUB_RED, client)
        if (blackCar_data < blueCar_data and blackCar_data < redCar_data):
            msg = "GO"
            pubMsg(msg, MQTT_TOPIC_PUB_BLACK, client)
        else:
            msg = "STOP"
            pubMsg(msg, MQTT_TOPIC_PUB_BLACK, client)

        time.sleep(5)

def pubMsg(msg, topic, client):
    pubMsg = client.publish(
            topic=topic,
            payload=msg.encode('utf-8'),
            qos=0,
        )
    pubMsg.wait_for_publish()

