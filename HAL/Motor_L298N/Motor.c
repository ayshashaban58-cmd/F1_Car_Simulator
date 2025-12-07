/*
 * Motor.c - DC Motor Driver Implementation
 */

#include "Motor.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"

#define MOTOR_IN1_PORT PORTB_REG
#define MOTOR_IN1_PIN 0
#define MOTOR_IN2_PORT PORTB_REG
#define MOTOR_IN2_PIN 1

void Motor_Init(void) {
    // Set motor control pins as output
    Dio_SetPinDirection(MOTOR_IN1_PORT, MOTOR_IN1_PIN, DIO_OUTPUT);
    Dio_SetPinDirection(MOTOR_IN2_PORT, MOTOR_IN2_PIN, DIO_OUTPUT);
    
    // Stop motor initially
    Motor_Stop();
}

void Motor_SetSpeed(uint8_t speed) {
    // Limit speed to 0-100%
    if(speed > MOTOR_SPEED_MAX) speed = MOTOR_SPEED_MAX;
    
    // Convert 0-100% to 0-1023 (10-bit PWM)
    uint16_t pwm_value = (speed * 1023UL) / 100;
    
    Timer_SetPWM(PWM_MOTOR, pwm_value);
}

void Motor_SetDirection(uint8_t direction) {
    switch(direction) {
        case MOTOR_FORWARD:
            Dio_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, DIO_HIGH);
            Dio_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, DIO_LOW);
            break;
        case MOTOR_BACKWARD:
            Dio_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, DIO_LOW);
            Dio_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, DIO_HIGH);
            break;
        case MOTOR_STOP:
        default:
            Dio_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, DIO_LOW);
            Dio_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, DIO_LOW);
            break;
    }
}

void Motor_Stop(void) {
    Motor_SetDirection(MOTOR_STOP);
    Motor_SetSpeed(0);
}

void Motor_Drive(uint8_t direction, uint8_t speed) {
    Motor_SetDirection(direction);
    Motor_SetSpeed(speed);
}
