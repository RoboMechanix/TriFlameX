#ifndef SER_INTERFACE_H
#define SER_INTERFACE_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "../../UTIL/BIT_MATH.h"
#include "../../MCAL/TIMR/TIM_interface.h"

void SER_init(TIM_TypeDef *TIMX, uint8_t channel);
void SER_write(TIM_TypeDef *TIMX, uint8_t channel, uint8_t angle);

#endif
