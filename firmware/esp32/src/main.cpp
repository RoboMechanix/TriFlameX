#include <main.h>

const char* ssid = "SSH";
const char* password = "AzabSSH359";
const char* mqtt_server = "192.168.0.69"; //IP Address

const char* mqtt_client_id = "ESP32_REDCar";
const char* mqtt_sub_topic = "laptop/commands/redcar"; 
const char* mqtt_pub_topic = "sensor/redcar";

WiFiClient espClient;
PubSubClient client(espClient);

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

u16_t dummydistance_cm = 12; 
bool go_command = false;

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
  //delay(100);
  dummydistance_cm++;

  sendPackedToSTM32(dummydistance_cm,-45);

  String message = String(dummydistance_cm);

  publishMessage(mqtt_pub_topic, message);
  
}


void sendValueToSTM32(float value) {
    stm32Serial.println(value, 1); 
}



    

