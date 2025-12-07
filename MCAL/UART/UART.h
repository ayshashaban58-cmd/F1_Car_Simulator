/*
 * UART.h - UART Driver for ESP32 Communication
 * TX: PD1, RX: PD0
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#define UART_BUFFER_SIZE 128

// Function prototypes
void UART_Init(uint32_t baud_rate);
void UART_SendByte(uint8_t data);
uint8_t UART_ReceiveByte(void);
void UART_SendString(const char *str);
void UART_SendData(uint8_t *data, uint16_t length);
uint8_t UART_DataAvailable(void);
uint8_t UART_ReadByte(void);

#endif /* UART_H_ */
