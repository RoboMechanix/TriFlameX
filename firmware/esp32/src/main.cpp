#include <main.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "192.168.1.x"; //IP Address

const char* mqtt_client_id = "ESP32_Node";
const char* mqtt_topic = "cmd/node1";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

void setup() {
  setup_led(); 
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupMQTT(mqtt_server, mqtt_client_id, mqtt_topic);

  //Wire.begin();
  //setupSTM32Serial(stm32Serial, 16, 17);
  
}

void loop() {
  if (!client.connected()) {
    connect_mqttServer();
  }
  client.loop();
  long now = millis();

  if (now - lastMsg > 2000) { // Publish every 2 seconds
    lastMsg = now;

    String message = String("Hello from ") + mqtt_client_id;
    Serial.print("Publishing message: ");
    Serial.println(message);

    client.publish(mqtt_topic, message.c_str());
  }
   
}
