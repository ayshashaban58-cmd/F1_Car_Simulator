#include "Motor.h"

void Motor_Init(void) {
    Dio_SetPinDirection(MOTOR_IN1_PORT, MOTOR_IN1_PIN, DIO_OUTPUT);
    Dio_SetPinDirection(MOTOR_IN2_PORT, MOTOR_IN2_PIN, DIO_OUTPUT);
    Dio_SetPinDirection(MOTOR_PWM_PORT, MOTOR_PWM_PIN, DIO_OUTPUT);
    Motor_Stop();
}

void Motor_SetSpeed(uint8_t speed) {
    if(speed > 100) speed = 100;
    Timer_SetPWM(TIMER1_CHANNELA, speed);
}

void Motor_SetDirection(Motor_DirectionType dir) {
    switch(dir) {
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

void Motor_Drive(Motor_DirectionType dir, uint8_t speed) {
    Motor_SetDirection(dir);
    Motor_SetSpeed(speed);
}
