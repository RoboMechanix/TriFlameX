/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"
#include "../../MiddleWares/HAL/SERVO/SER_interface.h"

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

void func(){
	GPIOC->ODR ^= (1 << 14); // toggle the led PC14
}

int main(void)
{
//	RCC->APB2ENR |= (1 << 2) | (1 << 3); // CLK PA, PB
//	GPIOA->CRL &= 0;
//	GPIOB->CRL &= 0;
//	GPIOA->CRL |= 0x44444440; // pin A0 analog input
//	ADC_init();
////	TIM_initPWM(TIM2, 1, 50);
//	TIM_initDelay(TIM4, 1);
//	float i = 0;
//	SER_init(TIM2, 1);
	RCC->APB2ENR |= (1 << 4);   // Enable GPIOC clock
	GPIOC->CRH = 0;
	GPIOC->CRH = 0x42444444;    // Set PC14 as output, others default
	TIM_callback(TIM4, 200, 1000, &func); // we can change the callback function to be anything
	while (1)
	{
//		TIM_delay(TIM4, 1000);
//		while (i <= 180){
//			SER_write(TIM2, 1, i);
//			i += 5;
//			TIM_delay(TIM4, 50);
//		}
//		TIM_delay(TIM4, 1000);
//		while (i >= 0){
//			SER_write(TIM2, 1, i);
//			i -= 5;
//			TIM_delay(TIM4, 50);
//		}

	}

}

