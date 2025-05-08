#include "stm32f1xx.h"
#include "MCAL/GPIO/GPIO_interface.h"


typedef enum {
	REVERSE = 0,
	FORWARD = 1
} DIR;




void initMotor(TIM_TypeDef TIMX, uint8_t Channel, float percentage, GPIO_TypeDef *EN , uint8_t ENNum,
																	GPIO_TypeDef *IN1 ,uint8_t IN1Num,
																	GPIO_TypeDef *IN2 ,uint8_t IN2Num);
void setDir(DIR dir);
DIR getDir();
void setSpeed(float velocityPercentage);
float getSpeed();
void stop();
