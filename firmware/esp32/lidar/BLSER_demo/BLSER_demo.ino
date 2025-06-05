#include "BLSER_interface.h"

void setup() {
  Serial.begin(115200);    
  pinMode(2, OUTPUT);
  BLSER_init(12, 19, 5, 18, 17);
}

void loop() {
  // for (int i = 0; i < 180; i += 2){
  //   BLSER_moveTo(i);
  //   delay(1);
  //   Serial.println(i);
  // }
  // analogWrite(12, 255); // stop the motor
  // analogWrite(12, 255); // stop the motor
  // for (int i = 180; i > 0; i -= 2){
  //   BLSER_moveTo(i);
  //   delay(1);
  //   Serial.println(i);
  // } 
  BLSER_moveTo(360);

  BLSER_moveTo(0);
}
