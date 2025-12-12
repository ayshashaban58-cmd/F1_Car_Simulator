#include "Odometry.h"
#include "../../HAL/MPU6050/MPU6050.h"
#include "../../MCAL/Timer/Timer.h"
#include <math.h> // Add -lm in linker for math

float x = 0, y = 0, theta = 0;
int16_t ax, ay, az, gx, gy, gz;
uint32_t last_tick = 0;
const float ASSUMED_SPEED = 10.0; // cm/s, adjust

void Odometry_Init(void) {
    MPU6050_Init();
}

void Odometry_Update(void) {
    uint32_t current_tick = Timer_GetTick();
    float delta_t = (current_tick - last_tick) / 100.0f; // sec
    last_tick = current_tick;

    MPU6050_ReadAccel(&ax, &ay, &az);
    MPU6050_ReadGyro(&gx, &gy, &gz);

    theta += (gz / 16384.0f) * delta_t; // deg/s sensitivity

    float vx = ASSUMED_SPEED * cos(theta * M_PI / 180.0f);
    float vy = ASSUMED_SPEED * sin(theta * M_PI / 180.0f);

    x += vx * delta_t;
    y += vy * delta_t;
}

float Odometry_GetX(void) { return x; }
float Odometry_GetY(void) { return y; }
float Odometry_GetTheta(void) { return theta; }
