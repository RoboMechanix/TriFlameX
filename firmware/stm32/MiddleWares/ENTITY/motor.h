#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f1xx.h"
#include "MCAL/GPIO/GPIO_interface.h"

typedef enum {
    REVERSE = 0,
    FORWARD = 1
} DIR;

typedef struct {
    DIR dir;
    float speed; // PWM .... percentage .... duty cycle
    uint8_t Ch;
    GPIO_TypeDef *EN;
    uint8_t ENNum;
    GPIO_TypeDef *IN1;
    uint8_t IN1Num;
    GPIO_TypeDef *IN2;
    uint8_t IN2Num;
    TIM_TypeDef *TIMX;
} Motor;

void initMotor(Motor *motor, float velocityPercentage,
			   TIM_TypeDef *TIMX,
               GPIO_TypeDef *EN, uint8_t ENNum,
               GPIO_TypeDef *IN1, uint8_t IN1Num,
               GPIO_TypeDef *IN2, uint8_t IN2Num);

void setDir(Motor *motor, DIR dir);
DIR getDir(Motor *motor);
void setSpeed(Motor *motor, float velocityPercentage);
float getSpeed(Motor *motor);
void stop(Motor *motor);

#endif
