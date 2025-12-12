#include <avr/io.h>
#include "Dio.h"

void Dio_Init(void) {
    // Outputs for Motor: PB0 (IN1), PB1 (IN2), PD6 (ENA PWM)
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD |= (1 << PD6);
    // Output for Servo: PB2 (PWM)
    DDRB |= (1 << PB2);
    // Inputs for IR Markers: PC2-PC5
    DDRC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
    // I2C: PC0 (SCL), PC1 (SDA) - handled in I2C_Init
    // UART: PD0 (RX), PD1 (TX) - handled in UART_Init
}

void Dio_WritePin(char port, uint8_t bit, uint8_t value) {
    if (port == 'B') {
        if (value) PORTB |= (1 << bit);
        else PORTB &= ~(1 << bit);
    } else if (port == 'D') {
        if (value) PORTD |= (1 << bit);
        else PORTD &= ~(1 << bit);
    } // Add 'A', 'C' if needed
}

uint8_t Dio_ReadPin(char port, uint8_t bit) {
    if (port == 'B') return (PINB & (1 << bit)) ? 1 : 0;
    if (port == 'C') return (PINC & (1 << bit)) ? 1 : 0;
    if (port == 'D') return (PIND & (1 << bit)) ? 1 : 0;
    return 0;
}

void Dio_TogglePin(char port, uint8_t bit) {
    if (port == 'B') PORTB ^= (1 << bit);
    if (port == 'D') PORTD ^= (1 << bit);
}
