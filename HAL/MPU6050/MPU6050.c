#include "MPU6050.h"

void MPU6050_Init(void) {
    // Wake up MPU6050
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);
    // Set gyro range to ±250°/s
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_GYRO_CONFIG, 0x00);
    // Set accel range to ±2g
    I2C_WriteRegister(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 0x00);
}

void MPU6050_ReadRawData(MPU6050_DataType* data) {
    uint8_t buffer[14];
    I2C_ReadMultiple(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, buffer, 14);
    
    data->accelX = (int16_t)((buffer[0] << 8) | buffer[1]);
    data->accelY = (int16_t)((buffer[2] << 8) | buffer[3]);
    data->accelZ = (int16_t)((buffer[4] << 8) | buffer[5]);
    data->gyroX = (int16_t)((buffer[8] << 8) | buffer[9]);
    data->gyroY = (int16_t)((buffer[10] << 8) | buffer[11]);
    data->gyroZ = (int16_t)((buffer[12] << 8) | buffer[13]);
}

void MPU6050_UpdateAngle(MPU6050_DataType* data, float dt) {
    // Convert gyro Z to degrees per second (131 LSB/°/s for ±250°/s range)
    float gyroZ_dps = data->gyroZ / 131.0f;
    data->angleZ += gyroZ_dps * dt;
    
    // Keep angle in [-180, 180] range
    while(data->angleZ > 180.0f) data->angleZ -= 360.0f;
    while(data->angleZ < -180.0f) data->angleZ += 360.0f;
}

void MPU6050_ResetAngle(MPU6050_DataType* data) {
    data->angleZ = 0.0f;
}
