#include "CAR_interface.h"
#include "../../MCAL/TIMR/TIM_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

// Global variables for motor control
TIM_TypeDef *TimxLeft_global;
TIM_TypeDef *TimxRight_global;
uint8_t ChannelLeft_global;
uint8_t ChannelRight_global;

GPIO_TypeDef *DirLeft1_global;
GPIO_TypeDef *DirLeft2_global;
GPIO_TypeDef *DirRight1_global;
GPIO_TypeDef *DirRight2_global;

uint8_t DirLeft1Pin_global;
uint8_t DirLeft2Pin_global;
uint8_t DirRight1Pin_global;
uint8_t DirRight2Pin_global;

void CAR_init(TIM_TypeDef *TimxLeft ,uint8_t ChannelLeft, float FrequencyLeft,
              GPIO_TypeDef *DirLeft1, GPIO_TypeDef *DirLeft2, uint8_t DirLeft1Pin, uint8_t DirLeft2Pin,
              TIM_TypeDef *TimxRight ,uint8_t ChannelRight, float FrequencyRight,
              GPIO_TypeDef *DirRight1, GPIO_TypeDef *DirRight2, uint8_t DirRight1Pin, uint8_t DirRight2Pin) {

    // Store GPIO pointers and pin numbers
    DirLeft1_global = DirLeft1;
    DirLeft2_global = DirLeft2;
    DirRight1_global = DirRight1;
    DirRight2_global = DirRight2;

    DirLeft1Pin_global = DirLeft1Pin;
    DirLeft2Pin_global = DirLeft2Pin;
    DirRight1Pin_global = DirRight1Pin;
    DirRight2Pin_global = DirRight2Pin;

    // Configure all direction pins as outputs
    GPIO_pinMode(DirLeft1, DirLeft1Pin, OUTPUT);
    GPIO_pinMode(DirLeft2, DirLeft2Pin, OUTPUT);
    GPIO_pinMode(DirRight1, DirRight1Pin, OUTPUT);
    GPIO_pinMode(DirRight2, DirRight2Pin, OUTPUT);

    // Store timer and channel configuration
    TimxLeft_global = TimxLeft;
    TimxRight_global = TimxRight;
    ChannelLeft_global = ChannelLeft;
    ChannelRight_global = ChannelRight;

    // Initialize PWM channels
    TIM_initPWM(TimxLeft, ChannelLeft, FrequencyLeft);
    TIM_initPWM(TimxRight, ChannelRight, FrequencyRight);
}

void CAR_forward(float rightSpeed ,float leftSpeed) {
    // Left motor forward
	GPIO_digitalWrite(GPIOB, 9, HIGH); // yellow high
	GPIO_digitalWrite(GPIOB, 8, LOW); // green low


    GPIO_digitalWrite(DirLeft1_global, DirLeft1Pin_global, HIGH);
    GPIO_digitalWrite(DirLeft2_global, DirLeft2Pin_global, LOW);
    // Right motor forward
    GPIO_digitalWrite(DirRight1_global, DirRight1Pin_global, HIGH);
    GPIO_digitalWrite(DirRight2_global, DirRight2Pin_global, LOW);

    TIM_writePWM(TimxLeft_global, ChannelLeft_global, leftSpeed);
    TIM_writePWM(TimxRight_global, ChannelRight_global, rightSpeed);
}

void CAR_backwards(float rightSpeed , float leftSpeed) {
    // Left motor backward
	GPIO_digitalWrite(GPIOB, 9, HIGH); // yellow high
	GPIO_digitalWrite(GPIOB, 8, LOW); // green low


    GPIO_digitalWrite(DirLeft1_global, DirLeft1Pin_global, LOW);
    GPIO_digitalWrite(DirLeft2_global, DirLeft2Pin_global, HIGH);
    // Right motor backward
    GPIO_digitalWrite(DirRight1_global, DirRight1Pin_global, LOW);
    GPIO_digitalWrite(DirRight2_global, DirRight2Pin_global, HIGH);

    TIM_writePWM(TimxLeft_global, ChannelLeft_global, leftSpeed);
    TIM_writePWM(TimxRight_global, ChannelRight_global, rightSpeed);
}

void CAR_right(float leftSpeed, float rightSpeed) {
    // Left motor forward
	GPIO_digitalWrite(GPIOB, 9, HIGH); // yellow high
	GPIO_digitalWrite(GPIOB, 8, LOW); // green low


    GPIO_digitalWrite(DirLeft1_global, DirLeft1Pin_global, HIGH);
    GPIO_digitalWrite(DirLeft2_global, DirLeft2Pin_global, LOW);
    // Right motor backward
    GPIO_digitalWrite(DirRight1_global, DirRight1Pin_global, LOW);
    GPIO_digitalWrite(DirRight2_global, DirRight2Pin_global, HIGH);

    TIM_writePWM(TimxLeft_global, ChannelLeft_global, leftSpeed);
    TIM_writePWM(TimxRight_global, ChannelRight_global, rightSpeed);
}

void CAR_left(float rightSpeed, float leftSpeed) {
    // Left motor backward
	GPIO_digitalWrite(GPIOB, 9, HIGH); // yellow high
	GPIO_digitalWrite(GPIOB, 8, LOW); // green low


    GPIO_digitalWrite(DirLeft1_global, DirLeft1Pin_global, LOW);
    GPIO_digitalWrite(DirLeft2_global, DirLeft2Pin_global, HIGH);
    // Right motor forward
    GPIO_digitalWrite(DirRight1_global, DirRight1Pin_global, HIGH);
    GPIO_digitalWrite(DirRight2_global, DirRight2Pin_global, LOW);

    TIM_writePWM(TimxLeft_global, ChannelLeft_global, leftSpeed);
    TIM_writePWM(TimxRight_global, ChannelRight_global, rightSpeed);
}

void CAR_stop() {
	GPIO_digitalWrite(GPIOB, 9, LOW); // yellow high

	GPIO_digitalWrite(GPIOB, 8, HIGH); // green low

    // Brake both motors
    GPIO_digitalWrite(DirLeft1_global, DirLeft1Pin_global, LOW);
    GPIO_digitalWrite(DirLeft2_global, DirLeft2Pin_global, LOW);
    GPIO_digitalWrite(DirRight1_global, DirRight1Pin_global, LOW);
    GPIO_digitalWrite(DirRight2_global, DirRight2Pin_global, LOW);

    TIM_writePWM(TimxLeft_global, ChannelLeft_global, 0);
    TIM_writePWM(TimxRight_global, ChannelRight_global, 0);
}
