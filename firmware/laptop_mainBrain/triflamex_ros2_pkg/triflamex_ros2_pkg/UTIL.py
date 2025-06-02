from enum import Enum



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

