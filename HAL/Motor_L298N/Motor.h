/*============================================================================
 * L298N Dual Motor Driver
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Motor 0: Steering, Motor 1: Drive
 *===========================================================================*/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "../Config/Std_Types.h"

typedef enum {
    MOTOR_STEER = 0,
    MOTOR_DRIVE = 1
} Motor_IDType;

typedef enum {
    DIRECTION_STOP = 0,
    DIRECTION_FORWARD,
    DIRECTION_BACKWARD
} Motor_DirectionType;

Std_ReturnType Motor_Init(void);
Std_ReturnType Motor_SetDirection(Motor_IDType Motor, Motor_DirectionType Dir);
Std_ReturnType Motor_SetSpeed(Motor_IDType Motor, uint16_t SpeedPercent);
Std_ReturnType Motor_Stop(Motor_IDType Motor);

#endif
