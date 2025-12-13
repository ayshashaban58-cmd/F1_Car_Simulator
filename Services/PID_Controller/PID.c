#include "PID.h"

void PID_Init(PID_ControllerType* pid, float kp, float ki, float kd, float minOut, float maxOut) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->integral = 0.0f;
    pid->prevError = 0.0f;
    pid->output = 0.0f;
    pid->minOutput = minOut;
    pid->maxOutput = maxOut;
}

float PID_Update(PID_ControllerType* pid, float error, float dt) {
    // Proportional term
    float p = pid->kp * error;
    
    // Integral term with anti-windup
    pid->integral += error * dt;
    float i = pid->ki * pid->integral;
    
    // Derivative term
    float d = 0.0f;
    if(dt > 0.0f) {
        d = pid->kd * (error - pid->prevError) / dt;
    }
    
    // Calculate output
    pid->output = p + i + d;
    
    // Clamp output
    if(pid->output > pid->maxOutput) {
        pid->output = pid->maxOutput;
        // Anti-windup: stop integral growth
        pid->integral -= error * dt;
    } else if(pid->output < pid->minOutput) {
        pid->output = pid->minOutput;
        pid->integral -= error * dt;
    }
    
    pid->prevError = error;
    return pid->output;
}

void PID_Reset(PID_ControllerType* pid) {
    pid->integral = 0.0f;
    pid->prevError = 0.0f;
    pid->output = 0.0f;
}
