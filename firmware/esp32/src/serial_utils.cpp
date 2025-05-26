
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    sendCommandToSTM32(MoveCommand::STOP);
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

void sendCommandToSTM32(MoveCommand command){
    if (command == MoveCommand::GO) {
        stm32Serial.println("GO");
    } else if (command == MoveCommand::STOP) {
        stm32Serial.println("STOP");
    } else {
        Serial.println("Unknown command");
    }
}