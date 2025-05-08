#include "motor.h"

void initMotor(Motor *motor, float velocityPercentage,
               GPIO_TypeDef *EN, uint8_t ENNum,
               GPIO_TypeDef *IN1, uint8_t IN1Num,
               GPIO_TypeDef *IN2, uint8_t IN2Num) {
    motor->dir = FORWARD;
    motor->speed = velocityPercentage;
    motor->EN = EN;
    motor->IN1 = IN1;
    motor->IN2 = IN2;
    motor->ENNum = ENNum;
    motor->IN1Num = IN1Num;
    motor->IN2Num = IN2Num;

    setDir(motor, FORWARD); // default direction
}

void setDir(Motor *motor, DIR dir) {
    motor->dir = dir;
    if (dir == REVERSE) {  // IN1 IN2  -> 01
        GPIO_digitalWrite(motor->IN1, motor->IN1Num, LOW);
        GPIO_digitalWrite(motor->IN2, motor->IN2Num, HIGH);
    } else { // IN1 IN2  -> 10
        GPIO_digitalWrite(motor->IN1, motor->IN1Num, HIGH);
        GPIO_digitalWrite(motor->IN2, motor->IN2Num, LOW);
    }
}

DIR getDir(Motor *motor) {
    return motor->dir;
}

void setSpeed(Motor *motor, float velocityPercentage) {
    motor->speed = velocityPercentage;

}

float getSpeed(Motor *motor) {
    return motor->speed;
}

void stop(Motor *motor) {
    GPIO_digitalWrite(motor->EN, motor->ENNum, LOW);
    GPIO_digitalWrite(motor->IN1, motor->IN1Num, LOW);
    GPIO_digitalWrite(motor->IN2, motor->IN2Num, LOW);
}
