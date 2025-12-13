#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_BUFFER_SIZE 128

// Function Prototypes
void UART_Init(uint32_t baudrate);
void UART_SendByte(uint8_t data);
void UART_SendString(const char* str);
uint8_t UART_Available(void);
uint8_t UART_ReceiveByte(void);
void UART_Flush(void);

#endif /* UART_H_ */
