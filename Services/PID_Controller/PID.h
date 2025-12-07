/*
 * PID.h - PID Controller for Steering
 * Maintains straight line using IMU gyro feedback
 */

#ifndef PID_H_
#define PID_H_

#include <stdint.h>

// PID parameters structure
typedef struct {
    float kp;
    float ki;
    float kd;
    float error;
    float last_error;
    float integral;
    float derivative;
    float output;
    float setpoint;
} PID_Controller_t;

// Function prototypes
void PID_Init(void);
void PID_Update(void);
void PID_Reset(void);
void PID_SetGains(float kp, float ki, float kd);
void PID_SetSetpoint(float setpoint);
float PID_GetOutput(void);

#endif /* PID_H_ */
