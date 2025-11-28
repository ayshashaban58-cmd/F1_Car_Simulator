/*============================================================================
 * DIO Driver Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Direct GPIO control for all peripherals
 *===========================================================================*/

#include "Dio.h"
#include <avr32/io.h>

Std_ReturnType Dio_Init(void) {
    // Configure motor pins as OUTPUT
    avr32_gpio.port[0].gpers = 0x0F;  // PA0-PA3 = GPIO output
    
    // Configure IR sensors as INPUT
    avr32_gpio.port[1].gperc = 0x0F;  // PB0-PB3 = peripheral input
    
    // Configure encoder as INPUT
    avr32_gpio.port[4].gperc = 0x03;  // PE0-PE1 = peripheral input
    
    // Configure I2C pins
    avr32_gpio.port[2].gperc = 0x03;  // PC0-PC1 = I2C
    
    // Configure LED as OUTPUT
    avr32_gpio.port[3].gpers = (1<<4); // PD4 = GPIO output
    
    return E_OK;
}

Std_ReturnType Dio_WriteChannel(uint8_t Channel, Dio_LevelType Level) {
    uint8_t port = Channel / 8;
    uint8_t pin = Channel % 8;
    
    if(Level == STD_HIGH) {
        avr32_gpio.port[port].ovrs = (1 << pin);
    } else {
        avr32_gpio.port[port].ovrc = (1 << pin);
    }
    return E_OK;
}

Std_ReturnType Dio_ReadChannel(uint8_t Channel, Dio_LevelType* Level) {
    uint8_t port = Channel / 8;
    uint8_t pin = Channel % 8;
    *Level = (avr32_gpio.port[port].pvr >> pin) & 1;
    return E_OK;
}

Std_ReturnType Dio_ToggleChannel(uint8_t Channel) {
    uint8_t port = Channel / 8;
    uint8_t pin = Channel % 8;
    avr32_gpio.port[port].ovrt = (1 << pin);
    return E_OK;
}
