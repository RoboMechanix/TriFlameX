
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    sendCommandToSTM32(MOVECOMMAND::STOP);
}

void sendDistanceToSTM32(int distance_cm){
    if (distance_cm < 0) {
        Serial.println("Invalid distance value");
        return;
    }
    
    stm32Serial.print("Distance: ");
    stm32Serial.print(distance_cm);
    stm32Serial.println(" cm");
}

void sendCommandToSTM32(MOVECOMMAND command){
    if (command == MOVECOMMAND::GO) {
        stm32Serial.println("GO");
    } else if (command == MOVECOMMAND::STOP) {
        stm32Serial.println("STOP");
    } else {
        Serial.println("Unknown command");
    }
}