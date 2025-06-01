#ifndef CAR_INTERFACE_H
#define CAR_INTERFACE_H

#include "stm32f103xb.h"
#include "../../MCAL/TIMR/TIM_interface.h"

void CAR_init(TIM_TypeDef *TimxLeft ,uint8_t ChannelLeft, float FrequencyLeft,
              GPIO_TypeDef *DirLeft1, GPIO_TypeDef *DirLeft2, uint8_t DirLeft1Pin, uint8_t DirLeft2Pin,
              TIM_TypeDef *TimxRight ,uint8_t ChannelRight, float FrequencyRight,
              GPIO_TypeDef *DirRight1, GPIO_TypeDef *DirRight2, uint8_t DirRight1Pin, uint8_t DirRight2Pin);

void CAR_forward(float rightSpeed , float leftSpeed);
void CAR_backwards(float rightSpeed , float leftSpeed);
void CAR_right(float leftSpeed, float rightSpeed) ;
void CAR_left(float rightSpeed, float leftSpeed);
void CAR_stop();

#endif
