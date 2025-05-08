#include "motor.h"

struct motor {

	uint8_t id;
	DIR dir;
	float pwm;
	uint8_t Ch;
	GPIO_TypeDef *ENPIN;
	GPIO_TypeDef *IN1PIN;
	GPIO_TypeDef *IN2PIN;
};


void initMotor(TIM_TypeDef TIMX, uint8_t Channel, float percentage, GPIO_TypeDef *ENPIN ,GPIO_TypeDef *IN1PIN , GPIO_TypeDef *IN2PIN);
void setDir(DIR dir);
void setSpeed(float velocityPercentage);
void stop();


