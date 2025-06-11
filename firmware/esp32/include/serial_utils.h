#pragma once
#include <main.h>

#define START_BYTE 0xAA
#define END_BYTE   0x55
#define ACK_BYTE   0xCC

#define baudrate 500000

enum class MOVECOMMAND{
    GO,
    STOP,
    ManualMode,
};

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin);
void setCommandSTM32(MOVECOMMAND command);
void sendPackedToSTM32(bool direction, u16_t distance, u8_t angle);
void sendPackedToSTM32Manual(bool command, bool direction, u16_t distance, u8_t angle);

/*
* Bit layout: [Command Bit][15-bit Distance][15-bit distance][sign Bit][7-bit angle]
* min distance = 0
* max distance = 32767
* Command Bit: 0 = STOP, 1 = GO
* sign Bit: 0 = positive angle, 1 = negative angle
* angle range: -127 to 127 degrees
*/