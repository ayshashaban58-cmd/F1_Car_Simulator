// src/Application/F1_Car/F1_Car.c

#include "F1_Car.h"
#include "../../HAL/Motor_L298N/Motor.h"
#include "../../HAL/Servo/Servo.h"
#include "../UART_Telemetry/Telemetry.h"

enum State { IDLE, RUNNING };
enum State state = IDLE;

void F1_Car_Init(void) {}

void F1_Car_Update(void) {
    // Check commands from telemetry
    if (state == RUNNING) {
        // Continue
    }
}

void F1_Car_Start(void) { state = RUNNING; }
void F1_Car_Stop(void) { state = IDLE; Motor_Stop(); Servo_SetAngle(0); }
void F1_Car_Reset(void) { F1_Car_Stop(); /* Reset odometry etc */ }
