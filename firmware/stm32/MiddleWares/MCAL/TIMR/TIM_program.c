#include "TIM_interface.h"

void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency){
	if (channel < 1 || channel > 4){
		return;
	}
    // init clock
	if (TIMX == TIM2) {
		SET_BIT(RCC->APB1ENR, 0);
		switch (channel){
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		}
    } else if (TIMX == TIM3) {
		SET_BIT(RCC->APB1ENR, 1);
		switch (channel){
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		}
    } else if (TIMX == TIM4) {
		SET_BIT(RCC->APB1ENR, 2);
		switch (channel){
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		}
    }

	// direction
	CLEAR_BIT(TIMX->CR1, 4);
	// mode 'edge aligned'
	CLEAR_BIT(TIMX->CR1, 5);
	CLEAR_BIT(TIMX->CR1, 6);
	// set the ARR preload
	SET_BIT(TIMX->CR1, 7);
	//enable the capture compare corresponding pin
	SET_BIT(TIMX->CCER, (4*(channel-1)));
	// choose the polarity of the pin to active high
	CLEAR_BIT(TIMX->CCER, (4*(channel-1)+1));

	volatile uint32_t *CCMRX;
	uint8_t modChannel = 1;
	if (channel <= 2){
		CCMRX = &TIMX->CCMR1;
		modChannel = channel;
	}else{
		CCMRX = &TIMX->CCMR2;
		modChannel = channel-2;
	}
	// set the channel mode to be output
	CLEAR_BIT(*CCMRX, (8*(modChannel-1)));
	CLEAR_BIT(*CCMRX, (8*(modChannel-1)+1));
	// set the channel preload enable
	SET_BIT(*CCMRX, (8*(modChannel-1)+3));
	// select PWM mode 1
	CLEAR_BIT(*CCMRX, (8*(modChannel-1)+4));
	SET_BIT(*CCMRX, (8*(modChannel-1)+5));
	SET_BIT(*CCMRX, (8*(modChannel-1)+6));

	// setting the psc with zero
	TIMX->PSC = 0;
	// calculating prescaler and arr for specific frequency
	float currentARR = (8000000/((frequency*(TIMX->PSC+1))))-1;
	while (currentARR >= 65536){
		TIMX->PSC += 1;
		currentARR = (8000000/((frequency*(TIMX->PSC+1))))-1;
	}
	TIMX->ARR = currentARR;
	SET_BIT(TIMX->EGR, 0);  // UG: Update Generation
	// start counting
	SET_BIT(TIMX->CR1, 0);
}

void TIM_writePWM(TIM_TypeDef *TIMX, uint8_t channel, float dutyCycle){
	if (channel < 1 || channel > 4 || dutyCycle < 0 || dutyCycle > 100){
		return;
	}
	volatile uint32_t *CCRX;
	if (channel == 1) {
		CCRX = &TIMX->CCR1;
    } else if (channel == 2) {
    	CCRX = &TIMX->CCR2;
    } else if (channel == 3) {
    	CCRX = &TIMX->CCR3;
    } else if (channel == 4) {
    	CCRX = &TIMX->CCR4;
    }
	*CCRX = (dutyCycle/100)*(TIMX->ARR);
}
