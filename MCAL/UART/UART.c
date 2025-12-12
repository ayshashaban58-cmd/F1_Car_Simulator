// src/MCAL/UART/UART.c

#include <avr/io.h>
#include "UART.h"

void UART_Init(void) {
    UBRRH = 0;
    UBRRL = 51; // 9600 baud at 8MHz
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void UART_SendByte(uint8_t byte) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = byte;
}

uint8_t UART_ReceiveByte(void) {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

void UART_SendString(const char* str) {
    while (*str) UART_SendByte(*str++);
}
