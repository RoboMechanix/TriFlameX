#include "CONTROL_interface.h"
float kp_global;
float kd_global;
float prev_error=0;
float prev_time=0;
float speed;
float kp_angle = 0;
float kd_angle = 0;
float prev_angle_error = 0;
float prev_angle_time = 0;
float servo_output = 0;

void PD_init_angle(float Kp, float Kd) {
    kp_angle = Kp;
    kd_angle = Kd;
}

// Update angle control, currentAngle and targetAngle in degrees
void PD_update_angle(float currentAngle, uint64_t time_ms) {
    float error = mainAngle - currentAngle;  // desired - current
    float dt = (time_ms - prev_angle_time) / 1000.0f;
    if (dt <= 0) dt = 0.001f;

    float derivative = (error - prev_angle_error) ;

    prev_angle_error = error;
    prev_angle_time = time_ms;

    float steering_correction = kp_angle * error + kd_angle * derivative;

    // Clamp correction
    if (steering_correction > 100) steering_correction = 100;
    else if (steering_correction < -100) steering_correction = -100;

    // Use global forward speed (assumed non-negative)
    float base_speed = speed;
    float right_motor_speed;
	float left_motor_speed;
    if (error > 0) {
        // Turn left: right motor faster, left motor slower
        right_motor_speed = base_speed + steering_correction;
        left_motor_speed = base_speed - steering_correction;
    } else if (error < 0) {
        // Turn right: left motor faster, right motor slower
        right_motor_speed = base_speed - (-steering_correction);  // steering_correction negative here
        left_motor_speed = base_speed + (-steering_correction);
    }

    // Clamp motor speeds to [0, 100]
    if (left_motor_speed > 100) left_motor_speed = 100;
    if (left_motor_speed < -100) left_motor_speed = -100;
    if (right_motor_speed > 100) right_motor_speed = 100;
    if (right_motor_speed < -100) right_motor_speed = -100;
    if(fabs(error)<3){
    	right_motor_speed=0;
    	left_motor_speed=0;
    }


    // Drive motors forward with computed speeds
    if(right_motor_speed>0 && left_motor_speed>0){
    CAR_forward(right_motor_speed, left_motor_speed);
    }
    else if(right_motor_speed<0 && left_motor_speed<0){
    	CAR_backwards(-right_motor_speed, -left_motor_speed);
    }
    else if(right_motor_speed>0 && left_motor_speed<0){
        	CAR_left(right_motor_speed, -left_motor_speed);
        }
    else if(right_motor_speed<0 && left_motor_speed>0){
        	CAR_right(left_motor_speed, -right_motor_speed);
        }
}



void PD_init( float Kp, float Kd)
{
	kp_global = Kp;
	kd_global = Kd;
}

void PD_update_from_distance(float actualDistance, uint64_t time_ms)
{
    float error = actualDistance - maxDistance;

    // in the backward case
    if(error<0){
    	kp_global=5;
    	kd_global=5;
    }

    float p = kp_global * error;
    float d = kd_global*(error - prev_error) ;
    prev_error = error;
    prev_time = time_ms;

    speed = p + d;

    // Clamp speed to [-MAX_LINEAR_SPEED_CORRECTION, MAX_LINEAR_SPEED_CORRECTION]
    if (speed > MAX_LINEAR_SPEED_CORRECTION) {
        speed = MAX_LINEAR_SPEED_CORRECTION;
    } else if (speed < -MAX_LINEAR_SPEED_CORRECTION) {
        speed = -MAX_LINEAR_SPEED_CORRECTION;
    }

    // Apply deadband threshold
//    if (speed > 0.0f && speed < 30.0f) {
//        speed = 30.0f;  // Minimum forward speed
//    } else if (speed < 0.0f && speed > -30.0f) {
//        speed = -30.0f; // Minimum backward speed
//    }
	if(fabs(error) < DISTANCE_ERROR_THRESH){
		speed = 0;
	}
    // Movement logic
    if (speed > 0) {
        CAR_forward(speed,speed);
    } else if (speed < 0) {
        CAR_backwards(-speed,-speed);
    } else {
        CAR_stop();
    }
}


// Update angle control, currentAngle and targetAngle in degrees it returns 1 if the error is less than a certain threshold else 0
uint8_t PD_update_angle_ret(float currentAngle) {
    float error = mainAngle - currentAngle;  // desired - current
    float derivative = (error - prev_angle_error) ;

    prev_angle_error = error;

    float steering_correction = kp_angle * error + kd_angle * derivative;

    // Clamp correction
    if (steering_correction > MAX_STEERING_CORRECTION) steering_correction = MAX_STEERING_CORRECTION;
    else if (steering_correction < -MAX_STEERING_CORRECTION) steering_correction = -MAX_STEERING_CORRECTION;

    if (steering_correction > 0) {
    	CAR_right(steering_correction, steering_correction);

    } else if (steering_correction < 0) {
    	CAR_left(-1*steering_correction, -1*steering_correction);
    }

    return (fabs(error) < ANGLE_ERROR_THRESH) ? 1 : 0;
}

