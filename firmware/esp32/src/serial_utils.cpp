
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
}
