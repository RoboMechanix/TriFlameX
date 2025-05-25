#pragma once
#include <HardwareSerial.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin, int baudrate = 115200) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
}
