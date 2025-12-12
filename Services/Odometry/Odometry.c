// src/Services/Odometry/Odometry.c

#include "Odometry.h"
#include "../../HAL/MPU6050/MPU6050.h"
#include "../../MCAL/Timer/Timer.h"

float x = 0, y = 0, theta = 0;
int16_t ax, ay, az, gx, gy, gz;
uint32_t last_tick = 0;
const float SQUARE_SIZE = 49.5; // cm
const float ASSUMED_SPEED = 10.0; // cm/s, assume constant speed

void Odometry_Init(void) {
    MPU6050_Init();
}

void Odometry_Update(void) {
    uint32_t dt = Timer_GetTick() - last_tick;
    last_tick = Timer_GetTick();
    float delta_t = dt / 100.0; // 100Hz

    MPU6050_ReadAccel(&ax, &ay, &az);
    MPU6050_ReadGyro(&gx, &gy, &gz);

    // Simple integration, error-prone but for demo
    theta += (gz / 16384.0) * delta_t; // Sensitivity 16384 LSB/deg/s

    float vx = ASSUMED_SPEED * cos(theta);
    float vy = ASSUMED_SPEED * sin(theta);

    x += vx * delta_t;
    y += vy * delta_t;
}
float Odometry_GetX(void) { return x; }
float Odometry_GetY(void) { return y; }
float Odometry_GetTheta(void) { return theta; }
