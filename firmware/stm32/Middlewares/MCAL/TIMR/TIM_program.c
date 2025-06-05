#include "TIM_interface.h"

volatile uint16_t *preload;
volatile uint16_t preload2;
volatile uint16_t preload3;
volatile uint16_t preload4;
volatile uint16_t *n;
volatile uint16_t n2;
volatile uint16_t n3;
volatile uint16_t n4;
volatile uint16_t *counter;
volatile uint16_t counter2;
volatile uint16_t counter3;
volatile uint16_t counter4;
volatile void (*callback2)();
volatile void (*callback3)();
volatile void (*callback4)();
uint64_t millis = 0;
uint16_t trigTime_ms_global;
int isFirstTime = 1;

void TIM_initPWM(TIM_TypeDef *TIMX, uint8_t channel, float frequency) {
	if (channel < 1 || channel > 4) {
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

	// direction upward
	CLEAR_BIT(TIMX->CR1, 4);
	// mode 'edge aligned'
	CLEAR_BIT(TIMX->CR1, 5);
	CLEAR_BIT(TIMX->CR1, 6);
	// set the ARR preload
	SET_BIT(TIMX->CR1, 7);
	//enable the capture compare corresponding pin
	SET_BIT(TIMX->CCER, (4 * (channel - 1)));
	// choose the polarity of the pin to active high
	CLEAR_BIT(TIMX->CCER, (4 * (channel - 1) + 1));

	volatile uint32_t *CCMRX;
	uint8_t modChannel = 1;
	if (channel <= 2) {
		CCMRX = &TIMX->CCMR1;
		modChannel = channel;
	} else {
		CCMRX = &TIMX->CCMR2;
		modChannel = channel - 2;
	}
	// set the channel mode to be output
	CLEAR_BIT(*CCMRX, (8 * (modChannel - 1)));
	CLEAR_BIT(*CCMRX, (8 * (modChannel - 1) + 1));
	// set the channel preload enable
	SET_BIT(*CCMRX, (8 * (modChannel - 1) + 3));
	// select PWM mode 1
	CLEAR_BIT(*CCMRX, (8 * (modChannel - 1) + 4));
	SET_BIT(*CCMRX, (8 * (modChannel - 1) + 5));
	SET_BIT(*CCMRX, (8 * (modChannel - 1) + 6));

	// setting the psc with zero
	TIMX->PSC = 0;
	// calculating prescaler and arr for specific frequency
	float currentARR = (8000000 / ((frequency * (TIMX->PSC + 1)))) - 1;
	while (currentARR >= 65536) {
		TIMX->PSC += 1;
		currentARR = (8000000 / ((frequency * (TIMX->PSC + 1)))) - 1;
	}
	TIMX->ARR = currentARR;
	SET_BIT(TIMX->EGR, 0);  // UG: Update Generation
	// start counting
	SET_BIT(TIMX->CR1, 0);
}

void TIM_writePWM(TIM_TypeDef *TIMX, uint8_t channel, float dutyCycle) {
	if (channel < 1 || channel > 4 || dutyCycle < 0 || dutyCycle > 100) {
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
	*CCRX = (dutyCycle / 100) * (TIMX->ARR);
}

void TIM_initDelay(TIM_TypeDef *TIMX, uint16_t minTime_ms) {
	enableTimerClock(TIMX);
	uint32_t clk_freq = 8000000; // 8 MHz
	uint32_t target_ticks = minTime_ms * 1000; // Convert minTime_ms to microseconds

	uint16_t prescaler = 0;
	uint32_t arr = 0;

	// Try to find the smallest prescaler that gives ARR <= 65535
	for (prescaler = 1; prescaler <= 0xFFFF; prescaler++) {
		arr = (clk_freq / prescaler) * minTime_ms / 1000;
		if (arr <= 0xFFFF)
			break;
	}

	if (prescaler > 0xFFFF) {
		return;
	}

	TIMX->CR1 = 0;
	TIMX->PSC = prescaler - 1;
	TIMX->ARR = arr - 1;
	TIMX->EGR = TIM_EGR_UG;
	TIMX->CNT = 0;
	TIMX->SR &= ~TIM_SR_UIF;
	TIMX->CR1 |= TIM_CR1_CEN;

}

void TIM_delay(TIM_TypeDef *TIMX, uint32_t delay_ms) {
	enableTimerClock(TIMX);
	TIMX->CR1 = 0;
	TIMX->CNT = 0;
	TIMX->PSC = 8000 - 1;
	TIMX->ARR = delay_ms - 1;
	TIMX->CR1 |= TIM_CR1_CEN;
	while (!(TIMX->SR & TIM_SR_UIF))
		;
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

void enableTimerClock(TIM_TypeDef *TIMx) {
	switch ((uint32_t) TIMx) {
	case (uint32_t) TIM1:
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		break;
	case (uint32_t) TIM2:
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		break;
	case (uint32_t) TIM3:
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		break;
	case (uint32_t) TIM4:
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		break;
	default:
		break;
	}
}

void TIM_callback(TIM_TypeDef *TIMX, float minTimeMs, float timeMs,
		void (*application)()) { // we can change the callback function to be anything
	// till now the mintime doesn't do anything
	// init clock and the corresponding timer's interrupt
	if (TIMX == TIM2) {
		SET_BIT(RCC->APB1ENR, 0); // Enable TIM2 clock
		SET_BIT(TIMX->DIER, 0); // Enable update interrupt (UIE)
		// enable interrupt
		NVIC_EnableIRQ(TIM2_IRQn);
		// set interrupt priority
		NVIC_SetPriority(TIM2_IRQn, 1);
		counter = &counter2;
		preload = &preload2;
		n = &n2;
		callback2 = application;
	} else if (TIMX == TIM3) {
		SET_BIT(RCC->APB1ENR, 1); // Enable TIM3 clock
		SET_BIT(TIMX->DIER, 0); // Enable update interrupt (UIE)
		// enable interrupt
		NVIC_EnableIRQ(TIM3_IRQn);
		// set interrupt priority
		NVIC_SetPriority(TIM3_IRQn, 1);
		counter = &counter3;
		preload = &preload3;
		n = &n3;
		callback3 = application;
	} else if (TIMX == TIM4) {
		SET_BIT(RCC->APB1ENR, 2); // Enable TIM4 clock
		SET_BIT(TIMX->DIER, 0); // Enable update interrupt (UIE)
		// enable NVIC interrupt
		NVIC_EnableIRQ(TIM4_IRQn);
		// set interrupt priority
		NVIC_SetPriority(TIM4_IRQn, 1);
		counter = &counter4;
		preload = &preload4;
		n = &n4;
		callback4 = application;
	}
	// direction upward
	CLEAR_BIT(TIMX->CR1, 4);
	// mode 'edge aligned'
	CLEAR_BIT(TIMX->CR1, 5);
	CLEAR_BIT(TIMX->CR1, 6);

//	uint32_t prescaler = ((minTimeMs*4000.0) - 1);
//	uint32_t arr = 1; // the arr should be >= 1
//	if (prescaler > 65535){
//		prescaler = 65535;
//		arr = ((minTimeMs*8000)/(prescaler + 1)) - 1;
//		if (arr > 65535){ // we won't reach this case unless the minimum time was more than 8 minutes
//			arr = 65535;
//		}
//	}

	uint32_t prescaler = 255;
	uint32_t arr = 100;

	TIMX->ARR = (uint16_t) arr;
	TIMX->PSC = prescaler;
	uint32_t arr_new = ((timeMs * 8000) / (TIMX->PSC + 1)) - 1;
	if (arr_new <= TIMX->ARR) {
		TIMX->ARR = (uint16_t) arr_new;
		*n = 1;
	} else {
		float div = ((float) (arr_new + 1)) / ((float) (TIMX->ARR + 1));
		*n = (uint16_t) div;
		*preload = (uint16_t) (((1 - (div - (float) (*n))))
				* ((float) (TIMX->ARR + 1))); // watch out we need old n
		*n = *n + 1; // due to the preload the interrupt number should increase by 1
		TIMX->CNT = *preload;
	}

	// start counting
	SET_BIT(TIMX->CR1, 0);
}
void TIM_initMillis(TIM_TypeDef *TIMX, uint16_t trigTime_ms) {
	enableTimerClock(TIMX);
	TIMX->CR1 = 0;
	trigTime_ms_global = trigTime_ms;
	TIMX->CCER |= TIM_CCER_CC1E;
	TIMX->DIER |= TIM_DIER_CC1IE;
	TIMX->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIMX->CNT = 0;
	TIMX->PSC = 8000 - 1;
	TIMX->ARR = (60000) - 1;
	if (TIMX == TIM2) {
		NVIC_EnableIRQ(TIM2_IRQn);
	} else if (TIMX == TIM3) {
		NVIC_EnableIRQ(TIM3_IRQn);
	} else if (TIMX == TIM4) {
		NVIC_EnableIRQ(TIM4_IRQn);
	}

	TIMX->CR1 |= TIM_CR1_CEN;
	TIMX->CCR1 = TIMX->CNT + trigTime_ms_global;

}

uint64_t TIM_Millis() {
	if (isFirstTime) {
		isFirstTime = 0;
		millis = 0;
	}
	return millis;
}

void TIM2_IRQHandler() {
	if (TIM2->SR & TIM_SR_CC1IF) {
		TIM2->SR &= ~TIM_SR_CC1IF;
		TIM2->CCR1 = TIM2->CNT + trigTime_ms_global;
		millis++;
//		if (isFirstTime) {
//			isFirstTime = 0;
//			millis = 0;
//		}
	}
	if ((TIM2->SR & (1 << 0)) == 1) { // check the uif flag
		TIM2->SR &= ~(1 << 0); // clear the uif
		counter2++;
		if (counter2 == n2) {
			counter2 = 0;
			TIM2->CNT = preload2; // set the preload
			callback2();
		}
	}
}

void TIM3_IRQHandler() {
	if ((TIM3->SR & (1 << 0)) == 1) { // check the uif flag
		if (TIM3->SR & TIM_SR_CC1IF) {
			TIM3->SR &= ~TIM_SR_CC1IF;
			TIM3->CCR1 = TIM3->CNT + trigTime_ms_global;
			millis++;
//			if (isFirstTime) {
//				isFirstTime = 0;
//				millis = 0;
//			}
		}
		if ((TIM3->SR & (1 << 0)) == 1) {
			TIM3->SR &= ~(1 << 0); // clear the uif
			counter3++;
			if (counter3 == n3) {
				counter3 = 0;
				TIM3->CNT = preload3; // set the preload
				callback3();
			}
		}
	}
}

void TIM4_IRQHandler() {
	if ((TIM4->SR & (1 << 0)) == 1) { // check the uif flag
		if (TIM4->SR & TIM_SR_CC1IF) {
			TIM4->SR &= ~TIM_SR_CC1IF;
			TIM4->CCR1 = TIM4->CNT + trigTime_ms_global;
			millis++;
//			if (isFirstTime) {
//				isFirstTime = 0;
//				millis = 0;
//			}
		}
		if ((TIM4->SR & (1 << 0)) == 1) {
			TIM4->SR &= ~(1 << 0); // clear the uif
			counter4++;
			if (counter4 == n4) {
				counter4 = 0;
				TIM4->CNT = preload4; // set the preload
				callback4();
			}
		}
	}
}
