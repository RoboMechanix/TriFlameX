#include "BLSER_interface.h"

volatile int counter = 0;
volatile bool is_cw = false;
int reff_count = 0;
float prev_err = 0.0;
float speed = 0.0;
float error = 0.0;
uint8_t encoderA, encoderB, pwm_pin, direction_pin;


void IRAM_ATTR handleInterrupt() {
  bool a = digitalRead(encoderA), b = digitalRead(encoderB); 
  if ((a && b)|| (!a && !b)){
    is_cw = true;
    counter++;
  }
  if ((a && !b) || (!a && b)){
    is_cw = false;
    counter--;
  }
}

void BLSER_init(uint8_t pwm_p, uint8_t dir_p, uint8_t encA, uint8_t encB){
  encoderA = encA;
  encoderB = encB;
  pwm_pin = pwm_p;
  direction_pin = dir_p;
  pinMode(pwm_pin, OUTPUT);
  pinMode(dir_p, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), handleInterrupt, CHANGE); //A
  // attachInterrupt(digitalPinToInterrupt(encB), handleInterrupt, CHANGE); //B
  analogWrite(pwm_pin, 255);

}

void BLSER_moveTo(float angle){
  reff_count = (angle/angle_per_step);
  error = (reff_count - counter);
  // analogWrite(pwm_pin, 255); // stop the motor
  while(fabs(error) > tolerance){
    if(print_counter)
      Serial.println(counter);
    error = (reff_count - counter);
    if(error > 0) // error positive then move clockwise 
        digitalWrite(direction_pin, HIGH);
    else // error negative then move anti-clockwise
        digitalWrite(direction_pin, LOW);
    error = fabs(error);
    speed = error*kp + (error - prev_err)*kd;
    prev_err = error;
    analogWrite(pwm_pin, map(speed, 0, 255, 255, 0));
  }
  analogWrite(pwm_pin, 255); // stop the motor
}
