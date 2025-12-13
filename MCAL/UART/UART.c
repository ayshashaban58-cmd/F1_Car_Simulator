#include "UART.h"

static volatile uint8_t rxBuffer[UART_BUFFER_SIZE];
static volatile uint8_t rxHead = 0;
static volatile uint8_t rxTail = 0;

void UART_Init(uint32_t baudrate) {
    uint16_t ubrr = (F_CPU / (16UL * baudrate)) - 1;
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE); // Enable RX, TX, RX interrupt
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data, 1 stop bit
}

void UART_SendByte(uint8_t data) {
    while(!(UCSRA & (1 << UDRE)));
    UDR = data;
}

void UART_SendString(const char* str) {
    while(*str) {
        UART_SendByte(*str++);
    }
}

uint8_t UART_Available(void) {
    return (rxHead != rxTail);
}

uint8_t UART_ReceiveByte(void) {
    while(rxHead == rxTail);
    uint8_t data = rxBuffer[rxTail];
    rxTail = (rxTail + 1) % UART_BUFFER_SIZE;
    return data;
}

void UART_Flush(void) {
    rxHead = 0;
    rxTail = 0;
}

ISR(USART_RXC_vect) {
    uint8_t data = UDR;
    uint8_t nextHead = (rxHead + 1) % UART_BUFFER_SIZE;
    if(nextHead != rxTail) {
        rxBuffer[rxHead] = data;
        rxHead = nextHead;
    }
}
