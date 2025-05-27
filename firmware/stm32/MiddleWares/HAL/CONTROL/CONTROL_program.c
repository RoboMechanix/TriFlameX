#include "CONTROL_interface.h"
float kp_global;
float kd_global;
float prev_error=0;
float prev_time=0;
float speed;
#define maxDistance 5 //5cm from target
void PD_init( float Kp, float Kd)
{
kp_global=Kp;
kd_global=Kd;

}
void PD_update_from_distance(float actualDistance, uint64_t time_ms)
{
float error = actualDistance-maxDistance;
float p = kp_global*error;
float d = (error-prev_error)/((time_ms-prev_time)/1000.0f);
prev_error=error;
prev_time=time_ms;
speed=p+d;
if (speed > 100.0f) {
    speed = 100.0f;
} else if (speed < -100.0f) {
    speed = -100.0f;
}
if(speed>0){
    CAR_forward(speed);
}
else if (speed<0)
{
    CAR_backwards(-speed);
}
else CAR_stop();

}