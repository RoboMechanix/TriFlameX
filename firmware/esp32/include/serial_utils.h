#pragma once
#include <main.h>

#define baudrate 115200

enum class MOVECOMMAND{
    GO,
    STOP,
};

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);
void sendDistanceToSTM32(int distance_cm);
void sendCommandToSTM32(MOVECOMMAND command);