#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>
#include "../MCAL/Dio/Dio.h"
#include "../MCAL/Timer/Timer.h"

// Motor pins: IN1=PB0, IN2=PB1, PWM=PD5 (OC1A)
#define MOTOR_IN1_PORT DIO_PORTB
#define MOTOR_IN1_PIN DIO_PIN0
#define MOTOR_IN2_PORT DIO_PORTB
#define MOTOR_IN2_PIN DIO_PIN1
#define MOTOR_PWM_PORT DIO_PORTD
#define MOTOR_PWM_PIN DIO_PIN5

typedef enum {
    MOTOR_FORWARD = 0,
    MOTOR_BACKWARD,
    MOTOR_STOP
} Motor_DirectionType;

// Function Prototypes
void Motor_Init(void);
void Motor_SetSpeed(uint8_t speed);
void Motor_SetDirection(Motor_DirectionType dir);
void Motor_Stop(void);
void Motor_Drive(Motor_DirectionType dir, uint8_t speed);

#endif /* MOTOR_H_ */
