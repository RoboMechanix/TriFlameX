#include <main.h>

long lastMsg = 0;

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
        setupMQTT(mqtt_server, mqtt_client_id, mqtt_sub_topic);
    }
    client.loop();
    delay(1000);
    return;
}

void mqttCallback(char* topic, byte* message, unsigned int length) {

    //Serial.print("Message arrived on topic: ");
    //Serial.print(topic);
    //Serial.print(". Message: ");
    String command = "";

    for (unsigned int i = 0; i < length; i++) {
      command += (char)message[i];
    }
    
    //Serial.println("Received from laptop: " + command);

    if (command == "GO") {
        setCommandSTM32(MOVECOMMAND::GO);
        //Serial.println("Sent command to STM32: GO");
    } else if (command == "STOP") {
        setCommandSTM32(MOVECOMMAND::STOP);
        //Serial.println("Sent command to STM32: STOP");
    } else {
        //Serial.println("Unknown command received.");
    }

}

void publishMessage(const char* topic, const String& payload) {

    if (client.connected()) {   
      long now = millis();  
      if (now - lastMsg > 2000) { 
        lastMsg = now;  
      client.publish(topic, payload.c_str());   
      }
    }
}

