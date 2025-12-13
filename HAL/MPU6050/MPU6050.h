#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>
#include "../MCAL/I2C/I2C.h"

// MPU6050 I2C Address
#define MPU6050_ADDR 0x68

// MPU6050 Registers
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43

typedef struct {
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
    float angleZ; // Yaw angle in degrees
} MPU6050_DataType;

// Function Prototypes
void MPU6050_Init(void);
void MPU6050_ReadRawData(MPU6050_DataType* data);
void MPU6050_UpdateAngle(MPU6050_DataType* data, float dt);
void MPU6050_ResetAngle(MPU6050_DataType* data);

#endif /* MPU6050_H_ */
