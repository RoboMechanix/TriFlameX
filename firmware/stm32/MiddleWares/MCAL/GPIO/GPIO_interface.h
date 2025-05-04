#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "../../UTIL/BIT_MATH.h"

typedef enum{
	INPUT_PULLUP,
	INPUT_PULLDOWN,
	INPUT_FLOAT,
	OUTPUT
}GPIO_MODE;

typedef enum{
	HIGH,
	LOW
}PIN_LEVEL;

void GPIO_pinMode(GPIO_TypeDef *GPIOX, uint8_t pinNumber, GPIO_MODE mode);
void GPIO_digitalWrite(GPIO_TypeDef *GPIOX, uint8_t pinNumber, PIN_LEVEL level);
void GPIO_digitalToggle(GPIO_TypeDef *GPIOX, uint8_t pinNumber);
uint8_t GPIO_digitalRead(GPIO_TypeDef *GPIOX, uint8_t pinNumber);

#endif
