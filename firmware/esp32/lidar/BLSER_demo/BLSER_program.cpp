#include "esp32-hal-gpio.h"
#include "BLSER_interface.h"

volatile int counter = 0;
volatile bool is_cw = false;
int reff_count = 0;
float prev_err = 0.0;
float speed = 0.0;
float error = 0.0;
uint8_t encoderA, encoderB, pwm_pin, direction_pin, brake_pin;


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

void BLSER_init(uint8_t pwm_p, uint8_t dir_p, uint8_t encB, uint8_t encA, uint8_t b_pin){
  encoderA = encA;
  encoderB = encB;
  pwm_pin = pwm_p;
  direction_pin = dir_p;
  brake_pin = b_pin;
  pinMode(pwm_pin, OUTPUT);
  pinMode(dir_p, OUTPUT);
  pinMode(brake_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encA), handleInterrupt, CHANGE); //A
  // attachInterrupt(digitalPinToInterrupt(encB), handleInterrupt, CHANGE); //B
  digitalWrite(brake_pin, LOW); // stop the motor
}

void BLSER_moveTo(float angle){
  reff_count = (angle/angle_per_step);
  error = (reff_count - counter);
  digitalWrite(brake_pin, HIGH); // start the motor
  while(fabs(error) >= tolerance){
    if(print_counter){
      Serial.print(counter);
      Serial.print(" ");
    }
    error = (reff_count - counter);
    if(error > 0) // error positive then move clockwise 
        digitalWrite(direction_pin, HIGH);
    else // error negative then move anti-clockwise
        digitalWrite(direction_pin, LOW);
    if (print_reff_counter){
      Serial.print(reff_count);
      Serial.print(" ");
    }
    if(print_error){
      Serial.print(error);
      Serial.print(" ");  
    }
    error = fabs(error);
    speed = error*kp + (error - prev_err)*kd;
    prev_err = error;
    if (print_speed){
      Serial.print(speed);
      Serial.print(" ");
    }if (print_speed || print_counter || print_reff_counter || print_error){
      Serial.println();
    }
    if (speed > 255)
      speed = 255;
    else if(speed < 0)
      speed = 0;
    analogWrite(pwm_pin, map(speed, 0, 255, 255, 0));
  }
  digitalWrite(brake_pin, LOW); // stop the motor
}
