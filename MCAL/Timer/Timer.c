// src/MCAL/Timer/Timer.c

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

extern volatile uint32_t system_tick;

void Timer_Init(void) {
    // Timer1 for 100Hz interrupt, 8MHz clock
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12); // CTC, prescaler 256
    OCR1A = 312; // For 100Hz: 8000000 / 256 / 100 = 312.5
    TIMSK1 = (1 << OCIE1A);

    // PWM for motor and servo (Timer0 for example)
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Fast PWM
    TCCR0B = (1 << CS01); // Prescaler 8
    DDRD |= (1 << PD6); // OC0A
}

void Timer_SetPWM(uint8_t channel, uint16_t duty) {
    if (channel == 0) OCR0A = duty; // 0-255
    // Add more channels
}

uint32_t Timer_GetTick(void) {
    return system_tick;
}
