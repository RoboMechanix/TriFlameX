#pragma once
#include <main.h>

#define baudrate 115200

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);