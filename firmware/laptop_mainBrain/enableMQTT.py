import paho.mqtt.client as mqtt
from config import MQTT_BROKER, MQTT_PORT, MQTT_CLIENT_ID
from config import command, enable_topic

# Create MQTT client
client = mqtt.Client(client_id=MQTT_CLIENT_ID, protocol=mqtt.MQTTv311)

# Connect to the MQTT broker
client.connect(MQTT_BROKER, MQTT_PORT, 60)

# Wait for connection to establish
client.loop_start()
client.publish(enable_topic, payload=command, qos=0, retain=False)
client.loop_stop()

# Disconnect from broker
client.disconnect()
