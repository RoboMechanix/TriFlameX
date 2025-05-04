#ifndef TIM_INTERFACE_H
#define TIM_INTERFACE_H

#include "stm32f1xx_hal.h"
#include "../../UTIL/BIT_MATH.h"

void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency);
void TIM_writePWM(TIM_TypeDef *TIMX, uint8_t channel, float dutyCycle);
void TIM_initDelay(TIM_TypeDef *TIMX, uint16_t minTime);
void TIM_delay(TIM_TypeDef *TIMX, uint32_t delay_ms);
void TIM_delay_long(TIM_TypeDef *TIMx, uint32_t delay_ms);


#endif
