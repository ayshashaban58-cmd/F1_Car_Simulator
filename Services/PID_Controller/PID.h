#ifndef PID_H_
#define PID_H_

#include <stdint.h>

typedef struct {
    float kp;
    float ki;
    float kd;
    float integral;
    float prevError;
    float output;
    float minOutput;
    float maxOutput;
} PID_ControllerType;

// Function Prototypes
void PID_Init(PID_ControllerType* pid, float kp, float ki, float kd, float minOut, float maxOut);
float PID_Update(PID_ControllerType* pid, float error, float dt);
void PID_Reset(PID_ControllerType* pid);

#endif /* PID_H_ */
