// src/MCAL/I2C/I2C.h

#ifndef I2C_H
#define I2C_H

void I2C_Init(void);
void I2C_Write(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t I2C_Read(uint8_t addr, uint8_t reg);

#endif
