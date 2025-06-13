/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

// === Globals ===
uint64_t current_time_ms = 1;

// === Variables ===
//float distance = 0.0f;
//float angle = 0.0f;
float realangle = 0.0f;

char c;
char uart_rx_buffer[UART_BUFFER_SIZE];
int uart_rx_index = 0;
int x = 0;

volatile uint8_t uart_line_ready = 0;
char uart_rx_buffer_copy[UART_BUFFER_SIZE];  // Used by main loop/task

// Function prototypes
//void UART_Init(void);
//char UART_ReadChar(void);
//int UART_ReadLine(char *buffer, int max_len);
void PD_Distance_Task(void *pvParameters);
void PD_Angle_Task(void *pvParameters);
//void UART_Parse_Task(void *pvParameters);

// Dummy delay (for simulation only)
void delay_ms(uint32_t ms) {
	for (volatile uint32_t i = 0; i < ms * 1000; i++) {
		__asm("NOP");
	}
}

int main(void) {
	// Initialize UART
	UART_init(1, BAUDRATE);
	UART1_InterruptsInit();

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
	// green led
	GPIO_pinMode(GPIOB, 8, OUTPUT);
	GPIO_digitalWrite(GPIOB, 8, LOW);

	// yellow led
	GPIO_pinMode(GPIOB, 6, OUTPUT);
	GPIO_digitalWrite(GPIOB, 6, LOW);

	// red led
	GPIO_pinMode(GPIOB, 9, OUTPUT);
	GPIO_digitalWrite(GPIOB, 9, LOW);

	// === Init Car Motors ===
	CAR_init(leftTimer, leftChannel, PWM_FREQ_HZ, leftDir1Port, leftDir2Port,
			leftDir1Pin, leftDir2Pin, rightTimer, rightChannel, PWM_FREQ_HZ,
			rightDir1Port, rightDir2Port, rightDir1Pin, rightDir2Pin);

	// === Init Millisecond Timer (TIM2 used for timing) ===
	TIM_initMillis(TIM2, 1);  // 1ms resolution
	delay_ms(50);

	// === Initialize PD controllers ===
	PD_init(0.64f, 6.0f);        // Distance PD
	PD_init_angle(0.90f, 0.0f); // Angle control gains

	// === Create FreeRTOS Tasks ===
//	xTaskCreate(UART_Parse_Task, "UARTTask", 128, NULL, 1, NULL);
	xTaskCreate(PD_Distance_Task, "DistanceTask", 256, NULL, 2, NULL);
	xTaskCreate(PD_Angle_Task, "AngleTask", 256, NULL, 2, NULL);

	// === Start Scheduler ===
	vTaskStartScheduler();

	// Should never reach here
	while (1)
		;
}

// === Task for PD Distance ===
void PD_Distance_Task(void *pvParameters) {
	while (1) {
		current_time_ms = TIM_Millis();
		if (distance != 0.0f) {
			if (distance > maxDistance)
				PD_init(0.64f, 6.0f);        // Distance PD

			PD_update_from_distance(distance, current_time_ms);
		}
		vTaskDelay(pdMS_TO_TICKS(1)); // Update every 10ms
	}
}

// === Task for PD Angle ===
void PD_Angle_Task(void *pvParameters) {
	while (1) {
		current_time_ms = TIM_Millis();
//		if(angle<100 && angle>80){
//			PD_init(0.0f, 0.0f);        // Distance PD
//
//			PD_init_angle(.0f, 0.0f);}
//		else {
//			PD_init(0.7f, 9.0f);        // Distance PD
//
//			PD_init_angle(1.3f, 0.0f);
//		}
		if (!command) {
			CAR_stop();
		} else
			PD_update_angle(angle, current_time_ms);

		vTaskDelay(pdMS_TO_TICKS(1

		)); // Update every 10ms
	}
}

// === UART Parser Task ===

