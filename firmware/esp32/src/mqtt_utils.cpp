#include <main.h>

long lastMsg = 0;
bool firstTime = true;

void setupMQTT(const char* server, const char* client_id, const char* topic, const char* topic2) {
    client.setServer(server, 1883);
    client.setCallback(mqttCallback);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");

        if (client.connect(client_id)) {
            Serial.println("connected.");
            client.subscribe(topic);
            client.subscribe(topic2);
        } else {
            Serial.print("failed. rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 2 seconds");
    
            blink_led(3,200); //blink LED three times (200ms on duration) to show that MQTT server connection attempt failed
            
            delay(2000);
          
        }
    }
}

void connect_mqttServer() {
    if (!client.connected()) {
        setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_laptopCMD, mqtt_sub_joyRos);
    }
    client.loop();
    delay(50);
}

void mqttCallback(char* topic, byte* message, unsigned int length) {
    String msg = "";
    for (unsigned int i = 0; i < length; i++) {
      msg += (char)message[i];
    }

    if (strcmp(topic, mqtt_sub_laptopCMD) == 0) {
        if (msg == "GO") {
            setCommandSTM32(MOVECOMMAND::GO);
            //sendPackedToSTM32(Sensordistance, Sensorangle); 
        }   
        else if (msg == "STOP") {
            setCommandSTM32(MOVECOMMAND::STOP);

        } 
        else if (msg == "Manual Mode") {
            setCommandSTM32(MOVECOMMAND::ManualMode);
        }
    }
    if (strcmp(topic, mqtt_sub_joyRos) == 0) {
        unsigned long raw = msg.toInt();

        int command = (raw >> 23) & 0x01;
        int direction = (raw >> 22) & 0x01;
        int distance = (raw >> 8) & 0x3FFF;
        int angleSign = (raw >> 7) & 0x01;
        int angleMag = raw & 0x7F;

        int angle = angleSign ? -angleMag : angleMag;

        xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
        go_command = (command == 1);
        xSemaphoreGive(xSharedDataMutex);

        bool dir = (direction == 1);

        sendPackedToSTM32(direction, distance, angle);
    }

}

void publishMessage(const char* topic, const String& payload) {

    long now = millis();
    if (client.connected() && (now - lastMsg > 1000)) {
        lastMsg = now;
        client.publish(topic, payload.c_str());
    }
}

