#pragma once
#include <PubSubClient.h>
#include <HardwareSerial.h>

extern PubSubClient client;
extern HardwareSerial stm32Serial;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String command = "";
    for (unsigned int i = 0; i < length; i++) {
        command += (char)payload[i];
    }
    Serial.println("Received from laptop: " + command);
    stm32Serial.println(command);  // Forward to STM32
}

void setupMQTT(const char* server, const char* client_id, const char* topic) {
    client.setServer(server, 1883);
    client.setCallback(mqttCallback);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect(client_id)) {
            Serial.println("connected.");
            client.subscribe(topic);
        } else {
            Serial.print("failed. rc=");
            Serial.print(client.state());
            delay(1000);
        }
    }
}
