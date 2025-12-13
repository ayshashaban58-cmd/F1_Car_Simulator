#include "I2C.h"

void I2C_Init(void) {
    // Set SCL to 100kHz: TWBR = ((F_CPU/SCL_FREQ)-16)/(2*Prescaler)
    // F_CPU = 8MHz, SCL = 100kHz, Prescaler = 1
    TWBR = 32; // (8000000/100000 - 16)/2 = 32
    TWSR = 0x00; // Prescaler = 1
}

I2C_StatusType I2C_Start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    if((TWSR & 0xF8) != I2C_START && (TWSR & 0xF8) != I2C_REP_START) {
        return I2C_ERROR;
    }
    return I2C_OK;
}

I2C_StatusType I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    uint8_t status = TWSR & 0xF8;
    if(status != I2C_MT_SLA_ACK && status != I2C_MT_DATA_ACK && status != I2C_MR_SLA_ACK) {
        return I2C_ERROR;
    }
    return I2C_OK;
}

uint8_t I2C_ReadACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t I2C_ReadNACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}

void I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

I2C_StatusType I2C_WriteRegister(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    if(I2C_Start() != I2C_OK) return I2C_ERROR;
    if(I2C_Write((devAddr << 1) | 0) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Write(regAddr) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Write(data) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    I2C_Stop();
    return I2C_OK;
}

I2C_StatusType I2C_ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data) {
    if(I2C_Start() != I2C_OK) return I2C_ERROR;
    if(I2C_Write((devAddr << 1) | 0) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Write(regAddr) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Start() != I2C_OK) return I2C_ERROR;
    if(I2C_Write((devAddr << 1) | 1) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    *data = I2C_ReadNACK();
    I2C_Stop();
    return I2C_OK;
}

I2C_StatusType I2C_ReadMultiple(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length) {
    if(I2C_Start() != I2C_OK) return I2C_ERROR;
    if(I2C_Write((devAddr << 1) | 0) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Write(regAddr) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    if(I2C_Start() != I2C_OK) return I2C_ERROR;
    if(I2C_Write((devAddr << 1) | 1) != I2C_OK) {
        I2C_Stop();
        return I2C_ERROR;
    }
    for(uint8_t i = 0; i < length - 1; i++) {
        buffer[i] = I2C_ReadACK();
    }
    buffer[length - 1] = I2C_ReadNACK();
    I2C_Stop();
    return I2C_OK;
}
