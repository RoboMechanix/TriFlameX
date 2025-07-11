#ifndef TIM_INTERFACE_H
#define TIM_INTERFACE_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "../../UTIL/BIT_MATH.h"
#include <stm32f103xb.h>


void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency);
void TIM_writePWM(TIM_TypeDef *TIMX, uint8_t channel, float dutyCycle);
void TIM_initDelay(TIM_TypeDef *TIMX, uint16_t minTime_ms);
void TIM_delay(TIM_TypeDef *TIMX, uint32_t delay_ms);
void TIM_delay_long(TIM_TypeDef *TIMX, uint32_t delay_ms);
void TIM_callback(TIM_TypeDef *TIMX, float minTimeMs, float time, void (*application)()); // we can change the callback function to be anything
void TIM_initMillis(TIM_TypeDef *TIMX, uint16_t trigTime_ms);
uint64_t TIM_Millis();
#endif
