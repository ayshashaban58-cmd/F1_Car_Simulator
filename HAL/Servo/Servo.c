#include "Servo.h"

void Servo_Init(void) {
    Dio_SetPinDirection(SERVO_PWM_PORT, SERVO_PWM_PIN, DIO_OUTPUT);
    Servo_Center();
}

void Servo_SetAngle(uint8_t angle) {
    if(angle > 100) angle = 100;
    Timer_SetPWM(TIMER1_CHANNELB, angle);
}

void Servo_Center(void) {
    Servo_SetAngle(SERVO_CENTER);
}

void Servo_TurnLeft(uint8_t amount) {
    if(amount > 50) amount = 50;
    Servo_SetAngle(SERVO_CENTER - amount);
}

void Servo_TurnRight(uint8_t amount) {
    if(amount > 50) amount = 50;
    Servo_SetAngle(SERVO_CENTER + amount);
}
