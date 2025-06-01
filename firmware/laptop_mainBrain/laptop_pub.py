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
        
        if is_all_autonomous():
            winner = get_lowest_data_car()
            if winner == "blue":
                pubMsg("GO", MQTT_TOPIC_PUB_BLUE, client)
                pubMsg("STOP", MQTT_TOPIC_PUB_RED, client)
                pubMsg("STOP", MQTT_TOPIC_PUB_BLACK, client)
            elif winner == "red":
                pubMsg("STOP", MQTT_TOPIC_PUB_BLUE, client)
                pubMsg("GO", MQTT_TOPIC_PUB_RED, client)
                pubMsg("STOP", MQTT_TOPIC_PUB_BLACK, client)
            else:
                pubMsg("STOP", MQTT_TOPIC_PUB_BLUE, client)
                pubMsg("STOP", MQTT_TOPIC_PUB_RED, client)
                pubMsg("GO", MQTT_TOPIC_PUB_BLACK, client)

        elif is_two_autonomous():
            if config.isBlueCarAutonomous and config.isRedCarAutonomous:
                if config.blueCar_data <= config.redCar_data:
                    pubMsg("GO", MQTT_TOPIC_PUB_BLUE, client)
                    pubMsg("STOP", MQTT_TOPIC_PUB_RED, client)
                else:
                    pubMsg("STOP", MQTT_TOPIC_PUB_BLUE, client)
                    pubMsg("GO", MQTT_TOPIC_PUB_RED, client)

            elif config.isBlueCarAutonomous and config.isBlackCarAutonomous:
                if config.blueCar_data <= config.blackCar_data:
                    pubMsg("GO", MQTT_TOPIC_PUB_BLUE, client)
                    pubMsg("STOP", MQTT_TOPIC_PUB_BLACK, client)
                else:
                    pubMsg("STOP", MQTT_TOPIC_PUB_BLUE, client)
                    pubMsg("GO", MQTT_TOPIC_PUB_BLACK, client)

            elif config.isRedCarAutonomous and config.isBlackCarAutonomous:
                if config.redCar_data <= config.blackCar_data:
                    pubMsg("GO", MQTT_TOPIC_PUB_RED, client)
                    pubMsg("STOP", MQTT_TOPIC_PUB_BLACK, client)
                else:
                    pubMsg("STOP", MQTT_TOPIC_PUB_RED, client)
                    pubMsg("GO", MQTT_TOPIC_PUB_BLACK, client)

        else:
            if config.isBlueCarAutonomous:
                pubMsg("GO", MQTT_TOPIC_PUB_BLUE, client)
            elif config.isRedCarAutonomous:
                pubMsg("GO", MQTT_TOPIC_PUB_RED, client)
            elif config.isBlackCarAutonomous:
                pubMsg("GO", MQTT_TOPIC_PUB_BLACK, client)

        if not config.isBlueCarAutonomous:
            pubMsg("Manual Mode", MQTT_TOPIC_PUB_BLUE, client)
        if not config.isRedCarAutonomous:
            pubMsg("Manual Mode", MQTT_TOPIC_PUB_RED, client)
        if not config.isBlackCarAutonomous:
            pubMsg("Manual Mode", MQTT_TOPIC_PUB_BLACK, client)

        
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
    
    
def is_all_autonomous():
    return config.isBlueCarAutonomous and config.isRedCarAutonomous and config.isBlackCarAutonomous

def is_two_autonomous():
    count = 0
    if config.isBlueCarAutonomous:
        count += 1
    if config.isRedCarAutonomous:
        count += 1
    if config.isBlackCarAutonomous:
        count += 1
    return count == 2

def get_lowest_data_car():
    if config.blueCar_data <= config.redCar_data and config.blueCar_data <= config.blackCar_data:
        return "blue"
    elif config.redCar_data <= config.blueCar_data and config.redCar_data <= config.blackCar_data:
        return "red"
    else:
        return "black"
