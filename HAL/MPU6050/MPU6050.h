// src/HAL/MPU6050/MPU6050.h

#ifndef MPU6050_H
#define MPU6050_H

#define MPU6050_ADDR 0x68

void MPU6050_Init(void);
void MPU6050_ReadAccel(int16_t* ax, int16_t* ay, int16_t* az);
void MPU6050_ReadGyro(int16_t* gx, int16_t* gy, int16_t* gz);

#endif
