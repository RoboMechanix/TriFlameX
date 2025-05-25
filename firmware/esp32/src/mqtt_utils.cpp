#include <main.h>


void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String command = "";
    for (unsigned int i = 0; i < length; i++) {
        command += (char)payload[i];
    }
    Serial.println("Received from laptop: " + command);
    stm32Serial.println(command);  // Forward to STM32
}

void setupMQTT(const char* server, const char* client_id, const char* topic) {
    client.setServer(server, 1883);
    client.setCallback(mqttCallback);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");

        if (client.connect(client_id)) {
            Serial.println("connected.");
            client.subscribe(topic);
        } else {
            Serial.print("failed. rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 2 seconds");
    
            blink_led(3,200); //blink LED three times (200ms on duration) to show that MQTT server connection attempt failed
            // Wait 2 seconds before retrying
            delay(2000);
          
        }
    }
}

void connect_mqttServer() {
    if (!client.connected()) {
        setupMQTT(mqtt_server, mqtt_client_id, mqtt_topic);
    }
    client.loop();
    delay(1000);
    return;
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic).equals(mqtt_topic)) {
      if(messageTemp == "10"){
        Serial.println("Action: blink LED");
        blink_led(1,1250); //blink LED once (for 1250ms ON time)
      }
  }

}

