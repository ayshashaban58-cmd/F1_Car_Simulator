/*
 * I2C.c - I2C/TWI Driver Implementation
 */

#include "I2C.h"
#include <avr/io.h>
#include <util/delay.h>

#define F_SCL 100000UL // 100kHz I2C clock
#define TWI_START 0x08
#define TWI_REP_START 0x10
#define TWI_MT_SLA_ACK 0x18
#define TWI_MT_DATA_ACK 0x28
#define TWI_MR_SLA_ACK 0x40
#define TWI_MR_DATA_ACK 0x50
#define TWI_MR_DATA_NACK 0x58

void I2C_Init(void) {
    // Set SCL frequency: TWBR = ((F_CPU / F_SCL) - 16) / 2
    // For F_CPU = 8MHz, F_SCL = 100kHz: TWBR = 32
    TWBR = 32;
    TWSR = 0x00; // Prescaler = 1
    TWCR = (1 << TWEN); // Enable TWI
}

uint8_t I2C_Start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    
    if((TWSR & 0xF8) != TWI_START && (TWSR & 0xF8) != TWI_REP_START)
        return I2C_ERROR;
    
    return I2C_SUCCESS;
}

void I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(100);
}

uint8_t I2C_WriteByte(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    
    uint8_t status = TWSR & 0xF8;
    if(status != TWI_MT_SLA_ACK && status != TWI_MT_DATA_ACK)
        return I2C_ERROR;
    
    return I2C_SUCCESS;
}

uint8_t I2C_ReadByte(uint8_t *data, uint8_t ack) {
    if(ack)
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    else
        TWCR = (1 << TWINT) | (1 << TWEN);
    
    while(!(TWCR & (1 << TWINT)));
    
    *data = TWDR;
    
    uint8_t status = TWSR & 0xF8;
    if((ack && status != TWI_MR_DATA_ACK) || (!ack && status != TWI_MR_DATA_NACK))
        return I2C_ERROR;
    
    return I2C_SUCCESS;
}

uint8_t I2C_WriteRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t data) {
    if(I2C_Start() != I2C_SUCCESS) return I2C_ERROR;
    if(I2C_WriteByte(device_addr << 1) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_WriteByte(reg_addr) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_WriteByte(data) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    I2C_Stop();
    return I2C_SUCCESS;
}

uint8_t I2C_ReadRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t *data) {
    if(I2C_Start() != I2C_SUCCESS) return I2C_ERROR;
    if(I2C_WriteByte(device_addr << 1) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_WriteByte(reg_addr) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Start() != I2C_SUCCESS) return I2C_ERROR;
    if(I2C_WriteByte((device_addr << 1) | 0x01) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_ReadByte(data, 0) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    I2C_Stop();
    return I2C_SUCCESS;
}

uint8_t I2C_ReadMultipleRegisters(uint8_t device_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t length) {
    if(I2C_Start() != I2C_SUCCESS) return I2C_ERROR;
    if(I2C_WriteByte(device_addr << 1) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_WriteByte(reg_addr) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Start() != I2C_SUCCESS) return I2C_ERROR;
    if(I2C_WriteByte((device_addr << 1) | 0x01) != I2C_SUCCESS) {
        I2C_Stop();
        return I2C_ERROR;
    }
    
    for(uint8_t i = 0; i < length; i++) {
        uint8_t ack = (i < length - 1) ? 1 : 0;
        if(I2C_ReadByte(&buffer[i], ack) != I2C_SUCCESS) {
            I2C_Stop();
            return I2C_ERROR;
        }
    }
    
    I2C_Stop();
    return I2C_SUCCESS;
}
