#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "192.168.1.x"; //LAPTOP_IP


WiFiClient espClient;
PubSubClient client(espClient);

HardwareSerial stm32Serial(2); // UART2 (e.g., TX2=17, RX2=16)

void callback(char* topic, byte* payload, unsigned int length) {
  String command = "";
  for (unsigned int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
  Serial.println("Received from laptop: " + command);

  // Send to STM32
  stm32Serial.println(command);
}

void setup() {
  Serial.begin(115200);
  stm32Serial.begin(115200, SERIAL_8N1, 16, 17);  // adjust pins
  Wire.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.connect("ESP32_Node1");
  client.subscribe("cmd/node1");  // Commands from laptop
}

void loop() {
  if (!client.connected()) client.connect("ESP32_Node1");
  client.loop();

  delay(1000);
}
