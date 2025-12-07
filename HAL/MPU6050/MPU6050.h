/*
 * MPU6050.h - IMU Sensor Driver
 * I2C Address: 0x68
 * Used for gyroscope Z-axis to maintain straight line
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>

// MPU6050 data structure
typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    float angle_z;      // Integrated angle from gyro
    float gyro_z_dps;   // Gyro Z in degrees per second
} MPU6050_Data_t;

// Function prototypes
void MPU6050_Init(void);
void MPU6050_Read(void);
MPU6050_Data_t* MPU6050_GetData(void);
void MPU6050_ResetAngle(void);

#endif /* MPU6050_H_ */
