// src/HAL/Servo/Servo.c

#include "Servo.h"
#include "../../MCAL/Timer/Timer.h"

// Assume Timer1 Channel B for servo PWM, pin PB2 OC1B

void Servo_Init(void) {
    TCCR1A |= (1 << COM1B1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Fast PWM ICR1 top, prescaler 8
    ICR1 = 20000; // 20ms period
    DDRB |= (1 << PB2);
}

void Servo_SetAngle(int8_t angle) {
    uint16_t pulse = 1500 + (angle * 500 / 90); // 1ms to 2ms
    OCR1B = pulse;
}
