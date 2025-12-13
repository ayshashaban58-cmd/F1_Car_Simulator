#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "../MCAL/Dio/Dio.h"
#include "../MCAL/Timer/Timer.h"

// Servo pin: PWM=PD4 (OC1B)
#define SERVO_PWM_PORT DIO_PORTD
#define SERVO_PWM_PIN DIO_PIN4

// Servo angles (0-100 mapped to pulse width)
#define SERVO_CENTER 50
#define SERVO_LEFT 0
#define SERVO_RIGHT 100

// Function Prototypes
void Servo_Init(void);
void Servo_SetAngle(uint8_t angle);
void Servo_Center(void);
void Servo_TurnLeft(uint8_t amount);
void Servo_TurnRight(uint8_t amount);

#endif /* SERVO_H_ */
