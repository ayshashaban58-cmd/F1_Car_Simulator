/*============================================================================
 * Odometry Service - Position Calculation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * IMU + Single Encoder fusion
 *===========================================================================*/

// src/Services/Odometry/Odometry.h

#ifndef ODOMETRY_H
#define ODOMETRY_H

void Odometry_Init(void);
void Odometry_Update(void);
float Odometry_GetX(void);
float Odometry_GetY(void);
float Odometry_GetTheta(void);

#endif
extern Position_t CarPosition;

Std_ReturnType Odometry_Init(float32_t StartX, float32_t StartY);
Std_ReturnType Odometry_Update(void);

#endif
