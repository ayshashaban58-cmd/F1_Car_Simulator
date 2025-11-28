/*============================================================================
 * PID Controller Service
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Speed + Steering control at 100Hz
 *===========================================================================*/

#ifndef PID_H_
#define PID_H_

#include "../Config/Std_Types.h"

typedef struct {
    float32_t Kp, Ki, Kd;
    float32_t Setpoint;
    float32_t OutputMin, OutputMax;
    float32_t Integral;
    float32_t PrevError;
    float32_t Dt;
    boolean Enabled;
} PID_Controller_t;

extern PID_Controller_t SpeedPID;
extern PID_Controller_t SteeringPID;

void PID_Init(PID_Controller_t* pid, float32_t kp, float32_t ki, float32_t kd, 
              float32_t min_out, float32_t max_out);
float32_t PID_Update(PID_Controller_t* pid, float32_t measurement);
void PID_Reset(PID_Controller_t* pid);

#endif
