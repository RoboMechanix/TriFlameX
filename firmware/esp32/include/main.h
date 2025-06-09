#ifndef MAIN_H
#define MAIN_H

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "wifi_utils.h"
#include "mqtt_utils.h"
#include "serial_utils.h"
#include <ledAsIndicator.h>
#include "util.h"
#include "lidar.h"

// ==== Constants === 
#define CAR_COLOUR blue
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// ==== Wi-Fi Credentials ====
extern const char* ssid;
extern const char* password;

// ==== MQTT Server Config ====
extern const char* mqtt_server;
extern const char* mqtt_client_id;
extern const char* mqtt_sub_laptopCMD;
extern const char* mqtt_sub_joyRos;
extern const char* mqtt_pub_topic;

// ==== Global Objects ====
extern WiFiClient espClient;
extern PubSubClient client;
extern HardwareSerial stm32Serial;
extern SemaphoreHandle_t xSharedDataMutex;

// ==== Global Variables ====
extern volatile bool go_command; 
extern bool isAutonomous;


// ==== FreeRTOS Variables ====
extern SemaphoreHandle_t xSharedDataMutex;

// ==== Function Declarations ====
void connectToWiFi(const char* ssid, const char* password);
void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);
void mqttCallback(char* topic, byte* payload, unsigned int length);
void setupMQTT(const char* server, const char* client_id, const char* topic);
void connect_mqttServer();  
void SerialTask(void *pvParameters);
void WiFiTask(void *pvParameters);
void MQTTTask(void *pvParameters);
void joe_task(void *pvParameters);
void communicationsTask(void *pvParameters);


typedef struct {
  int distance;
  int angle;
} SensorData;

extern QueueHandle_t mqttQueue;

#endif // MAIN_H_