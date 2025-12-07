/*
 * Servo.h - Servo Motor Driver for Steering
 * Single servo for front wheel steering
 * PWM: OC1B (PD4)
 * Angle: -45° (left) to +45° (right), 0° = center
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

// Servo angle range
#define SERVO_ANGLE_MIN -45
#define SERVO_ANGLE_MAX 45
#define SERVO_ANGLE_CENTER 0

// Function prototypes
void Servo_Init(void);
void Servo_SetAngle(int8_t angle);
void Servo_Center(void);

#endif /* SERVO_H_ */
