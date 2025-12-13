#ifndef DIO_H_
#define DIO_H_

#include <avr/io.h>

// Pin Definitions
typedef enum {
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
} Dio_PinType;

typedef enum {
    DIO_PORTA = 0,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD
} Dio_PortType;

typedef enum {
    DIO_LOW = 0,
    DIO_HIGH
} Dio_LevelType;

typedef enum {
    DIO_INPUT = 0,
    DIO_OUTPUT
} Dio_DirectionType;

// Function Prototypes
void Dio_SetPinDirection(Dio_PortType port, Dio_PinType pin, Dio_DirectionType dir);
void Dio_WritePin(Dio_PortType port, Dio_PinType pin, Dio_LevelType level);
Dio_LevelType Dio_ReadPin(Dio_PortType port, Dio_PinType pin);
void Dio_TogglePin(Dio_PortType port, Dio_PinType pin);
void Dio_SetPortDirection(Dio_PortType port, uint8_t dir);
void Dio_WritePort(Dio_PortType port, uint8_t value);
uint8_t Dio_ReadPort(Dio_PortType port);

#endif /* DIO_H_ */
