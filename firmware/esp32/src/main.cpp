#include <main.h>

const char* ssid = "SSH";
const char* password = "AzabSSH359";
const char* mqtt_server = "192.168.0.69"; //IP Address

const char* mqtt_client_id = "ESP32_REDCar";
const char* mqtt_sub_laptopCMD = "laptop/commands/redcar"; 
const char* mqtt_pub_topic = "sensor/redcar";
const char* mqtt_sub_joyRos = "joyROS/redcar/cmd";

WiFiClient espClient;
PubSubClient client(espClient);

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16


u16_t dummydistance_cm = 12; 
bool go_command = false;
bool isAutonomous = true; 
int Sensordistance= 3;
int Sensorangle = 45;  

void setup() {
  Serial.begin(115200);
  setup_led();

  // Blocking the flow till the wi-fi is connected
  connectToWiFi(ssid, password);
  setupSTM32Serial(stm32Serial, 16, 17);
  setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_laptopCMD, mqtt_sub_joyRos);
  
}

void loop(){

  if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi(ssid, password);
    }

     if (!client.connected()) {
      connect_mqttServer();
    }

    client.loop();
    delay(100);

    String message = String(Sensordistance++);
    publishMessage(mqtt_pub_topic, message);
    if (go_command){
      sendPackedToSTM32(Sensordistance, Sensorangle);
    }
}




    

