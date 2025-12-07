/*
 * Motor.h - DC Motor Driver using L298N
 * Single motor for rear wheels
 * IN1: PB0, IN2: PB1, EN: PWM_MOTOR (OC1A/PD5)
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

// Motor direction
#define MOTOR_FORWARD  1
#define MOTOR_BACKWARD 2
#define MOTOR_STOP     0

// Speed range: 0-100%
#define MOTOR_SPEED_MIN 0
#define MOTOR_SPEED_MAX 100

// Function prototypes
void Motor_Init(void);
void Motor_SetSpeed(uint8_t speed);
void Motor_SetDirection(uint8_t direction);
void Motor_Stop(void);
void Motor_Drive(uint8_t direction, uint8_t speed);

#endif /* MOTOR_H_ */
