/*============================================================================
 * F1 Simulator - Main Application
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 100Hz Autonomous Racing Car
 *===========================================================================*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MCAL/Dio/Dio.h"
#include "MCAL/Timer/Timer.h"
#include "MCAL/I2C/I2C.h"
#include "MCAL/UART/UART.h"
#include "HAL/Motor_L298N/Motor.h"
#include "HAL/MPU6050/MPU6050.h"
#include "HAL/Servo/Servo.h"
#include "HAL/IR_Markers_4x/IR_Markers.h"
#include "Services/Odometry/Odometry.h"
#include "Services/PID_Controller/PID.h"
#include "Services/Path_Planning/Path_Planning.h"
#include "Services/Marker_Correction/Marker_Correction.h"
#include "Application/F1_Car/F1_Car.h"
#include "Application/UART_Telemetry/Telemetry.h"

volatile uint32_t system_tick = 0;

ISR(TIMER1_COMPA_vect) {
    system_tick++;
    Odometry_Update();
    IR_Markers_Scan();
    Marker_Correction_Correct();
    Path_Planning_Update();
    PID_Update();
    Motor_SetSpeed(pid_speed_output);
    Servo_SetAngle(pid_steering_output);
    Telemetry_Send();
}

int main(void) {
    Dio_Init();
    Timer_Init();
    I2C_Init();
    UART_Init();
    Motor_Init();
    MPU6050_Init();
    Servo_Init();
    IR_Markers_Init();
    Odometry_Init();
    PID_Init();
    Path_Planning_Init();
    Marker_Correction_Init();
    F1_Car_Init();

    sei(); // Enable global interrupts

    while (1) {
        F1_Car_Update();
        _delay_ms(10); // 100Hz loop approximation
    }
}
