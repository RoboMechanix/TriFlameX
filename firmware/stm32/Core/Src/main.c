/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"

float map(float val, float from1, float to1, float from2, float to2){
	return (val/(to1-from1)*(to2-from1));
}

void ADC_init(){
	RCC->APB2ENR |= (1 << 9); // start the clock
	ADC1->CR2 |= (1 << 0); // power the adc
	for (volatile int i = 0; i < 1000; i++) {
	    // Delay loop, intentionally empty
	}
	ADC1->CR2 |= (1 << 0); // repower the adc
    ADC1->CR2 &= ~(1 << 11);   // Right alignment by default
	ADC1->CR2 |= (1 << 1); // continuous conversion
	ADC1->CR2 |= (1 << 2); // calibrate
	while (ADC1->CR2 & (1 << 2)); // wait for the calibration
	ADC1->SMPR2 |= (3 << 0); // sampling cycles of 28.5 cycles
	ADC1->SQR1 &= ~(0xF << 20); // choose length of 1 conversion
	ADC1->SQR3 |= (0 << 0); // choose the order
	ADC1->CR2 |= (1 << 22); // start conversion
}
uint16_t read_ADC(){
    while (!(ADC1->SR & (1 << 1))); // Wait for EOC
    ADC1->SR &= ~(1 << 1);          // Clear EOC flag
    return ADC1->DR;
}


int main(void)
{
//	RCC->APB2ENR |= (1 << 2) | (1 << 3); // CLK PA, PB
//	GPIOA->CRL &= 0;
//	GPIOB->CRL &= 0;
//	GPIOA->CRL |= 0x44444440; // pin A0 analog input
//	ADC_init();
//	GPIO_pinMode(GPIOA, 6, INPUT_PULLUP);
//	TIM_initPWM(TIM4, 4, 100);
	GPIO_pinMode(GPIOB, 12, OUTPUT);
	TIM_initDelay(TIM2, 10);
	while (1)
	{
//		uint16_t reading = read_ADC();
//		reading = map(reading, 0, 4095, 0, 100);
//		if (GPIO_digitalRead(GPIOA, 6)){
//			TIM_writePWM(TIM4, 4, reading);
//		}if(!GPIO_digitalRead(GPIOA, 6)){
//			TIM_writePWM(TIM4, 4, reading);
//		}
		GPIO_digitalWrite(GPIOB, 12, HIGH);
		TIM_delay(TIM2, 100);
		GPIO_digitalWrite(GPIOB, 12, LOW);
		TIM_delay(TIM2, 100);
	}

}

