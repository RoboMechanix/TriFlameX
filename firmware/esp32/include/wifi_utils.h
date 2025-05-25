#pragma once
#include <WiFi.h>

#define ledPin 2

void connectToWiFi(const char* ssid, const char* password) {
    delay(50);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    char c = 0; //counter for number of attempts

    while (WiFi.status() != WL_CONNECTED) {
        //blink LED twice (for 200ms ON time) to indicate that wifi not connected
        blink_led(2,200); 
        delay(1000); 
        Serial.print(".");
        c++;
        if (c > 20) { 
            Serial.println("\nFailed to connect to WiFi. Please check your credentials.");
            ESP.restart();
            return;
        }
    }
    Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
}

void blink_led(unsigned int times, unsigned int duration){
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW); 
    delay(200);
  }
}