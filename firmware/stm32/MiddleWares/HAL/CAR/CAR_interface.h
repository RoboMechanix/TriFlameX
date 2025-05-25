#ifndef CAR_INTERFACE_H
#define CAR_INTERFACE_H

#include "stm32f103xb.h"
#include "../../MCAL/TIMR/TIM_interface.h"

void CAR_init(TIM_TypeDef *TimxLeft ,uint8_t ChannelLeft, float FrequencyLeft ,GPIO_TypeDef *DirPin1,uint8_t Dir1pinNumber,TIM_TypeDef *TimxRight ,uint8_t ChannelRight, float FrequencyRight, GPIO_TypeDef *DirPin2,uint8_t Dir2pinNumber) ;
void CAR_forward(float Speed);
void CAR_backwards(float Speed);
void CAR_right(float Speed);
void CAR_left(float Speed);
void CAR_stop();

#endif