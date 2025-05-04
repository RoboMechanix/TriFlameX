/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
void GPIO_Init(void) {
    // Enable clock for GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Set PA0 as Alternate Function Push-Pull (AFPP) for PWM
    GPIOA->CRL &= 0;          // Clear mode bits for PA0
    GPIOA->CRL |= GPIO_CRL_MODE0_1;         // Set PA0 as output at 2 MHz
    GPIOA->CRL |= GPIO_CRL_CNF0_1;          // Set PA0 to alternate function
}
int main(void)
{

	GPIO_Init();
	TIM_initPWM(TIM2, 1, 100);
	TIM_writePWM(TIM2, 1, 1);
	while (1)
	{

	}

}

