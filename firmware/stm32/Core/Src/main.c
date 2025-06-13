/* Includes ------------------------------------------------------------------*/
#include "main.h"

// === Globals ===
uint64_t current_time_ms = 1;
uint8_t is_angle_reached = 0;
uint32_t time = 0, time2 = 0 ;

// Dummy delay (for simulation only)
void delay_ms(uint32_t ms) {
	for (volatile uint32_t i = 0; i < ms * 1000; i++) {
		__asm("NOP");
	}
}

int main(void) {

	UART_init(1, BAUDRATE);

	// === Left Motor (TIM3, PA4/PA5) ===
	TIM_TypeDef *leftTimer = TIM3;
	uint8_t leftChannel = 2;
	GPIO_TypeDef *leftDir1Port = GPIOA;
	uint8_t leftDir1Pin = 4;
	GPIO_TypeDef *leftDir2Port = GPIOA;
	uint8_t leftDir2Pin = 5;

	// === Right Motor (TIM4, PA2/PA3) ===
	TIM_TypeDef *rightTimer = TIM4;
	uint8_t rightChannel = 2;
	GPIO_TypeDef *rightDir1Port = GPIOA;
	uint8_t rightDir1Pin = 2;
	GPIO_TypeDef *rightDir2Port = GPIOA;
	uint8_t rightDir2Pin = 3;

	// === Init Car Motors ===
	CAR_init(leftTimer, leftChannel, PWM_FREQ_HZ, leftDir1Port, leftDir2Port,
			 leftDir1Pin, leftDir2Pin, rightTimer, rightChannel, PWM_FREQ_HZ,
			 rightDir1Port, rightDir2Port, rightDir1Pin, rightDir2Pin);

	// === Init Millisecond Timer (TIM2 used for timing) ===
	TIM_initMillis(TIM2, 1);  // 1ms resolution

	// === Initialize PD Controllers ===
	PD_init(0.6f, 1.0f);        // Distance PD
	PD_init_angle(2.5f, 1.0f);  // Angle control PD
	UART1_InterruptsInit();

	// green led
	GPIO_pinMode(GPIOB, 8, OUTPUT);
	GPIO_digitalWrite(GPIOB, 8, LOW);

	// yellow led
	GPIO_pinMode(GPIOB, 6, OUTPUT);
	GPIO_digitalWrite(GPIOB, 6, LOW);

	// red led
	GPIO_pinMode(GPIOB, 9, OUTPUT);
	GPIO_digitalWrite(GPIOB, 9, LOW);


	while (1) {

		if (!command) {
			CAR_stop();
			continue;
		}


		if(!is_angle_reached && PD_update_angle_ret(angle)){
			if (TIM_Millis() - time > 1000){
				is_angle_reached = 1;
				delay_ms(700);
				CAR_stop();
			}
		}else if (!is_angle_reached){
			GPIO_digitalWrite(GPIOB, 6, LOW); // yellow low
			GPIO_digitalWrite(GPIOB, 8, LOW); // green low
			GPIO_digitalWrite(GPIOB, 9, HIGH); // red high
			time = TIM_Millis();
		}
		if (is_angle_reached){
			if(PD_update_from_distance_ret(distance)){
				if (TIM_Millis() - time2 > 1000){
					GPIO_digitalWrite(GPIOB, 6, LOW); // yellow low
					GPIO_digitalWrite(GPIOB, 8, HIGH); // green high
					GPIO_digitalWrite(GPIOB, 9, LOW); // red low
					CAR_stop();
				}

			}else{
				GPIO_digitalWrite(GPIOB, 6, HIGH); // yellow high
				GPIO_digitalWrite(GPIOB, 8, LOW); // green low
				GPIO_digitalWrite(GPIOB, 9, LOW); // red low
				time2 = TIM_Millis();
			}
		}
	}
}


