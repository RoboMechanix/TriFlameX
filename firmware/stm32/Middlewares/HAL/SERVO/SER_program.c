#include "SER_interface.h"

void SER_init(TIM_TypeDef *TIMX, uint8_t channel){
	if (channel < 1 || channel > 4){
		return;
	}
	TIM_initPWM(TIMX, channel, 50); // set frequency to 50 HZ
}

void SER_write(TIM_TypeDef *TIMX, uint8_t channel, uint8_t angle){
	if (channel < 1 || channel > 4){
		return;
	}
	// equation to convert angle to duty cycle
	float dutyCycle = ((float)angle)/18 + 2.5;
	TIM_writePWM(TIMX, channel, dutyCycle);
}
