// src/Services/PID_Controller/PID.c

#include "PID.h"
#include "../Odometry/Odometry.h"
#include "../Path_Planning/Path_Planning.h"

float kp_speed = 1.0, ki_speed = 0.1, kd_speed = 0.05;
float kp_steer = 2.0, ki_steer = 0.2, kd_steer = 0.1;
float integral_speed = 0, prev_err_speed = 0;
float integral_steer = 0, prev_err_steer = 0;
float pid_speed_output = 0, pid_steering_output = 0;

void PID_Init(void) {}

void PID_Update(void) {
    float target_x = Path_Planning_GetTargetX();
    float target_y = Path_Planning_GetTargetY();
    float curr_x = Odometry_GetX();
    float curr_y = Odometry_GetY();
    float curr_theta = Odometry_GetTheta();

    float err_dist = sqrt(pow(target_x - curr_x, 2) + pow(target_y - curr_y, 2));
    float err_angle = atan2(target_y - curr_y, target_x - curr_x) - curr_theta;

    // Speed PID
    float d_err_speed = err_dist - prev_err_speed;
    integral_speed += err_dist;
    pid_speed_output = kp_speed * err_dist + ki_speed * integral_speed + kd_speed * d_err_speed;
    prev_err_speed = err_dist;

    // Steering PID
    float d_err_steer = err_angle - prev_err_steer;
    integral_steer += err_angle;
    pid_steering_output = kp_steer * err_angle + ki_steer * integral_steer + kd_steer * d_err_steer;
    prev_err_steer = err_angle;
}

void PID_Reset(void) {
    integral_speed = 0;
    integral_steer = 0;
    prev_err_speed = 0;
    prev_err_steer = 0;
}
