#ifndef LIDAR_H
#define LIDAR_H
// ==== Lidar and Stepper Task Declarations ====
#include "TOF_Sense.h"
#define dir_pin 23
#define step_pin 22
#define en_pin 18
#define calibration_pin 19
#define steps (200*2)
#define resolution (1.8/2.0) // degree per step
#define shifting_angle_factor 15
#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

extern TOF_Parameter TOF_0;
extern volatile int Sensordistance;
extern volatile int Sensorangle;

void stepper_task(void *parameter);
void tof_task(void *parameter);
void stepperInit();
void tofInit();

#endif // LIDAR_H