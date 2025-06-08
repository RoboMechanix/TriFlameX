/* Includes ------------------------------------------------------------------*/
#include "main.h"
// === Globals ===
uint64_t current_time_ms = 1;


// === Variables ===
float distance = 0.0f;
float angle = 0.0f;
float realangle = 0.0f;
int dir= 0;
uint8_t command;

char c;
int x=0;


// Dummy delay (for simulation only)
void delay_ms(uint32_t ms) {
	for (volatile uint32_t i = 0; i < ms * 1000; i++) {
		__asm("NOP");
	}
}


int main(void) {

	UART_init(1,BAUDRATE);

	// === Left Motor (TIM3, PA4/PA5) ===
	TIM_TypeDef *leftTimer = TIM3;
	uint8_t leftChannel = 2;
	GPIO_TypeDef *leftDir1Port = GPIOA;
	uint8_t leftDir1Pin = 4;
	GPIO_TypeDef *leftDir2Port = GPIOA;
	uint8_t leftDir2Pin = 5;

	// === Right Motor (TIM4, PB6/PB7) ===
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

	// === Initialize PD controllers ===
	PD_init(0.4f, 2.0f);        // Distance PD
	PD_init_angle(2.0f, 1.0f);  // Angle control gains

	while (1) {

		delay_ms(1);
		//CAR_forward(100,100);

		UARTMessage msg;
		do {
			 msg = UART_receive_message(1);
		}
		while (msg.type== MSG_NONE);

		distance = msg.distance;
		angle = msg.angle;
		command= msg.command;
		dir = msg.dir;

		if (!command){
			CAR_stop();
			continue;
		}

		distance = dir? -distance : distance ;

		PD_update_angle(angle,1000);
		if(distance!=0){
			PD_update_from_distance(distance, current_time_ms);
		}


	}

}

