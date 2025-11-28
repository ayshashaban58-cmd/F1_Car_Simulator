/*============================================================================
 * L298N Motor Driver Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Steering: Motor 0, Drive: Motor 1
 *===========================================================================*/

#include "Motor.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../Config/Dio_Cfg.h"

Std_ReturnType Motor_Init(void) {
    // Initialize motor direction pins
    Dio_WriteChannel(MOTOR_DIR_IN1, STD_LOW);
    Dio_WriteChannel(MOTOR_DIR_IN2, STD_LOW);
    Dio_WriteChannel(MOTOR_DRV_IN1, STD_LOW);
    Dio_WriteChannel(MOTOR_DRV_IN2, STD_LOW);
    
    // Stop motors
    Timer_SetPWM(0, 0);  // Steering PWM
    Timer_SetPWM(1, 0);  // Drive PWM
    
    return E_OK;
}

Std_ReturnType Motor_SetDirection(Motor_IDType Motor, Motor_DirectionType Dir) {
    switch(Motor) {
        case MOTOR_STEER:
            if(Dir == DIRECTION_FORWARD) {
                Dio_WriteChannel(MOTOR_DIR_IN1, STD_HIGH);
                Dio_WriteChannel(MOTOR_DIR_IN2, STD_LOW);
            } else if(Dir == DIRECTION_BACKWARD) {
                Dio_WriteChannel(MOTOR_DIR_IN1, STD_LOW);
                Dio_WriteChannel(MOTOR_DIR_IN2, STD_HIGH);
            } else {
                Dio_WriteChannel(MOTOR_DIR_IN1, STD_LOW);
                Dio_WriteChannel(MOTOR_DIR_IN2, STD_LOW);
            }
            break;
            
        case MOTOR_DRIVE:
            if(Dir == DIRECTION_FORWARD) {
                Dio_WriteChannel(MOTOR_DRV_IN1, STD_HIGH);
                Dio_WriteChannel(MOTOR_DRV_IN2, STD_LOW);
            } else if(Dir == DIRECTION_BACKWARD) {
                Dio_WriteChannel(MOTOR_DRV_IN1, STD_LOW);
                Dio_WriteChannel(MOTOR_DRV_IN2, STD_HIGH);
            } else {
                Dio_WriteChannel(MOTOR_DRV_IN1, STD_LOW);
                Dio_WriteChannel(MOTOR_DRV_IN2, STD_LOW);
            }
            break;
    }
    return E_OK;
}

Std_ReturnType Motor_SetSpeed(Motor_IDType Motor, uint16_t SpeedPercent) {
    uint16_t Duty = (SpeedPercent * 10);  // 0-100% → 0-1000
    if(Duty > 1000) Duty = 1000;
    
    Timer_SetPWM(Motor, Duty);
    return E_OK;
}

Std_ReturnType Motor_Stop(Motor_IDType Motor) {
    Motor_SetDirection(Motor, DIRECTION_STOP);
    Timer_SetPWM(Motor, 0);
    return E_OK;
}
