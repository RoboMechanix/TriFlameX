import time
from config import (
    MQTT_TOPIC_PUB_BLACK,
    MQTT_TOPIC_PUB_RED,
    MQTT_TOPIC_PUB_BLUE
)
import config
firstTime = True

blueCar_prevState = False
redCar_prevState = False
blackCar_prevState = False

def on_publish(client, userdata, mid):
    global firstTime
    global blueCar_prevState, redCar_prevState, blackCar_prevState
    if firstTime:
        firstTime = False
        blueCar_prevState = config.isBlueCar_live
        redCar_prevState = config.isRedCar_live
        blackCar_prevState = config.isBlackCar_live
        #print_status()
    else:
        check_status()
            
    #print("message published")
    #pass
    

def publish_message(client):
    
    while True:
        if (config.blueCar_data < config.redCar_data and config.blueCar_data < config.blackCar_data):
            msg = "GO"
            pubMsg(msg, MQTT_TOPIC_PUB_BLUE, client)
        else:
            msg = "STOP"
            pubMsg(msg, MQTT_TOPIC_PUB_BLUE, client)
        if (config.redCar_data < config.blueCar_data and config.redCar_data < config.blackCar_data):
            msg = "GO"
            pubMsg(msg, MQTT_TOPIC_PUB_RED, client)
        else:
            msg = "STOP"
            pubMsg(msg, MQTT_TOPIC_PUB_RED, client)
        if (config.blackCar_data < config.blueCar_data and config.blackCar_data < config.redCar_data):
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
    if blueCar_prevState != config.isBlueCar_live:
        blueCar_prevState = config.isBlueCar_live
        changed = True
    if redCar_prevState != config.isRedCar_live:
        redCar_prevState = config.isRedCar_live
        changed = True
    if blackCar_prevState != config.isBlackCar_live:
        blackCar_prevState = config.isBlackCar_live
        changed = True
    if changed:
        print_status()

def print_status():   
    print()
    print ("Blue Car is live ✅" if config.isBlueCar_live else "Blue Car is Dead 🛑") 
    print ("Red Car is live ✅" if config.isRedCar_live else "Red Car is Dead 🛑")
    print ("Black Car is live ✅" if config.isBlackCar_live else "Black Car is Dead 🛑")