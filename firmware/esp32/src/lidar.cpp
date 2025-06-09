#include "lidar.h"
#include <main.h>

void tof_task(void *parameter){
  while(1){
    TOF_Active_Decoding(); // Query and decode TOF data
  }
}

void stepper_task(void *parameter){
  float span = 126.0;
  float min_angle_steps = 0, max_angle_steps = 0;
  bool mask = false, mask2 = false;
  int counter = 0;
  float min_angle = 0.0 + ((180.0-span)/2.0);
  float max_angle = 180.0 - ((180.0-span)/2.0);
  float angle1 = 0.0, angle2 = 0.0, dist1 = 0.0, dist2 = 0.0, prev_distance = 0.0, prev_angle = 0.0;
  uint8_t distance_tolerance = 10, angle_tolerance = 3;
  float avg_dist = 0.0, avg_angle = 0.0;
  float current_angle;

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
    vTaskDelay(5 / portTICK_PERIOD_MS);  // for stability
    for (int i = min_angle_steps; i <= max_angle_steps; i ++){
      digitalWrite(step_pin, HIGH);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      digitalWrite(step_pin, LOW);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      current_angle = i*resolution;
      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot
      // Serial.print(current_angle-10);
      // Serial.print(",");
      // Serial.println(current_dist);
      if (current_dist < min_dist) {
        min_dist = current_dist;
        angle_at_min_dist = current_angle;
      }
    }

    angle1 = angle_at_min_dist;
    dist1 = min_dist;
    angle1 = CLAMP(angle1, 0, (max_angle - shifting_angle_factor));

    xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
    Sensordistance = dist1;
    Sensorangle = angle1;
    xSemaphoreGive(xSharedDataMutex);

    Serial.print("(");
    Serial.print(angle1);
    Serial.print(",");
    Serial.print(dist1);
    Serial.println(")");

    angle_at_min_dist = 181;
    min_dist = 9999;  // set high starting value
    digitalWrite(dir_pin, LOW); // clockwise
    vTaskDelay(5 / portTICK_PERIOD_MS);  // for stability 
    for (int i = max_angle_steps; i >= min_angle_steps; i --){
      digitalWrite(step_pin, HIGH);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      digitalWrite(step_pin, LOW);
      vTaskDelay(1 / portTICK_PERIOD_MS);  
      current_angle = i*resolution + shifting_angle_factor;

      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot
      // Serial.print(current_angle);
      // Serial.print(",");
      // Serial.println(current_dist);
      if (current_dist <= min_dist) {
        min_dist = current_dist;
        angle_at_min_dist = current_angle;
      }
    }
    angle2 = angle_at_min_dist;
    dist2 = min_dist;
    angle2 = CLAMP(angle_at_min_dist, 0, (max_angle - shifting_angle_factor));

    xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
    Sensordistance = dist2;
    Sensorangle = angle2;
    xSemaphoreGive(xSharedDataMutex);

    Serial.print("(");
    Serial.print(angle2);
    Serial.print(",");
    Serial.print(dist2);
    Serial.println(")");

  }
}
