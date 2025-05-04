/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../../MiddleWares/MCAL/TIMR/TIM_interface.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"

int main(void)
{
	GPIO_pinMode(GPIOB, 7, OUTPUT);
	GPIO_pinMode(GPIOA, 6, INPUT_PULLUP);
	TIM_initPWM(TIM2, 1, 100);
	while (1)
	{
		if (GPIO_digitalRead(GPIOA, 6)){
			TIM_writePWM(TIM2, 1, 1);
//			GPIO_digitalWrite(GPIOB, 7, HIGH);
		}if(!GPIO_digitalRead(GPIOA, 6)){
			TIM_writePWM(TIM2, 1, 50);
//			GPIO_digitalWrite(GPIOB, 7, LOW);
		}
	}

}

