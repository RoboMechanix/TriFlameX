/* Includes ------------------------------------------------------------------*/
#include "main.h"
// === Globals ===
uint64_t current_time_ms = 1;


// === Variables ===
float distance = 0.0f;
float angle = 0.0f;
float realangle = 0.0f;

char c;
// UART buffer for receiving data
char uart_rx_buffer[UART_BUFFER_SIZE];
int uart_rx_index = 0;
int x=0;

// Function prototypes
void UART_Init(void);
char UART_ReadChar(void);
int UART_ReadLine(char *buffer, int max_len);
void UART_SendInt(int32_t num);
void UART_SendString(const char *str);
void UART_SendUInt(uint32_t num);
void IntToStr(int32_t value, char *str);
void FloatToStr(float value, char *str, uint8_t precision);
// Dummy delay (for simulation only)
void delay_ms(uint32_t ms) {
	for (volatile uint32_t i = 0; i < ms * 1000; i++) {
		__asm("NOP");
	}
}

int main(void) {
	// Initialize UART
	UART_Init();

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
	delay_ms(50);

	// === Initialize PD controllers ===
	PD_init(2.0f, 2.5f);        // Distance PD
	PD_init_angle(1.0f, 3.3f);  // Angle control gains

	while (1) {
		// Read one line from UART (blocking until '\n')
		if (UART_ReadLine(uart_rx_buffer, UART_BUFFER_SIZE)) {
			// uart_rx_buffer contains something like: "123.45,67.89"

			// Parse distance and angle
			char *comma_pos = strchr(uart_rx_buffer, ',');
			if (comma_pos != NULL) {
				*comma_pos = 0; // Null terminate distance part
				distance = atof(uart_rx_buffer)/10;
				angle = atof(comma_pos + 1);
//				realangle=angle-90;

				// Optional: Validate values (e.g., distance > 0)
			}
		}

		current_time_ms = TIM_Millis();

//		UART_SendString("");

		if(PD_update_angle_ret(angle, current_time_ms)){
			if(distance!=0){
				PD_update_from_distance(distance, current_time_ms);
			}
		}
//
//		// Use received values instead of simulated
//		if(distance!=0)
//			PD_update_from_distance(distance, current_time_ms);

//		char string[10];
//		FloatToStr(angle, string, 3);
//		UART_SendString("Number: ");
//		UART_SendString(string);
//		UART_SendString("\r\n");
//		delay_ms(1);
	}

	CAR_stop();

	while (1)
		;
}

// --- UART Functions ---

// Initialize USART1 (assuming 72 MHz APB2 clock, 9600 baud)
#include <string.h>
#include <stdint.h>

//#define UART_BUFFER_SIZE 64

//volatile char uart_rx_buffer[UART_BUFFER_SIZE];
//volatile int uart_rx_index = 0;
volatile uint8_t uart_line_ready = 0;

extern char uart_rx_buffer_copy[UART_BUFFER_SIZE];  // For main() to access safely

// Initialize USART1 with RX interrupt enabled
void UART_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    GPIOA->CRH |= (0x3 << GPIO_CRH_MODE9_Pos) | (0x2 << GPIO_CRH_CNF9_Pos);   // PA9: TX
    GPIOA->CRH |= (0x1 << GPIO_CRH_CNF10_Pos);                                 // PA10: RX

    USART1->CR1 &= ~USART_CR1_UE;
    USART1->BRR = 0x0010;  // 500000 baud at 8 MHz
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

    NVIC_EnableIRQ(USART1_IRQn);
}

// Interrupt handler for USART1
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_ORE) {
        volatile uint32_t tmp = USART1->DR;  // Clear ORE by reading DR
        (void)tmp;
    }

    if (USART1->SR & USART_SR_RXNE) {
        char received = (char)(USART1->DR & 0xFF);

        if (received == '\r') return;

        if (received == '\n') {
            uart_rx_buffer[uart_rx_index] = '\0';
            uart_rx_index = 0;
            uart_line_ready = 1;
        } else {
            if (uart_rx_index < UART_BUFFER_SIZE - 1) {
                uart_rx_buffer[uart_rx_index++] = received;
            } else {
                uart_rx_index = 0;  // reset on overflow
            }
        }
    }
}


// Safe read line function to be called from main loop
// Returns 1 if a full line is ready
char uart_rx_buffer_copy[UART_BUFFER_SIZE];  // Used by main

int UART_ReadLine(char *buffer, int max_len) {
    if (uart_line_ready) {
        __disable_irq();
        strncpy((char *)uart_rx_buffer_copy, (char *)uart_rx_buffer, UART_BUFFER_SIZE);
        uart_line_ready = 0;
        __enable_irq();

        strncpy(buffer, uart_rx_buffer_copy, max_len);
        buffer[max_len - 1] = '\0'; // Ensure null-termination
        return 1;
    }
    return 0;
}

void UART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    USART1->DR = c;                        // Send the character
}

void UART_SendString(const char *str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}

void UART_SendUInt(uint32_t num) {
    char buffer[10];  // enough for 32-bit unsigned int
    int i = 0;

    if (num == 0) {
        UART_SendChar('0');
        return;
    }

    while (num > 0 && i < sizeof(buffer)) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Reverse and send
    while (i--) {
        UART_SendChar(buffer[i]);
    }
}

void UART_SendInt(int32_t num) {
    if (num < 0) {
        UART_SendChar('-');
        num = -num;
    }
    UART_SendUInt((uint32_t)num);
}

void IntToStr(int32_t value, char *str) {
    char temp[12];  // Enough for -2,147,483,648 and null terminator
    int i = 0, j = 0;
    uint8_t is_negative = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    // Convert digits to temp buffer in reverse
    while (value != 0 && i < sizeof(temp) - 1) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (is_negative) {
        temp[i++] = '-';
    }

    // Reverse into output string
    while (i > 0) {
        str[j++] = temp[--i];
    }

    str[j] = '\0';
}

void FloatToStr(float value, char *str, uint8_t precision) {
    if (value < 0) {
        *str++ = '-';
        value = -value;
    }

    // Extract integer part
    uint32_t int_part = (uint32_t)value;

    // Convert integer part to string
    char int_str[12];
    IntToStr(int_part, int_str);

    // Copy integer part to final string
    char *p = int_str;
    while (*p) {
        *str++ = *p++;
    }

    *str++ = '.';  // Decimal point

    // Extract and convert fractional part
    float frac = value - (float)int_part;

    for (uint8_t i = 0; i < precision; i++) {
        frac *= 10.0f;
        uint8_t digit = (uint8_t)frac;
        *str++ = '0' + digit;
        frac -= digit;
    }

    *str = '\0';  // Null-terminate
}

