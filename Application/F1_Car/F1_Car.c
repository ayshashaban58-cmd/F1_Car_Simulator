#include "F1_Car.h"
#include "../../HAL/Motor_L298N/Motor.h"
#include "../../HAL/Servo/Servo.h"
#include "../UART_Telemetry/Telemetry.h"

enum State { IDLE, RUNNING };
enum State state = IDLE;

void F1_Car_Init(void) {}

void F1_Car_Update(void) {
    uint8_t cmd = UART_ReceiveByte(); // Assume non-blocking if needed
    Telemetry_ParseCommand(cmd);
    if (state == RUNNING) {
        // Continue control
    }
}

void F1_Car_Start(void) { state = RUNNING; }
void F1_Car_Stop(void) { state = IDLE; Motor_SetSpeed(0); Servo_SetAngle(0); }
void F1_Car_Reset(void) { F1_Car_Stop(); /* Reset odometry */ x = y = theta = 0; }
