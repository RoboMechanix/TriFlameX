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
    xSemaphoreTake(xSharedDataMutex,portMAX_DELAY);
    command = go_command;
    bool autonomous = isAutonomous;
    xSemaphoreGive(xSharedDataMutex);
    //sendPackedToSTM32(30,20);
    if (command && autonomous ){
      sendPackedToSTM32(Sensordistance, Sensorangle);
    }
    else if (autonomous){
      sendPackedToSTM32(0,0);
    }
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}