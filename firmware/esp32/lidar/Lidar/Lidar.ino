#include "TOF_Sense.h"
#include <ESP32Servo.h>
extern TOF_Parameter TOF_0;
Servo servo;
volatile float current_angle;
float span = 90.0, step_size = 0.25;
float min_angle = 0, max_angle = 0;
void setup() {
  Serial.begin(460800);//Initialize the USB serial port baud rate to 115200 初始化USB串口波特率到115200
  TOF_UART.begin(1500000, SERIAL_8N1, TOF_RX_PIN, TOF_TX_PIN);//Initialize the TOF serial port baud rate to 1500000 and specify the pin 初始化TOF串口波特率到921600,并指定引脚
  servo.setPeriodHertz(50);
  servo.attach(12);
  min_angle = 0.0 + ((180.0-span)/2.0);
  max_angle = 180.0 - ((180.0-span)/2.0);
  delay(10); // Give time for Serial to connect

  xTaskCreate(
        tof_task,      // Function name of the task
        "tof",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        NULL         // Task handle
  );
  xTaskCreate(
        servo_task,     // Function name of the task
        "servo",  // Name of the task (e.g. for debugging)
        4096,       // Stack size (bytes)
        NULL,       // Parameter to pass
        2,          // Task priority
        NULL        // Task handle
  );
}

void tof_task(void *parameter){
  while(1){
    TOF_Active_Decoding();//Query and decode TOF data 查询获取TOF数据，并进行解码
    // Serial.print(current_angle);
    // Serial.print(",");
    // Serial.println(TOF_0.dis);
  }
}

void servo_task(void *parameter){
  while(1){
    float min_dist_at_angle = 181;
    uint32_t min_dist = 9999;  // set high starting value

    for (float i = min_angle; i <= max_angle; i += step_size) {
      servo.write(i);
      vTaskDelay(2 / portTICK_PERIOD_MS);  // Allow servo to reach position

      current_angle = i;
      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot

      if (current_dist < min_dist) {
        min_dist = current_dist;
        min_dist_at_angle = current_angle;
      }
    }
    Serial.print("(");
    Serial.print(min_dist_at_angle-6);
    Serial.print(",");
    Serial.print(min_dist);
    Serial.println(")");
    min_dist_at_angle = 181;
    min_dist = 9999;  // set high starting value
    for(float i = max_angle; i >= min_angle; i-=step_size){
      servo.write(i);
      vTaskDelay(2 / portTICK_PERIOD_MS);  // Allow servo to reach position

      current_angle = i;
      uint32_t current_dist = TOF_0.dis;  // Get stable snapshot

      if (current_dist < min_dist) {
        min_dist = current_dist;
        min_dist_at_angle = current_angle;
      }
    }
    Serial.print("(");
    Serial.print(min_dist_at_angle+6);
    Serial.print(",");
    Serial.print(min_dist);
    Serial.println(")");
       
  }
}

void loop() {
}
