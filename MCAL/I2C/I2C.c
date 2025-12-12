#include <avr/io.h>
#include "I2C.h"

void I2C_Init(void) {
    TWBR = 72; // 100kHz at 8MHz
    TWSR = 0;
}

void I2C_Start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_WriteByte(uint8_t byte) {
    TWDR = byte;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_ReadByte(uint8_t ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

void I2C_Write(uint8_t addr, uint8_t reg, uint8_t data) {
    I2C_Start();
    I2C_WriteByte(addr << 1);
    I2C_WriteByte(reg);
    I2C_WriteByte(data);
    I2C_Stop();
}

uint8_t I2C_Read(uint8_t addr, uint8_t reg) {
    I2C_Start();
    I2C_WriteByte(addr << 1);
    I2C_WriteByte(reg);
    I2C_Start();
    I2C_WriteByte((addr << 1) | 1);
    uint8_t data = I2C_ReadByte(0);
    I2C_Stop();
    return data;
}
