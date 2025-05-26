import time
import paho.mqtt.client as mqtt
from config import (
    MQTT_TOPIC_PUB_BLACK,
    blackCar_data,
    MQTT_TOPIC_PUB_RED,
    redCar_data,
    MQTT_TOPIC_PUB_BLUE,
    blueCar_data,
    isBlueCar_live,
    isRedCar_live,
    isBlackCar_live)

firstTime = True

blueCar_prevState = False
redCar_prevState = False
blackCar_prevState = False

def on_publish(client, userdata, mid):
    global firstTime
    global blueCar_prevState, redCar_prevState, blackCar_prevState
    if firstTime:
        firstTime = False
        blueCar_prevState = isBlueCar_live
        redCar_prevState = isRedCar_live
        blackCar_prevState = isBlackCar_live
        print_status()
    else:
        check_status()
            
    #print("message published")
    #pass
    

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
            
        time.sleep(0.5)
        
def pubMsg(msg, topic, client):
    pubMsg = client.publish(
            topic=topic,
            payload=msg.encode('utf-8'),
            qos=0,
        )
    pubMsg.wait_for_publish()


def check_status():
    global blueCar_prevState, redCar_prevState, blackCar_prevState
    changed = False
    if blueCar_prevState != isBlueCar_live:
        blueCar_prevState = isBlueCar_live
        changed = True
    if redCar_prevState != isRedCar_live:
        redCar_prevState = isRedCar_live
        changed = True
    if blackCar_prevState != isBlackCar_live:
        blackCar_prevState = isBlackCar_live
        changed = True
    if changed:
        print_status()

def print_status():   
    print ("Blue Car is live ✅" if isBlueCar_live else "Blue Car is Dead 🛑") 
    print ("Red Car is live ✅" if isRedCar_live else "Red Car is Dead 🛑")
    print ("Black Car is live ✅" if isBlackCar_live else "Black Car is Dead 🛑")