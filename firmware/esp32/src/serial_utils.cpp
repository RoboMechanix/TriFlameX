
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    setCommandSTM32(MOVECOMMAND::STOP);
}

void sendPackedToSTM32(bool direction, u16_t distance, int8_t angle) {
    if (distance > 16383 || angle < -127 || angle > 127) {
        Serial.println("Invalid distance or angle range");
        return;
    }

    uint8_t buffer[6];
    buffer[0] = START_BYTE;

    // Pack bits: [command:1][dir:1][distance:14][sign:1][angle:7]
    uint32_t packed = 0;
    packed |= ((go_command ? 1 : 0) & 0x01) << 23;           
    packed |= ((direction ? 1 : 0) & 0x01) << 22;            
    packed |= (distance & 0x3FFF) << 8;                      
    packed |= ((angle < 0 ? 1 : 0) & 0x01) << 7;             
    packed |= (abs(angle) & 0x7F);                           

    buffer[1] = (packed >> 16) & 0xFF;
    buffer[2] = (packed >> 8) & 0xFF;
    buffer[3] = packed & 0xFF;
    buffer[5] = END_BYTE;

    // Checksum = XOR of payload bytes
    buffer[4] = buffer[1] ^ buffer[2] ^ buffer[3];

    stm32Serial.write(buffer, sizeof(buffer));

    // Wait for ACK
    unsigned long start = millis();
    while (millis() - start < 100) {
        if (stm32Serial.available()) {
            uint8_t ack = stm32Serial.read();
            if (ack == ACK_BYTE) {
                Serial.println("ACK received from STM32");
                return;
            }
        }
    }
    Serial.println("⚠️ No ACK received");
}


void setCommandSTM32(MOVECOMMAND command) {
    switch (command) {

    case MOVECOMMAND::GO:
        xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
        go_command = true; 
        isAutonomous = true;
        xSemaphoreGive(xSharedDataMutex);
        break;

    case MOVECOMMAND::STOP:
        xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
        go_command = false; 
        isAutonomous = true;
        xSemaphoreGive(xSharedDataMutex);
        break;

    case MOVECOMMAND::ManualMode:
        xSemaphoreTake(xSharedDataMutex,portMAX_DELAY);
        isAutonomous = false;
        xSemaphoreGive(xSharedDataMutex);
        break;

    default:
        Serial.println("Unknown command");
  }
}

