/*============================================================================
 * Odometry Service - Position Calculation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * IMU + Single Encoder fusion
 *===========================================================================*/

#ifndef ODOMETRY_H_
#define ODOMETRY_H_

#include "../Config/Std_Types.h"

typedef struct {
    float32_t X, Y;           // Grid position (0.0-8.0)
    float32_t Theta;          // Heading (radians)
    float32_t Vx, Vy;         // Velocity
    float32_t Omega;          // Angular velocity
    uint32_t Timestamp;
    float32_t Error;
} Position_t;

extern Position_t CarPosition;

Std_ReturnType Odometry_Init(float32_t StartX, float32_t StartY);
Std_ReturnType Odometry_Update(void);

#endif
