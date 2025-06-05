#include <main.h>

void WiFiTask(void *pvParameters) {
  while (true) {
    if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi(ssid, password);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void MQTTTask(void *pvParameters) {
  while (true) {
    if (!client.connected()) {
      connect_mqttServer();
    }

    client.loop();

    String message = String(Sensordistance++);
    publishMessage(mqtt_pub_topic, message);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void SerialTask(void *pvParameters) {
  while (true) {
    bool command = false;
    //sendPackedToSTM32(30,20);
    if (go_command){
      sendPackedToSTM32(Sensordistance, Sensorangle);
    }
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}