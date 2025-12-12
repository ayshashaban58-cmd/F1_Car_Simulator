/*============================================================================
 * Odometry Service - Position Calculation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * IMU + Single Encoder fusion
 *===========================================================================*/

#ifndef ODOMETRY_H
#define ODOMETRY_H

void Odometry_Init(void);
void Odometry_Update(void);
float Odometry_GetX(void);
float Odometry_GetY(void);
float Odometry_GetTheta(void);

#endif
