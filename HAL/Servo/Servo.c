#include "Servo.h"
#include "../../MCAL/Timer/Timer.h"

void Servo_Init(void) {
    // Already in Timer_Init
}

void Servo_SetAngle(int8_t angle) {
    uint16_t pulse = 1500 + (angle * 500 / 90); // 1000-2000us
    Timer_SetPWM(1, pulse); // Channel 1 for Servo
}
