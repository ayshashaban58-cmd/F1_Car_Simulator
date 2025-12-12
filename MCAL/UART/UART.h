#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_SendByte(uint8_t byte);
uint8_t UART_ReceiveByte(void);
void UART_SendString(const char* str);

#endif
