#include "Dio.h"

static volatile uint8_t* getDDRRegister(Dio_PortType port) {
    switch(port) {
        case DIO_PORTA: return &DDRA;
        case DIO_PORTB: return &DDRB;
        case DIO_PORTC: return &DDRC;
        case DIO_PORTD: return &DDRD;
        default: return &DDRA;
    }
}

static volatile uint8_t* getPORTRegister(Dio_PortType port) {
    switch(port) {
        case DIO_PORTA: return &PORTA;
        case DIO_PORTB: return &PORTB;
        case DIO_PORTC: return &PORTC;
        case DIO_PORTD: return &PORTD;
        default: return &PORTA;
    }
}

static volatile uint8_t* getPINRegister(Dio_PortType port) {
    switch(port) {
        case DIO_PORTA: return &PINA;
        case DIO_PORTB: return &PINB;
        case DIO_PORTC: return &PINC;
        case DIO_PORTD: return &PIND;
        default: return &PINA;
    }
}

void Dio_SetPinDirection(Dio_PortType port, Dio_PinType pin, Dio_DirectionType dir) {
    volatile uint8_t* ddr = getDDRRegister(port);
    if(dir == DIO_OUTPUT) {
        *ddr |= (1 << pin);
    } else {
        *ddr &= ~(1 << pin);
    }
}

void Dio_WritePin(Dio_PortType port, Dio_PinType pin, Dio_LevelType level) {
    volatile uint8_t* portReg = getPORTRegister(port);
    if(level == DIO_HIGH) {
        *portReg |= (1 << pin);
    } else {
        *portReg &= ~(1 << pin);
    }
}

Dio_LevelType Dio_ReadPin(Dio_PortType port, Dio_PinType pin) {
    volatile uint8_t* pinReg = getPINRegister(port);
    return (*pinReg & (1 << pin)) ? DIO_HIGH : DIO_LOW;
}

void Dio_TogglePin(Dio_PortType port, Dio_PinType pin) {
    volatile uint8_t* portReg = getPORTRegister(port);
    *portReg ^= (1 << pin);
}

void Dio_SetPortDirection(Dio_PortType port, uint8_t dir) {
    volatile uint8_t* ddr = getDDRRegister(port);
    *ddr = dir;
}

void Dio_WritePort(Dio_PortType port, uint8_t value) {
    volatile uint8_t* portReg = getPORTRegister(port);
    *portReg = value;
}

uint8_t Dio_ReadPort(Dio_PortType port) {
    volatile uint8_t* pinReg = getPINRegister(port);
    return *pinReg;
}
