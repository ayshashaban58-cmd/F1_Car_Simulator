/*============================================================================
 * F1 Car State Machine Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Main application logic
 *===========================================================================*/

#include "F1_Car.h"
#include "../../HAL/Motor_L298N/Motor.h"
#include "../Services/PID_Controller/PID.h"
#include "../Services/Odometry/Odometry.h"
#include "../Services/Marker_Correction/Marker_Correction.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../Config/Dio_Cfg.h"
#include "../../Config/Motor_Cfg.h"

F1_Car_t F1Car = {F1_STATE_IDLE, 0, 0, 999.0f, FALSE};

Std_ReturnType F1_Car_Init(void) {
    F1Car.CurrentState = F1_STATE_IDLE;
    Motor_Stop(MOTOR_STEER);
    Motor_Stop(MOTOR_DRIVE);
    SpeedPID.Setpoint = TARGET_RPM;
    return E_OK;
}

void F1_Car_Start(void) {
    if(F1Car.CurrentState == F1_STATE_IDLE) {
        F1_Car_Reset();
        F1Car.CurrentState = F1_STATE_READY;
        F1Car.RaceActive = TRUE;
    }
}

void F1_Car_Stop(void) {
    F1Car.RaceActive = FALSE;
    Motor_Stop(MOTOR_STEER);
    Motor_Stop(MOTOR_DRIVE);
    F1Car.CurrentState = F1_STATE_IDLE;
}

void F1_Car_Reset(void) {
    Odometry_Init(0.0f, 0.0f);
    F1Car.CurrentLap = 0;
    F1Car.LapStartTime = Timer_GetTick();
}

Std_ReturnType F1_Car_Update(void) {
    switch(F1Car.CurrentState) {
        case F1_STATE_READY:
            if(F1Car.RaceActive) {
                F1Car.CurrentState = F1_STATE_RACING;
            }
            break;
            
        case F1_STATE_RACING:
            if(!F1Car.RaceActive) {
                F1Car.CurrentState = F1_STATE_FINISHED;
                Motor_Stop(MOTOR_DRIVE);
                Motor_Stop(MOTOR_STEER);
            }
            break;
            
        case F1_STATE_FINISHED:
        case F1_STATE_IDLE:
        case F1_STATE_ERROR:
        default:
            break;
    }
    return E_OK;
}
