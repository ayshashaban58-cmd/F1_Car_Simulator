/*
 * MPU6050.c - IMU Sensor Driver Implementation
 */

#include "MPU6050.h"
#include "../../MCAL/I2C/I2C.h"

// MPU6050 I2C address
#define MPU6050_ADDR 0x68

// MPU6050 registers
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43

// Gyro sensitivity: 250°/s = 131 LSB/(°/s)
#define GYRO_SENSITIVITY 131.0f
#define DT 0.01f  // 100Hz = 10ms = 0.01s

static MPU6050_Data_t mpu_data = {0};
static int16_t gyro_z_offset = 0;

void MPU6050_Init(void) {
    // Wake up MPU6050
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);
    
    // Set gyro range to ±250°/s
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_GYRO_CONFIG, 0x00);
    
    // Set accel range to ±2g
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 0x00);
    
    // Calibrate gyro (read offset)
    int32_t gyro_sum = 0;
    for(uint8_t i = 0; i < 100; i++) {
        uint8_t buffer[2];
        I2C_ReadMultipleRegisters(MPU6050_ADDR, MPU6050_GYRO_XOUT_H + 4, buffer, 2);
        int16_t gyro_raw = (buffer[0] << 8) | buffer[1];
        gyro_sum += gyro_raw;
    }
    gyro_z_offset = gyro_sum / 100;
    
    // Reset angle
    mpu_data.angle_z = 0;
}

void MPU6050_Read(void) {
    uint8_t buffer[14];
    
    // Read all sensor data (accel + temp + gyro)
    if(I2C_ReadMultipleRegisters(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, buffer, 14) == I2C_SUCCESS) {
        // Parse accelerometer data
        mpu_data.accel_x = (buffer[0] << 8) | buffer[1];
        mpu_data.accel_y = (buffer[2] << 8) | buffer[3];
        mpu_data.accel_z = (buffer[4] << 8) | buffer[5];
        
        // Parse gyroscope data
        mpu_data.gyro_x = (buffer[8] << 8) | buffer[9];
        mpu_data.gyro_y = (buffer[10] << 8) | buffer[11];
        mpu_data.gyro_z = (buffer[12] << 8) | buffer[13];
        
        // Remove offset from gyro Z
        mpu_data.gyro_z -= gyro_z_offset;
        
        // Convert to degrees per second
        mpu_data.gyro_z_dps = mpu_data.gyro_z / GYRO_SENSITIVITY;
        
        // Integrate to get angle (simple integration)
        mpu_data.angle_z += mpu_data.gyro_z_dps * DT;
    }
}

MPU6050_Data_t* MPU6050_GetData(void) {
    return &mpu_data;
}

void MPU6050_ResetAngle(void) {
    mpu_data.angle_z = 0;
}
