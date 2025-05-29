#pragma once
#include <main.h>

#define baudrate 115200

enum class MOVECOMMAND{
    GO,
    STOP,
};

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);
void setCommandSTM32(MOVECOMMAND command);
void sendPackedToSTM32(u16_t distance_cm);

/*
* Bit layout: [Command Bit][15-bit Distance]
* min distance = 0
* max distance = 32767
* Command Bit: 0 = STOP, 1 = GO
*/