/*
 * Dio.c - Digital Input/Output Driver Implementation
 */

#include "Dio.h"
#include <avr/io.h>

void Dio_Init(void) {
    // All ports initialized as input by default
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    
    // Clear all outputs
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

void Dio_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction) {
    if(pin > 7) return;
    
    switch(port) {
        case PORTA_REG:
            if(direction == DIO_OUTPUT) DDRA |= (1 << pin);
            else DDRA &= ~(1 << pin);
            break;
        case PORTB_REG:
            if(direction == DIO_OUTPUT) DDRB |= (1 << pin);
            else DDRB &= ~(1 << pin);
            break;
        case PORTC_REG:
            if(direction == DIO_OUTPUT) DDRC |= (1 << pin);
            else DDRC &= ~(1 << pin);
            break;
        case PORTD_REG:
            if(direction == DIO_OUTPUT) DDRD |= (1 << pin);
            else DDRD &= ~(1 << pin);
            break;
    }
}

void Dio_WritePin(uint8_t port, uint8_t pin, uint8_t value) {
    if(pin > 7) return;
    
    switch(port) {
        case PORTA_REG:
            if(value == DIO_HIGH) PORTA |= (1 << pin);
            else PORTA &= ~(1 << pin);
            break;
        case PORTB_REG:
            if(value == DIO_HIGH) PORTB |= (1 << pin);
            else PORTB &= ~(1 << pin);
            break;
        case PORTC_REG:
            if(value == DIO_HIGH) PORTC |= (1 << pin);
            else PORTC &= ~(1 << pin);
            break;
        case PORTD_REG:
            if(value == DIO_HIGH) PORTD |= (1 << pin);
            else PORTD &= ~(1 << pin);
            break;
    }
}

uint8_t Dio_ReadPin(uint8_t port, uint8_t pin) {
    if(pin > 7) return 0;
    
    uint8_t value = 0;
    switch(port) {
        case PORTA_REG:
            value = (PINA >> pin) & 0x01;
            break;
        case PORTB_REG:
            value = (PINB >> pin) & 0x01;
            break;
        case PORTC_REG:
            value = (PINC >> pin) & 0x01;
            break;
        case PORTD_REG:
            value = (PIND >> pin) & 0x01;
            break;
    }
    return value;
}

void Dio_TogglePin(uint8_t port, uint8_t pin) {
    if(pin > 7) return;
    
    switch(port) {
        case PORTA_REG:
            PORTA ^= (1 << pin);
            break;
        case PORTB_REG:
            PORTB ^= (1 << pin);
            break;
        case PORTC_REG:
            PORTC ^= (1 << pin);
            break;
        case PORTD_REG:
            PORTD ^= (1 << pin);
            break;
    }
}

void Dio_WritePort(uint8_t port, uint8_t value) {
    switch(port) {
        case PORTA_REG:
            PORTA = value;
            break;
        case PORTB_REG:
            PORTB = value;
            break;
        case PORTC_REG:
            PORTC = value;
            break;
        case PORTD_REG:
            PORTD = value;
            break;
    }
}

uint8_t Dio_ReadPort(uint8_t port) {
    uint8_t value = 0;
    switch(port) {
        case PORTA_REG:
            value = PINA;
            break;
        case PORTB_REG:
            value = PINB;
            break;
        case PORTC_REG:
            value = PINC;
            break;
        case PORTD_REG:
            value = PIND;
            break;
    }
    return value;
}
