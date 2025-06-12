#include <main.h>

const char* ssid = "SSH";
const char* password = "AzabSSH359";
const char* mqtt_server = "192.168.0.69"; //IP Address

const char* mqtt_client_id = "ESP32_" TOSTRING(CAR_COLOUR) "Car";
const char* mqtt_sub_laptopCMD = "laptop/commands/" TOSTRING(CAR_COLOUR) "car";
const char* mqtt_pub_topic = "sensor/" TOSTRING(CAR_COLOUR) "car";
const char* mqtt_sub_joyRos = "joyROS/" TOSTRING(CAR_COLOUR) "car/cmd";



WiFiClient espClient;
PubSubClient client(espClient);

HardwareSerial stm32Serial(2); // UART2: TX2=17, RX2=16

SemaphoreHandle_t xSharedDataMutex;

u16_t dummydistance_cm = 12; 
volatile bool go_command = false;
bool isAutonomous = true; 
volatile int Sensordistance= 69999;
volatile int Sensorangle = 90;  

void setup() {
  Serial.begin(115200);
  setup_led();
  
  xSharedDataMutex = xSemaphoreCreateMutex();
    if (xSharedDataMutex == NULL) {
      while (1) {
        Serial.println("Failed to create mutex");
      }
    }
    // Blocking the flow till the wi-fi is connected
    connectToWiFi(ssid, password);
    tofInit();
    stepperInit();
    delay(2000); // Give time for Serial to connect
    
    setupSTM32Serial(stm32Serial, rx_pin, tx_pin);
    setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_laptopCMD, mqtt_sub_joyRos);
    
    // Comms on core 0
    xTaskCreatePinnedToCore(WiFiTask, "WiFiTask", 4096, NULL, 1, NULL, 0); 
    xTaskCreatePinnedToCore(MQTTTask, "MQTTTask", 8192, NULL, 2, NULL, 0); 
    xTaskCreatePinnedToCore(SerialTask, "SerialTask", 4096, NULL, 2, NULL, 0);

    xTaskCreatePinnedToCore(
          tof_task,         // Function name
          "tof",            // Task name
          2048,             // Stack size
          NULL,             // Parameter
          1,                // Priority
          NULL,             // Task handle
          1                 // Core 1
    );

    xTaskCreatePinnedToCore(
          stepper_task,     // Function name
          "stepper",        // Task name
          4096,             // Stack size
          NULL,             // Parameter
          2,                // Priority
          NULL,             // Task handle
          1                 // Core 1
    );
  
}


void loop(){}

    