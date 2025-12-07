/*
 * Timer.c - Timer Driver Implementation
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint32_t system_ticks;

void Timer_Init(void) {
    // Timer0: CTC mode for 100Hz system tick
    // F_CPU = 8MHz, Prescaler = 1024
    // OCR0 = (8000000 / (1024 * 100)) - 1 = 77
    TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00); // CTC, prescaler 1024
    OCR0 = 77;
    TIMSK |= (1 << OCIE0); // Enable compare match interrupt
    
    // Timer1: Fast PWM mode, 10-bit
    // Non-inverting mode for both OC1A and OC1B
    // Prescaler = 8, PWM frequency = 8MHz/(8*1024) = ~977Hz
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // Non-inverting, Fast PWM 10-bit
    TCCR1B = (1 << WGM12) | (1 << CS11); // Fast PWM 10-bit, prescaler 8
    ICR1 = 1023; // 10-bit resolution
    
    // Initialize PWM outputs to 0
    OCR1A = 0; // Motor
    OCR1B = 0; // Servo
    
    // Set PWM pins as output
    DDRD |= (1 << PD5) | (1 << PD4); // OC1A and OC1B
}

void Timer_SetPWM(uint8_t channel, uint16_t duty) {
    // Limit duty cycle to 10-bit (0-1023)
    if(duty > 1023) duty = 1023;
    
    switch(channel) {
        case PWM_MOTOR:
            OCR1A = duty;
            break;
        case PWM_SERVO:
            OCR1B = duty;
            break;
    }
}

uint32_t Timer_GetTicks(void) {
    return system_ticks;
}
