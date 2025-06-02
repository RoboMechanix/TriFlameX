#pragma once
#include <main.h>

extern PubSubClient client;
extern HardwareSerial stm32Serial; // UART2: TX2=17, RX2=16

void mqttCallback(char* topic, byte* payload, unsigned int length);
void setupMQTT(const char* server, const char* client_id, const char* topic, const char* topic2);
void callback(char* topic, byte* message, unsigned int length);
void connect_mqttServer();
void publishMessage(const char* topic, const String& payload);

