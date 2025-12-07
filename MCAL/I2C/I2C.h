/*
 * I2C.h - I2C/TWI Driver for MPU6050
 * SCL: PC0, SDA: PC1
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

// I2C status codes
#define I2C_SUCCESS 0
#define I2C_ERROR   1

// Function prototypes
void I2C_Init(void);
uint8_t I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(uint8_t *data, uint8_t ack);
uint8_t I2C_WriteRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t data);
uint8_t I2C_ReadRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t *data);
uint8_t I2C_ReadMultipleRegisters(uint8_t device_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t length);

#endif /* I2C_H_ */
