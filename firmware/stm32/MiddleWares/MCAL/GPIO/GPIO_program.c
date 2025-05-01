#include "GPIO_interface.h"

void GPIO_pinMode(GPIO_TypeDef *GPIOX, uint8_t pinNumber, GPIO_MODE mode){
	if (pinNumber < 0 || pinNumber > 15){
		return;
	}
	// Initialize the clock of port x
    if (GPIOX == GPIOA) {
		SET_BIT(RCC->APB2ENR, 2);
    } else if (GPIOX == GPIOB) {
		SET_BIT(RCC->APB2ENR, 3);
    } else if (GPIOX == GPIOC) {
		SET_BIT(RCC->APB2ENR, 4);
    } else if (GPIOX == GPIOD){
    	SET_BIT(RCC->APB2ENR, 5);
    } else if (GPIOX == GPIOE){
    	SET_BIT(RCC->APB2ENR, 6);
    }
	volatile uint8_t pinIndex = pinNumber % 8;

	volatile uint32_t *CRX;
	if (pinNumber < 8 && pinNumber >= 0){
		CRX = &GPIOX->CRL;
	}else if(pinNumber >= 8 && pinNumber < 16){
		CRX = &GPIOX->CRH;
	}
	// Zero the CRX register
	*CRX &= 0;
	if (mode == OUTPUT){
		if (pinIndex == 0){
			*CRX |= (0x2 << 0);
		}else{
			*CRX |= (0x2 << (4*(pinIndex)));
		}
	}else if (mode == INPUT_FLOAT){
		if (pinIndex == 0){
			*CRX |= (0x4 << 0);
		}else{
			*CRX |= (0x4 << (4*(pinIndex)));
		}
	}else if (mode == INPUT_PULLUP){
		if (pinIndex == 0){
			*CRX |= (0x8 << 0);
		}else{
			*CRX |= (0x8 << (4*(pinIndex)));
		}
		SET_BIT(GPIOX->ODR, pinNumber);
	}else if (mode == INPUT_PULLDOWN){
		if (pinIndex == 0){
			*CRX |= (0x8 << 0);
		}else{
			*CRX |= (0x8 << (4*(pinIndex)));
		}
		CLEAR_BIT(GPIOX->ODR, pinNumber);
	}
}

void GPIO_digitalWrite(GPIO_TypeDef *GPIOX, uint8_t pinNumber, PIN_LEVEL level){
	if (pinNumber < 0 || pinNumber > 15){
		return;
	}
	if (level == HIGH){
		SET_BIT(GPIOX->ODR, pinNumber);
	}else if(level == LOW){
		CLEAR_BIT(GPIOX->ODR, pinNumber);
	}
}

uint8_t GPIO_digitalRead(GPIO_TypeDef *GPIOX, uint8_t pinNumber){
	if (pinNumber < 0 || pinNumber > 15){
		return 99;
	}
	return READ_BIT(GPIOX->IDR, pinNumber);
}

void GPIO_digitalToggle(GPIO_TypeDef *GPIOX, uint8_t pinNumber){
	if (pinNumber < 0 || pinNumber > 15){
		return;
	}
	TOGGLE_BIT(GPIOX->ODR, pinNumber);
}
