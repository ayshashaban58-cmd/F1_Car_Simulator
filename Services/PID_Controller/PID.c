/*
 * PID.c - PID Controller Implementation
 * Controls servo angle to maintain straight line
 */

#include "PID.h"
#include "../../HAL/MPU6050/MPU6050.h"
#include "../Odometry/Odometry.h"

#define DT 0.01f  // 100Hz = 10ms
#define OUTPUT_LIMIT 45.0f  // Max servo angle ±45°

static PID_Controller_t pid_steering = {
    .kp = 2.0f,
    .ki = 0.1f,
    .kd = 0.5f,
    .setpoint = 0.0f
};

void PID_Init(void) {
    PID_Reset();
}

void PID_Update(void) {
    // Get current orientation error
    Odometry_Data_t* odo = Odometry_GetData();
    
    // Calculate error (difference from setpoint)
    pid_steering.error = pid_steering.setpoint - odo->theta_deg;
    
    // Normalize error to -180 to +180
    while(pid_steering.error > 180.0f) pid_steering.error -= 360.0f;
    while(pid_steering.error < -180.0f) pid_steering.error += 360.0f;
    
    // Calculate integral with anti-windup
    pid_steering.integral += pid_steering.error * DT;
    if(pid_steering.integral > 100.0f) pid_steering.integral = 100.0f;
    if(pid_steering.integral < -100.0f) pid_steering.integral = -100.0f;
    
    // Calculate derivative
    pid_steering.derivative = (pid_steering.error - pid_steering.last_error) / DT;
    
    // Calculate PID output
    pid_steering.output = (pid_steering.kp * pid_steering.error) +
                          (pid_steering.ki * pid_steering.integral) +
                          (pid_steering.kd * pid_steering.derivative);
    
    // Limit output to servo range
    if(pid_steering.output > OUTPUT_LIMIT) pid_steering.output = OUTPUT_LIMIT;
    if(pid_steering.output < -OUTPUT_LIMIT) pid_steering.output = -OUTPUT_LIMIT;
    
    // Save last error
    pid_steering.last_error = pid_steering.error;
}

void PID_Reset(void) {
    pid_steering.error = 0.0f;
    pid_steering.last_error = 0.0f;
    pid_steering.integral = 0.0f;
    pid_steering.derivative = 0.0f;
    pid_steering.output = 0.0f;
}

void PID_SetGains(float kp, float ki, float kd) {
    pid_steering.kp = kp;
    pid_steering.ki = ki;
    pid_steering.kd = kd;
}

void PID_SetSetpoint(float setpoint) {
    pid_steering.setpoint = setpoint;
}

float PID_GetOutput(void) {
    return pid_steering.output;
}
