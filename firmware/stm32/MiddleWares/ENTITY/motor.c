#include "motor.h"

struct motor {

	uint8_t id;
	DIR dir;
	float speed; // PWM .... percentage .... duty cycle
	uint8_t Ch;
	GPIO_TypeDef *EN;
	uint8_t ENNum;
	GPIO_TypeDef *IN1;
	uint8_t IN1Num;
	GPIO_TypeDef *IN2;
	uint8_t IN2Num;
};


void initMotor(TIM_TypeDef TIMX, uint8_t Channel, float percentage, GPIO_TypeDef *EN , uint8_t ENNum,
																	GPIO_TypeDef *IN1 ,uint8_t IN1Num,
																	GPIO_TypeDef *IN2 ,uint8_t IN2Num){

	motor -> dir = FORWARD;
}



void setDir(DIR dir){
	motor-> dir = dir;

	if (dir == REVERSE){ // IN1 IN2  -> 01
		GPIO_digitalWrite(IN1,IN1Num,LOW);
		GPIO_digitalWrite(IN2,IN2Num,HIGH);
	}
	else if (dir == FORWARD){ // IN1 IN2  -> 10
		GPIO_digitalWrite(IN1,IN1Num,HIGH);
		GPIO_digitalWrite(IN2,IN2Num,LOW);
	}

}

DIR getDir(){
	return dir;
}

void setSpeed(float velocityPercentage){
	motor -> speed = velocityPercentage;

}

float getSpeed(){
	return speed;
}

void stop(){
	GPIO_digitalWrite(EN,ENNum,LOW);
	GPIO_digitalWrite(IN1,IN1Num,LOW);
	GPIO_digitalWrite(IN2,IN2Num,LOW);
}




