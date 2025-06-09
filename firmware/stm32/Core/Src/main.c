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
	PD_init(0.4f, 2.0f);        // Distance PD
	PD_init_angle(2.0f, 1.0f);  // Angle control gains
	UART_init(1, BAUDRATE);

	while (1) {
		UARTMessage msg;
		do {
			msg = UART_receive_message(1);
		}while (msg.type == MSG_NONE);

		distance = msg.distance;
		angle = msg.angle;

		current_time_ms = TIM_Millis();

		if (msg.command ==0){
			CAR_stop();
			continue;
		}

		PD_update_angle_ret(angle);
		if(distance!=0){
			PD_update_from_distance(distance, current_time_ms);
		}

	}

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
