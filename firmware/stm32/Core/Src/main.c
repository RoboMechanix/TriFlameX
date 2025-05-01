/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../../MiddleWares/MCAL/GPIO/GPIO_interface.h"

int main(void)
{
	GPIO_pinMode(GPIOB, 7, OUTPUT);
	GPIO_pinMode(GPIOA, 6, INPUT_PULLDOWN);
    while (1)
	{
    	if (GPIO_digitalRead(GPIOA, 6)){
    		GPIO_digitalWrite(GPIOB, 7, HIGH);
    	}if(!GPIO_digitalRead(GPIOB, 6)){
    		GPIO_digitalWrite(GPIOB, 7, LOW);
    	}
	}

}
