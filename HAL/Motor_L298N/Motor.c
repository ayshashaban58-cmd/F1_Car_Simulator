/*
 * Dio.h - Digital Input/Output Driver
 * ATmega32 Pin Control
 */

#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

// Port definitions
#define PORTA_REG 0
#define PORTB_REG 1
#define PORTC_REG 2
#define PORTD_REG 3

// Pin direction
#define DIO_INPUT  0
#define DIO_OUTPUT 1

// Pin state
#define DIO_LOW  0
#define DIO_HIGH 1

// Function prototypes
void Dio_Init(void);
void Dio_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction);
void Dio_WritePin(uint8_t port, uint8_t pin, uint8_t value);
uint8_t Dio_ReadPin(uint8_t port, uint8_t pin);
void Dio_TogglePin(uint8_t port, uint8_t pin);
void Dio_WritePort(uint8_t port, uint8_t value);
uint8_t Dio_ReadPort(uint8_t port);

#endif /* DIO_H_ */
