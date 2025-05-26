#include <main.h>

const char* ssid = "SSH";
const char* password = "AzabSSH359";
const char* mqtt_server = "192.168.0.69"; //IP Address

const char* mqtt_client_id = "ESP32_BlueCar";
const char* mqtt_sub_topic = "laptop/commands"; 
const char* mqtt_pub_topic = "sensor/esp32";

WiFiClient espClient;
PubSubClient client(espClient);


HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

void setup() {
  setup_led(); 

  Serial.begin(115200);

  connectToWiFi(ssid, password);
  setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_topic);

  Wire.begin();
  setupSTM32Serial(stm32Serial, 16, 17);
  
}

void loop() {

  if (!client.connected()) {
    connect_mqttServer();
  }
  client.loop();
  
  String message = String("Hello from ") + mqtt_client_id;
  publishMessage(mqtt_pub_topic, message);
  
   
}


    

