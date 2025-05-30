#ifndef BLSER_INTERFACE_H
#define BLSER_INTERFACE_H

#include "Arduino.h"
#define print_counter false
#define kp 4.0
#define kd 2.0
#define tolerance 1
#define angle_per_step 1.8

extern volatile int counter;
extern volatile bool is_cw;

void BLSER_init(uint8_t pwm_pin, uint8_t dir_pin, uint8_t encA, uint8_t encB);
void BLSER_moveTo(float angle);
void IRAM_ATTR handleInterrupt();

#endif