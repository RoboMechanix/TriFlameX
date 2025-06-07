from enum import Enum
MQTT_BROKER = "192.168.0.69" 
import paho.mqtt.publish as publish
import time

def pack_payload(command, distance, sign, angle):
    payload = (command << 23) | (distance << 8) | (sign << 7) | angle
    return payload


class Car(Enum):
    BLUE = 1
    RED = 2                                                                                                                                 
    BLACK = 3

COLOR_CODES = {
    Car.BLUE: "\033[94m",   
    Car.RED: "\033[91m",    
    Car.BLACK: "\033[90m",  
}
ENDC = "\033[0m" 


def reliable_publish(topic, payload, retries=10, delay=0.1):
    for attempt in range(retries):
        try:
            publish.single(topic, payload=payload, hostname=MQTT_BROKER)
            return
        except Exception as e:
            if attempt < retries - 1:
                time.sleep(delay)
            else:
                raise e
