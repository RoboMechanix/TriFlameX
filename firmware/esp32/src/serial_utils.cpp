
#include <main.h>

void setupSTM32Serial(HardwareSerial& serial, int rxPin, int txPin) {
    serial.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    setCommandSTM32(MOVECOMMAND::STOP);
}

void sendPackedToSTM32(uint16_t distance_cm, int8_t angle_deg) {
    if (distance_cm > 32767) {
        Serial.println("❌ Distance out of range (0–32767)");
        return;
    }

    if (angle_deg < -127 || angle_deg > 127) {
        Serial.println("❌ Angle out of range (-127 to 127)");
        return;
    }

    uint8_t angle_sign = (angle_deg < 0) ? 1 : 0;
    uint8_t angle_mag = abs(angle_deg) & 0x7F;

    // Pack data
    uint32_t packed = 0;
    packed |= ((go_command ? 1 : 0) << 23);       // Command bit
    packed |= ((distance_cm & 0x7FFF) << 8);      // 15-bit distance
    packed |= ((angle_sign & 0x01) << 7);         // Sign bit
    packed |= (angle_mag & 0x7F);                 // Angle magnitude

    // Send as 3 bytes (MSB first)
    stm32Serial.write((packed >> 16) & 0xFF);
    stm32Serial.write((packed >> 8) & 0xFF);
    stm32Serial.write(packed & 0xFF);
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

