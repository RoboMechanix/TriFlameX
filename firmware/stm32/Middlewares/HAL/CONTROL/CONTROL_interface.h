#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H
#include "../CAR/CAR_interface.h"
#include "stm32f103xb.h"
#include "../../MCAL/TIMR/TIM_interface.h"

#define MAX_STEERING_CORRECTION 45


void PD_init_angle(float Kp, float Kd);
void PD_update_angle(float currentAngle, uint64_t time_ms);
void PD_init( float Kp, float Kd);
void PD_update_from_distance(float actualDistance, uint64_t time_ms);
uint8_t PD_update_angle_ret(float currentAngle, uint64_t time_ms);

#endif // CONTROL_INTERFACE_H
