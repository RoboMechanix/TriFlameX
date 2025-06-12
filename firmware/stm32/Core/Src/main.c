/* Includes ------------------------------------------------------------------*/
#include "main.h"

// === Globals ===
uint64_t current_time_ms = 1;



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
	PD_init(0.4f, 2.0f);        // Distance PD
	PD_init_angle(2.0f, 1.0f);  // Angle control PD
	UART1_InterruptsInit();


	while (1) {
		delay_ms(1);  // ~1ms delay


		if (!command) {
			CAR_stop();
			continue;
		}

//		if (dir) {
//			distance *= -1;
//		}

		PD_update_angle(angle, 69);  // 69 might be the actual angle from IMU

		if (distance != 0) {
			PD_update_from_distance(distance, current_time_ms);
		}
	}
}


