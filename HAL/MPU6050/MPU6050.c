#include "MPU6050.h"
#include "../../MCAL/I2C/I2C.h"

void MPU6050_Init(void) {
    I2C_Write(MPU6050_ADDR, 0x6B, 0x00); // Wake up
    I2C_Write(MPU6050_ADDR, 0x1B, 0x00); // Gyro config
    I2C_Write(MPU6050_ADDR, 0x1C, 0x00); // Accel config
}

void MPU6050_ReadAccel(int16_t* ax, int16_t* ay, int16_t* az) {
    *ax = (I2C_Read(MPU6050_ADDR, 0x3B) << 8) | I2C_Read(MPU6050_ADDR, 0x3C);
    *ay = (I2C_Read(MPU6050_ADDR, 0x3D) << 8) | I2C_Read(MPU6050_ADDR, 0x3E);
    *az = (I2C_Read(MPU6050_ADDR, 0x3F) << 8) | I2C_Read(MPU6050_ADDR, 0x40);
}

void MPU6050_ReadGyro(int16_t* gx, int16_t* gy, int16_t* gz) {
    *gx = (I2C_Read(MPU6050_ADDR, 0x43) << 8) | I2C_Read(MPU6050_ADDR, 0x44);
    *gy = (I2C_Read(MPU6050_ADDR, 0x45) << 8) | I2C_Read(MPU6050_ADDR, 0x46);
    *gz = (I2C_Read(MPU6050_ADDR, 0x47) << 8) | I2C_Read(MPU6050_ADDR, 0x48);
}
