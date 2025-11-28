/*============================================================================
 * UART Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * UART0 for ESP32 communication
 *===========================================================================*/

#include "UART.h"
#include <avr32/io.h>

Std_ReturnType UART_Init(uint32_t BaudRate) {
    // 115200 baud @ 50MHz
    avr32_usart0.mr = 0x000C0000;        // Normal mode
    avr32_usart0.brgr = 135;             // Baud rate
    avr32_usart0.cr = 0x00000040;        // RX/TX enable
    avr32_usart0.ier = 0x00000020;       // RX interrupt
    return E_OK;
}

Std_ReturnType UART_SendByte(uint8_t Byte) {
    while(!(avr32_usart0.csr & 0x40));   // Wait TX ready
    avr32_usart0 thr = Byte;
    return E_OK;
}

Std_ReturnType UART_SendString(const char* Str) {
    while(*Str) {
        UART_SendByte(*Str++);
    }
    UART_SendByte('\n');
    return E_OK;
}

Std_ReturnType UART_ReceiveByte(uint8_t* Byte) {
    if(avr32_usart0.csr & 0x20) {        // RX ready
        *Byte = avr32_usart0.rhr;
        return E_OK;
    }
    return E_NOT_OK;
}

boolean UART_Available(void) {
    return (avr32_usart0.csr & 0x20) != 0;
}
