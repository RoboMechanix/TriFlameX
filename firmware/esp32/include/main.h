#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <HardwareSerial.h>


#include "wifi_utils.h"
#include "mqtt_utils.h"
#include "serial_utils.h"
#include <ledAsIndicator.h>

// ==== Wi-Fi Credentials ====
extern const char* ssid;
extern const char* password;

// ==== MQTT Server Config ====
extern const char* mqtt_server;
extern const char* mqtt_client_id;
extern const char* mqtt_sub_topic;

// ==== Global Objects ====
extern WiFiClient espClient;
extern PubSubClient client;
extern HardwareSerial stm32Serial;

// ==== Global Variables ====
extern bool go_command; 
extern bool isAutonomous;

// ==== Function Declarations ====
void connectToWiFi(const char* ssid, const char* password);
void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);
void mqttCallback(char* topic, byte* payload, unsigned int length);
void setupMQTT(const char* server, const char* client_id, const char* topic);
void connect_mqttServer();  

