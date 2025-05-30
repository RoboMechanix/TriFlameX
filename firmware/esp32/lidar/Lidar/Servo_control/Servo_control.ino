#include "BLSER_interface.h"

void setup() {
  Serial.begin(115200);    
  pinMode(2, OUTPUT);
  BLSER_init(12,19,5,18);
  delay(5000);

}

void loop() {
  // BLSER_moveTo(180);
  //   Serial.println("180");
  // delay(1000);
  // BLSER_moveTo(0);
  //   Serial.println("0");
  // delay(1000);
  // BLSER_moveTo(90);
  // delay(1000);
  //   Serial.println("90");
  // BLSER_moveTo(0);
  //   Serial.println("0");
  // delay(1000);
  for (int i = 0; i < 180; i += 1){
    BLSER_moveTo(i);
    delay(20);
    Serial.println(i);
  }
  for (int i = 180; i > 0; i -= 1){
    BLSER_moveTo(i);
    delay(20);
    Serial.println(i);
  }
}
