// src/MCAL/Dio/Dio.c

#include <avr/io.h>
#include "Dio.h"

void Dio_Init(void) {
    // Initialize all pins as needed
    DDRA = 0xFF; // Example: Port A output
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
}

void Dio_WritePin(uint8_t pin, uint8_t value) {
    if (pin < 8) {
        if (value) PORTA |= (1 << pin);
        else PORTA &= ~(1 << pin);
    } // Add for other ports
    // Extend for all pins 0-31
}

uint8_t Dio_ReadPin(uint8_t pin) {
    if (pin < 8) return (PINA & (1 << pin)) ? 1 : 0;
    // Extend for all pins
    return 0;
}

void Dio_TogglePin(uint8_t pin) {
    if (pin < 8) PORTA ^= (1 << pin);
    // Extend
}
