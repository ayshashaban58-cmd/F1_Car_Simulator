#include "Timer.h"

volatile uint32_t systemTicks = 0;

// Timer0 for system tick (1ms interrupt)
void Timer0_Init(void) {
    // CTC mode, prescaler 64
    TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00);
    OCR0 = 124; // 8MHz/64/125 = 1kHz (1ms)
    TIMSK |= (1 << OCIE0); // Enable compare match interrupt
}

// Timer1 for PWM (Motor & Servo)
void Timer1_Init_PWM(void) {
    // Fast PWM, ICR1 as TOP, non-inverting mode
    // OC1A = PD5 (Motor PWM), OC1B = PD4 (Servo PWM)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
    ICR1 = 19999; // 20ms period for servo (8MHz/8/20000 = 50Hz)
    OCR1A = 0; // Motor duty
    OCR1B = 1500; // Servo center (1.5ms pulse)
}

// Timer2 for additional timing (optional)
void Timer2_Init(void) {
    // Normal mode, prescaler 64
    TCCR2 = (1 << CS22);
}

void Timer_SetPWM(Timer_ChannelType channel, uint8_t duty) {
    switch(channel) {
        case TIMER1_CHANNELA: // Motor
            OCR1A = (uint16_t)((duty * ICR1) / 100);
            break;
        case TIMER1_CHANNELB: // Servo (duty = 0-100, map to 1000-2000us)
            // 0% = 1ms (1000), 50% = 1.5ms (1500), 100% = 2ms (2000)
            OCR1B = 1000 + (duty * 10);
            break;
        default:
            break;
    }
}

uint32_t Timer_GetSystemTick(void) {
    uint32_t ticks;
    cli();
    ticks = systemTicks;
    sei();
    return ticks;
}

void Timer_DelayMs(uint16_t ms) {
    uint32_t start = Timer_GetSystemTick();
    while((Timer_GetSystemTick() - start) < ms);
}

// Timer0 Compare Match ISR
ISR(TIMER0_COMP_vect) {
    systemTicks++;
}
