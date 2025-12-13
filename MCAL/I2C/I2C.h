#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

// I2C Status Codes
#define I2C_START 0x08
#define I2C_REP_START 0x10
#define I2C_MT_SLA_ACK 0x18
#define I2C_MT_DATA_ACK 0x28
#define I2C_MR_SLA_ACK 0x40
#define I2C_MR_DATA_ACK 0x50
#define I2C_MR_DATA_NACK 0x58

typedef enum {
    I2C_OK = 0,
    I2C_ERROR
} I2C_StatusType;

// Function Prototypes
void I2C_Init(void);
I2C_StatusType I2C_Start(void);
I2C_StatusType I2C_Write(uint8_t data);
uint8_t I2C_ReadACK(void);
uint8_t I2C_ReadNACK(void);
void I2C_Stop(void);
I2C_StatusType I2C_WriteRegister(uint8_t devAddr, uint8_t regAddr, uint8_t data);
I2C_StatusType I2C_ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data);
I2C_StatusType I2C_ReadMultiple(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length);

#endif /* I2C_H_ */
