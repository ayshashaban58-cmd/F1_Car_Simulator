/*============================================================================
 * Odometry Service - Position Calculation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * IMU + Single Encoder fusion
 *===========================================================================*/

#ifndef ODOMETRY_H_
#define ODOMETRY_H_

#include <stdint.h>
#include "../HAL/MPU6050/MPU6050.h"

#define GRID_SIZE 49.5f // Grid square size in cm

typedef struct {
    float x; // X position in cm
    float y; // Y position in cm
    float theta; // Heading angle in degrees
    float speed; // Current speed in cm/s
    uint8_t squaresPassed; // Number of grid squares passed
} Odometry_DataType;

// Function Prototypes
void Odometry_Init(Odometry_DataType* odom);
void Odometry_Update(Odometry_DataType* odom, MPU6050_DataType* imu, float dt);
void Odometry_Reset(Odometry_DataType* odom);
void Odometry_ResetErrors(Odometry_DataType* odom, float correctedX, float correctedY, float correctedTheta);

#endif /* ODOMETRY_H_ */
