#include "motor.h"

struct motor {

	uint8_t id;
	DIR dir;
	float pwm;
	uint8_t Ch;
	GPIO_TypeDef *EN;
	uint8_t ENNum;
	GPIO_TypeDef *IN1;
	uint8_t IN1Num;
	GPIO_TypeDef *IN2;
	uint8_t IN2Num;
};


void initMotor(TIM_TypeDef TIMX, uint8_t Channel, float percentage, GPIO_TypeDef *ENPIN ,GPIO_TypeDef *IN1PIN , GPIO_TypeDef *IN2PIN);
void setDir(DIR dir);
void setSpeed(float velocityPercentage);

void stop(){
	GPIO_digitalWrite(EN,ENNum,LOW);
	GPIO_digitalWrite(IN1,IN1Num,LOW);
	GPIO_digitalWrite(IN2,IN2Num,LOW);
}




