#include <main.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "192.168.1.x"; //IP Address

const char* mqtt_client_id = "ESP32_Node1";
const char* mqtt_topic = "cmd/node1";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

void setup() {
    setup_led(); 
    Serial.begin(115200);
    //Wire.begin();
    setupSTM32Serial(stm32Serial, 16, 17);
    connectToWiFi(ssid, password);
    setupMQTT(mqtt_server, mqtt_client_id, mqtt_topic);
}

void loop() {
    connect_mqttServer();
   
}

void connect_mqttServer() {
    if (!client.connected()) {
        setupMQTT(mqtt_server, mqtt_client_id, mqtt_topic);
    }
    client.loop();
    delay(1000);
    return;
}