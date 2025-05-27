#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H
#include "../CAR/CAR_interface.h"
#include "stm32f103xb.h"
#include "../../MCAL/TIMR/TIM_interface.h"
void PD_init( float Kp, float Kd);
void PD_update_from_distance(float actualDistance, uint64_t time_ms);

#endif // CONTROL_INTERFACE_H
