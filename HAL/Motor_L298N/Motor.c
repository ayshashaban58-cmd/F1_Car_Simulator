// src/HAL/Motor_L298N/Motor.c

#include "Motor.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"

// Assume pins: IN1 PB0, IN2 PB1, ENA PD6 (PWM)

void Motor_Init(void) {
    Dio_WritePin(0, 0); // PB0
    Dio_WritePin(1, 0); // PB1
}

void Motor_SetSpeed(int16_t speed) {
    uint16_t abs_speed = (speed < 0) ? -speed : speed;
    Timer_SetPWM(0, abs_speed);
    if (speed > 0) {
        Dio_WritePin(0, 1);
        Dio_WritePin(1, 0);
    } else if (speed < 0) {
        Dio_WritePin(0, 0);
        Dio_WritePin(1, 1);
    } else {
        Motor_Stop();
    }
}

void Motor_SetDirection(uint8_t dir) {
    // Integrated in SetSpeed
}

void Motor_Stop(void) {
    Dio_WritePin(0, 0);
    Dio_WritePin(1, 0);
    Timer_SetPWM(0, 0);
}
