/*============================================================================
 * UART Driver - ESP32 Communication
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 115200 baud for telemetry
 *===========================================================================*/

#ifndef UART_H_
#define UART_H_

#include "../Config/Std_Types.h"

Std_ReturnType UART_Init(uint32_t BaudRate);
Std_ReturnType UART_SendByte(uint8_t Byte);
Std_ReturnType UART_SendString(const char* Str);
Std_ReturnType UART_ReceiveByte(uint8_t* Byte);
boolean UART_Available(void);

#endif
