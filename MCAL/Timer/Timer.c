#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

extern volatile uint32_t system_tick;

void Timer_Init(void) {
    // Timer1 for 100Hz system tick (CTC mode, prescaler 256)
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12);
    OCR1A = 312; // 8MHz / 256 / 100 = 312.5 ~100Hz
    TIMSK = (1 << OCIE1A);

    // Timer0 for Motor PWM on PD6 (OC0)
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // Fast PWM, prescaler 8
    DDRD |= (1 << PD6);
    OCR0 = 0;

    // Timer1 Channel B for Servo PWM on PB2 (OC1B)
    TCCR1A |= (1 << COM1B1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Fast PWM, ICR1 top, prescaler 8
    ICR1 = 20000; // 20ms period for servo
    DDRB |= (1 << PB2);
    OCR1B = 1500; // Neutral
}

void Timer_SetPWM(uint8_t channel, uint16_t duty) {
    if (channel == 0) OCR0 = (uint8_t)duty; // Motor 0-255
    if (channel == 1) OCR1B = duty; // Servo pulse width
}

uint32_t Timer_GetTick(void) {
    return system_tick;
}
