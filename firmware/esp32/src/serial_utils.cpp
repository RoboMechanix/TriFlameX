
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    setCommandSTM32(MOVECOMMAND::STOP);
}

void sendPackedToSTM32(u16_t distance_cm) {
    if (distance_cm < 0 || distance_cm > 32767) {
        Serial.println("Distance out of range (0-32767)");  //2^15 - 1
        return;
    }

    uint16_t packed = (go_command ? 1 : 0) << 15 | (distance_cm & 0x7FFF);
    stm32Serial.println(packed); 
}

void setCommandSTM32(MOVECOMMAND command) {
    if (command == MOVECOMMAND::GO) {
        go_command = true;
    } else if (command == MOVECOMMAND::STOP) {
        go_command = false;
    }
    else {
        Serial.println("Unknown command");
    }
}

