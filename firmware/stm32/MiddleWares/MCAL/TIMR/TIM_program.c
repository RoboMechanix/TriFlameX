#include "TIM_interface.h"

void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency){
	if (channel < 1 || channel > 4){
		return;
	}
	// init clock and corresponding pin in the GPIO
	if (TIMX == TIM2) {
	    SET_BIT(RCC->APB1ENR, 0); // Enable TIM2 clock
	    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
	    switch (channel) {
	    case 1: // PA0
	        GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
	        GPIOA->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1); // 2 MHz, AF PP
	        break;
	    case 2: // PA1
	        GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
	        GPIOA->CRL |= (GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1);
	        break;
	    case 3: // PA2
	        GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	        GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);
	        break;
	    case 4: // PA3
	        GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
	        GPIOA->CRL |= (GPIO_CRL_MODE3_1 | GPIO_CRL_CNF3_1);
	        break;
	    }
	} else if (TIMX == TIM3) {
	    SET_BIT(RCC->APB1ENR, 1); // Enable TIM3 clock
	    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN; // Enable GPIOA & GPIOB
	    switch (channel) {
	    case 1: // PA6
	        GPIOA->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
	        GPIOA->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1);
	        break;
	    case 2: // PA7
	        GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
	        GPIOA->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1);
	        break;
	    case 3: // PB0
	        GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
	        GPIOB->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1);
	        break;
	    case 4: // PB1
	        GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
	        GPIOB->CRL |= (GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1);
	        break;
	    }
	} else if (TIMX == TIM4) {
	    SET_BIT(RCC->APB1ENR, 2); // Enable TIM4 clock
	    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock
	    switch (channel) {
	    case 1: // PB6
	        GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
	        GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1);
	        break;
	    case 2: // PB7
	        GPIOB->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
	        GPIOB->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1);
	        break;
	    case 3: // PB8
	        GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
	        GPIOB->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_CNF8_1);
	        break;
	    case 4: // PB9
	        GPIOB->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
	        GPIOB->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1);
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

void TIM_initDelay(TIM_TypeDef *TIMX, uint16_t minTime){

}

void TIM_delay(TIM_TypeDef *TIMX, uint32_t delay_ms){
		TIMX->CR1 = 0;
	    TIMX->CNT = 0;
		TIMX->PSC = 8000-1;
		TIMX->ARR = delay_ms-1;
		TIMX->CR1 |= TIM_CR1_CEN;
		while(!(TIMX->SR & TIM_SR_UIF));
		TIMX->SR &= ~TIM_SR_UIF;
		TIMX->CR1 &= ~TIM_CR1_CEN;    // Stop timer
}

void TIM_delay_long(TIM_TypeDef *TIMX, uint32_t delay_ms) { // use it when delay > 65 Seconds
    while (delay_ms > 0) {
        uint32_t chunk = (delay_ms > 65000) ? 65000 : delay_ms;
        TIM_delay(TIMX, chunk);
        delay_ms -= chunk;
    }
}

