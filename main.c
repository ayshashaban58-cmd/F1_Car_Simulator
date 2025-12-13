/*============================================================================
 * F1 Simulator - Main Application
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 100Hz Autonomous Racing Car
 *===========================================================================*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "MCAL/Dio/Dio.h"
#include "MCAL/Timer/Timer.h"
#include "MCAL/I2C/I2C.h"
#include "MCAL/UART/UART.h"

#include "HAL/Motor_L298N/Motor.h"
#include "HAL/Servo/Servo.h"
#include "HAL/MPU6050/MPU6050.h"
#include "HAL/IR_Markers_4x/IR_Markers.h"

#include "Services/Odometry/Odometry.h"
#include "Services/PID_Controller/PID.h"
#include "Services/Path_Planning/Path_Planning.h"
#include "Services/Marker_Correction/Marker_Correction.h"

#include "Application/F1_Car/F1_Car.h"
#include "Application/UART_Telemetry/Telemetry.h"

// Global variables
MPU6050_DataType imuData;
IR_Markers_DataType irData;
Odometry_DataType odomData;
PID_ControllerType steeringPID;
Path_PlanningType pathPlan;
Marker_CorrectionType markerCorrection;
F1_Car_Type f1Car;
Telemetry_CommandType command;

uint32_t lastUpdateTime = 0;
uint32_t lastTelemetryTime = 0;

void System_Init(void) {
    // Initialize all modules
    Timer0_Init();    // System tick
    Timer1_Init_PWM(); // Motor & Servo PWM
    I2C_Init();
    Telemetry_Init();
    
    Motor_Init();
    Servo_Init();
    MPU6050_Init();
    IR_Markers_Init();
    
    Odometry_Init(&odomData);
    PID_Init(&steeringPID, 0.8f, 0.0f, 0.2f, -50.0f, 50.0f); // Kp, Ki, Kd, min, max
    Path_Init(&pathPlan);
    Marker_Init(&markerCorrection);
    F1_Car_Init(&f1Car);
    
    sei(); // Enable global interrupts
}

void Control_Loop(void) {
    uint32_t currentTime = Timer_GetSystemTick();
    float dt = (currentTime - lastUpdateTime) / 1000.0f; // Convert to seconds
    
    if(dt >= 0.01f) { // 100Hz control loop
        lastUpdateTime = currentTime;
        
        // Read sensors
        MPU6050_ReadRawData(&imuData);
        MPU6050_UpdateAngle(&imuData, dt);
        IR_Markers_Scan(&irData);
        
        // Update odometry
        Odometry_Update(&odomData, &imuData, dt);
        
        // Check for marker corrections
        Marker_CheckAndCorrect(&markerCorrection, &irData, &odomData, &imuData);
        
        // Update path planning
        Path_Update(&pathPlan, &odomData);
        
        // Control based on car state
        if(f1Car.isRunning && !Path_IsCompleted(&pathPlan)) {
            // Calculate steering error
            float angleError = Path_GetAngleError(&pathPlan, &odomData);
            
            // PID control for steering
            float steeringOutput = PID_Update(&steeringPID, angleError, dt);
            
            // Map steering output to servo angle (-50 to 50 -> 0 to 100)
            uint8_t servoAngle = 50 + (int8_t)steeringOutput;
            Servo_SetAngle(servoAngle);
            
            // Set motor speed
            Motor_Drive(MOTOR_FORWARD, f1Car.motorSpeed);
        } else {
            // Stop car
            Motor_Stop();
            Servo_Center();
            if(Path_IsCompleted(&pathPlan)) {
                F1_Car_Stop(&f1Car);
            }
        }
    }
    
    // Send telemetry at 10Hz
    if((currentTime - lastTelemetryTime) >= 100) {
        lastTelemetryTime = currentTime;
        Telemetry_SendData(&odomData, &imuData, &irData, &f1Car);
    }
    
    // Process incoming commands
    if(Telemetry_ReceiveCommand(&command)) {
        Telemetry_ProcessCommand(&command, &f1Car);
    }
}

int main(void) {
    System_Init();
    _delay_ms(100); // Wait for sensors to stabilize
    
    while(1) {
        Control_Loop();
    }
    
    return 0;
}
