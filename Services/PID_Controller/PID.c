/*============================================================================
 * PID Controller Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Standard PID formula with anti-windup
 *===========================================================================*/

#include "PID.h"

PID_Controller_t SpeedPID;
PID_Controller_t SteeringPID;

void PID_Init(PID_Controller_t* pid, float32_t kp, float32_t ki, float32_t kd, 
              float32_t min_out, float32_t max_out) {
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->OutputMin = min_out;
    pid->OutputMax = max_out;
    pid->Integral = 0.0f;
    pid->PrevError = 0.0f;
    pid->Dt = 0.01f;  // 100Hz
    pid->Enabled = TRUE;
}

float32_t PID_Update(PID_Controller_t* pid, float32_t measurement) {
    if(!pid->Enabled) return 0.0f;
    
    float32_t error = pid->Setpoint - measurement;
    pid->Integral += error * pid->Dt;
    
    // Anti-windup
    if(pid->Integral > pid->OutputMax) pid->Integral = pid->OutputMax;
    if(pid->Integral < pid->OutputMin) pid->Integral = pid->OutputMin;
    
    float32_t derivative = (error - pid->PrevError) / pid->Dt;
    float32_t output = pid->Kp * error + 
                      pid->Ki * pid->Integral + 
                      pid->Kd * derivative;
    
    // Clamp output
    if(output > pid->OutputMax) output = pid->OutputMax;
    if(output < pid->OutputMin) output = pid->OutputMin;
    
    pid->PrevError = error;
    return output;
}

void PID_Reset(PID_Controller_t* pid) {
    pid->Integral = 0.0f;
    pid->PrevError = 0.0f;
}
