#include "TOF_Sense.h"
#define dir_pin 14
#define step_pin 12
#define en_pin 18
#define calibration_pin 5
#define steps (200*2)
#define resolution (1.8/2.0) // degree per step
extern TOF_Parameter TOF_0;
volatile float current_angle;

void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  Serial.begin(460800);
  TOF_UART.begin(1500000, SERIAL_8N1, TOF_RX_PIN, TOF_TX_PIN);
  pinMode(calibration_pin, INPUT_PULLUP);
  pinMode(en_pin, OUTPUT);
  digitalWrite(en_pin, LOW); // activate the stepper
  delay(2000); // Give time for Serial to connect

  // Run both tasks on Core 1
  xTaskCreatePinnedToCore(
        tof_task,         // Function name
        "tof",            // Task name
        2048,             // Stack size
        NULL,             // Parameter
        1,                // Priority
        NULL,             // Task handle
        1                 // Core 1
  );

  xTaskCreatePinnedToCore(
        stepper_task,     // Function name
        "stepper",        // Task name
        4096,             // Stack size
        NULL,             // Parameter
        2,                // Priority
        NULL,             // Task handle
        1                 // Core 1
  );
}


void tof_task(void *parameter){
  while(1){
    TOF_Active_Decoding(); // Query and decode TOF data
  }
}

void stepper_task(void *parameter){
  float span = 90.0;
  float min_angle_steps = 0, max_angle_steps = 0;
  bool mask = false, mask2 = false;
  int counter = 0;
  float min_angle = 0.0 + ((180.0-span)/2.0);
  float max_angle = 180.0 - ((180.0-span)/2.0);
  float angle1 = 0.0, angle2 = 0.0, dist1 = 0.0, dist2 = 0.0;
  while(1){
    ////////////////////////////////////// Calibration //////////////////////////////////////
    if (!digitalRead(calibration_pin) && !mask){
      counter ++;
      mask = true;
    }else if(digitalRead(calibration_pin) && mask){
      mask = false;
    }
    if (counter % 2 == 0 && !mask2){
      digitalWrite(en_pin, HIGH); // deactivate the stepper
      Serial.println("stepper off");
      min_angle_steps = 0;
      max_angle_steps = 0;
      mask2 = true;
    }else if(counter % 2 != 0 && mask2){
      digitalWrite(en_pin, LOW); // reactivate the stepper
      Serial.println("stepper on");
      // transforming angle to steps
      min_angle_steps = min_angle/resolution;
      max_angle_steps = max_angle/resolution;
      digitalWrite(dir_pin, HIGH); // AntiClockwise
      vTaskDelay(50 / portTICK_PERIOD_MS);  // for stability
      for (int i = 0; i < min_angle_steps; i++){ // to go to the min angle
        digitalWrite(step_pin, HIGH);
        vTaskDelay(2 / portTICK_PERIOD_MS);  
        digitalWrite(step_pin, LOW);
        vTaskDelay(2 / portTICK_PERIOD_MS); 
      }
      mask2 = false;
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    float angle_at_min_dist = 181;
    uint32_t min_dist = 9999;  // set high starting value
    digitalWrite(dir_pin, HIGH); // AntiClockwise
    vTaskDelay(50 / portTICK_PERIOD_MS);  // for stability
    for (int i = min_angle_steps; i <= max_angle_steps; i ++){
      digitalWrite(step_pin, HIGH);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      digitalWrite(step_pin, LOW);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      current_angle = i*resolution;
      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot
      if (current_dist < min_dist) {
        min_dist = current_dist;
        angle_at_min_dist = current_angle;
      }
    }
    // Serial.print("(");
    // Serial.print(angle_at_min_dist);
    // Serial.print(",");
    // Serial.print(min_dist);
    // Serial.println(")");
    angle1 = angle_at_min_dist - 3;
    dist1 = min_dist;

    angle_at_min_dist = 181;
    min_dist = 9999;  // set high starting value
    digitalWrite(dir_pin, LOW); // clockwise
    vTaskDelay(50 / portTICK_PERIOD_MS);  // for stability 
    for (int i = max_angle_steps; i >= min_angle_steps; i --){
      digitalWrite(step_pin, HIGH);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      digitalWrite(step_pin, LOW);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      current_angle = i*resolution;
      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot
      if (current_dist < min_dist) {
        min_dist = current_dist;
        angle_at_min_dist = current_angle;
      }
    }
    // Serial.print("(");
    // Serial.print(angle_at_min_dist);
    // Serial.print(",");
    // Serial.print(min_dist);
    // Serial.println(")");
    angle2 = angle_at_min_dist + 3;
    dist2 = min_dist;

    Serial.print("(");
    Serial.print((angle1 + angle2)/2.0);
    Serial.print(",");
    Serial.print((dist1 + dist2)/2.0);
    Serial.println(")");

  }
}

void loop() {
}
