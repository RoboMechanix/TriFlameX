# === Configuration ===
REQUIRED_SSID = "SSH"
MQTT_BROKER = "192.168.0.69"   
INTERFACE = "wlp0s20f3"
REQUIRED_IP =  MQTT_BROKER 
MQTT_PORT = 1883
MQTT_TOPIC_SUB_BLUE = "sensor/bluecar"
MQTT_TOPIC_SUB_RED = "sensor/redcar"
MQTT_TOPIC_SUB_BLACK = "sensor/blackcar"
MQTT_TOPIC_SUB_BLUE_ROS = "bluecar/cmd"
MQTT_TOPIC_SUB_RED_ROS = "redcar/cmd"
MQTT_TOPIC_SUB_BLACK_ROS = "blackcar/cmd"
MQTT_TOPIC_PUB_BLUE = "laptop/commands/bluecar"
MQTT_TOPIC_PUB_RED = "laptop/commands/redcar"
MQTT_TOPIC_PUB_BLACK = "laptop/commands/blackcar"
MQTT_CLIENT_ID = "Ubuntu_Client"


# === ESP Data ===
blueCar_data = 69
redCar_data = 69
blackCar_data = 69
isBlueCar_live = False
isRedCar_live = False
isBlackCar_live = False
