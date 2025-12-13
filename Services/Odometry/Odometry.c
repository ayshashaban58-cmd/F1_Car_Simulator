#include "Odometry.h"
#include <math.h>

#define PI 3.14159265359f

void Odometry_Init(Odometry_DataType* odom) {
    odom->x = 0.0f;
    odom->y = 0.0f;
    odom->theta = 0.0f;
    odom->speed = 30.0f; // Default speed in cm/s
    odom->squaresPassed = 0;
}

void Odometry_Update(Odometry_DataType* odom, MPU6050_DataType* imu, float dt) {
    // Update heading from IMU
    odom->theta = imu->angleZ;
    
    // Calculate displacement based on speed and heading
    float thetaRad = odom->theta * PI / 180.0f;
    float dx = odom->speed * cosf(thetaRad) * dt;
    float dy = odom->speed * sinf(thetaRad) * dt;
    
    odom->x += dx;
    odom->y += dy;
    
    // Calculate squares passed (based on total distance)
    float totalDistance = sqrtf(odom->x * odom->x + odom->y * odom->y);
    odom->squaresPassed = (uint8_t)(totalDistance / GRID_SIZE);
}

void Odometry_Reset(Odometry_DataType* odom) {
    odom->x = 0.0f;
    odom->y = 0.0f;
    odom->theta = 0.0f;
    odom->squaresPassed = 0;
}

void Odometry_ResetErrors(Odometry_DataType* odom, float correctedX, float correctedY, float correctedTheta) {
    odom->x = correctedX;
    odom->y = correctedY;
    odom->theta = correctedTheta;
}
