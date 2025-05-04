#ifndef TIM_INTERFACE_H
#define TIM_INTERFACE_H

#include "stm32f1xx_hal.h"
#include "../../UTIL/BIT_MATH.h"

void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency);
void TIM_writePWM(TIM_TypeDef *TIMX, uint8_t channel, float dutyCycle);

#endif
