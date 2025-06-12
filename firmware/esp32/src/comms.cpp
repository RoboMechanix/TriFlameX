#include <main.h>

int x =9;

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
    int dis = 0;
    xSemaphoreTake(xSharedDataMutex,portMAX_DELAY);
    dis = Sensordistance;
    xSemaphoreGive(xSharedDataMutex);

    String message = String(dis);
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
    
    if (command && autonomous ){
      int dis = 0;
      int angle = 0;
      xSemaphoreTake(xSharedDataMutex,portMAX_DELAY);
      dis = Sensordistance;
      angle = Sensorangle;
      xSemaphoreGive(xSharedDataMutex);
      sendPackedToSTM32(false ,dis, angle);
    }
    else if (autonomous){
      sendPackedToSTM32(false,15,210);
    }
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}