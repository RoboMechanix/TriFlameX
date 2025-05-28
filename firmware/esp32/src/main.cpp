#include <main.h>

const char* ssid = "SSH";
const char* password = "AzabSSH359";
const char* mqtt_server = "192.168.0.69"; //IP Address

const char* mqtt_client_id = "ESP32_BlueCar";
const char* mqtt_sub_topic = "laptop/commands/bluecar"; 
const char* mqtt_pub_topic = "sensor/bluecar";

WiFiClient espClient;
PubSubClient client(espClient);

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

float dummydistance_cm = 5.3; 

void setup() {
  setup_led(); 

  Serial.begin(115200); 

  connectToWiFi(ssid, password);
  setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_topic);

  Wire.begin();
  setupSTM32Serial(stm32Serial, 16, 17);
  
}

void sendValueToSTM32(float value);

void loop() {

  if (!client.connected()) {
    connect_mqttServer();
  }
  client.loop();
  delay(50);
  dummydistance_cm++;

  sendValueToSTM32(1.0);

  //String message = mqtt_client_id + String(": ") + dummydistance_cm + String(" cm");
  String message = String(dummydistance_cm, 0);
  //message+= String(" cm");
  publishMessage(mqtt_pub_topic, message);
  
}


void sendValueToSTM32(float value) {
    stm32Serial.println(value, 1); 
}



    

