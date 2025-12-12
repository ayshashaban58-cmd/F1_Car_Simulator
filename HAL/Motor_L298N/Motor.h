// src/HAL/Motor_L298N/Motor.h

#ifndef MOTOR_H
#define MOTOR_H

void Motor_Init(void);
void Motor_SetSpeed(int16_t speed); // -255 to 255
void Motor_SetDirection(uint8_t dir); // 0 forward, 1 backward
void Motor_Stop(void);

#endif
