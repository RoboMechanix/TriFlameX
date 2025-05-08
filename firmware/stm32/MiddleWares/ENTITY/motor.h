#include "stm32f1xx.h"



typedef enum {
	reverse = 0,
	forward = 1
} DIR;




void initMotor(TIM_TypeDef TIMX, uint8_t Channel, float percentage, GPIO_TypeDef *ENPIN ,GPIO_TypeDef *IN1PIN , GPIO_TypeDef *IN2PIN);
void setDir(DIR dir);
void setSpeed(float velocityPercentage);
void stop();
