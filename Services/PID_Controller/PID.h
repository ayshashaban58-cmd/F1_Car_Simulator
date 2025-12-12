// src/Services/PID_Controller/PID.h

#ifndef PID_H
#define PID_H

void PID_Init(void);
void PID_Update(void);
void PID_Reset(void);

extern float pid_speed_output;
extern float pid_steering_output;

#endif
