/*
 * UART.c - UART Driver Implementation
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Circular buffer for receiving
static volatile uint8_t rx_buffer[UART_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

// UART RX interrupt
ISR(USART_RXC_vect) {
    uint8_t data = UDR;
    uint8_t next_head = (rx_head + 1) % UART_BUFFER_SIZE;
    
    if(next_head != rx_tail) {
        rx_buffer[rx_head] = data;
        rx_head = next_head;
    }
}

void UART_Init(uint32_t baud_rate) {
    // Calculate UBRR value
    // UBRR = (F_CPU / (16 * baud_rate)) - 1
    uint16_t ubrr = (8000000UL / (16UL * baud_rate)) - 1;
    
    // Set baud rate
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;
    
    // Enable receiver, transmitter, and RX interrupt
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
    
    // Clear buffers
    rx_head = 0;
    rx_tail = 0;
}

void UART_SendByte(uint8_t data) {
    // Wait for empty transmit buffer
    while(!(UCSRA & (1 << UDRE)));
    
    // Put data into buffer, sends the data
    UDR = data;
}

uint8_t UART_ReceiveByte(void) {
    // Wait for data to be received
    while(!(UCSRA & (1 << RXC)));
    
    // Get and return received data from buffer
    return UDR;
}

void UART_SendString(const char *str) {
    while(*str) {
        UART_SendByte(*str++);
    }
}

void UART_SendData(uint8_t *data, uint16_t length) {
    for(uint16_t i = 0; i < length; i++) {
        UART_SendByte(data[i]);
    }
}

uint8_t UART_DataAvailable(void) {
    return (rx_head != rx_tail);
}

uint8_t UART_ReadByte(void) {
    if(rx_head == rx_tail) return 0;
    
    uint8_t data = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;
    
    return data;
}
