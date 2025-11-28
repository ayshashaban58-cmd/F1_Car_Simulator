/*============================================================================
 * Motor PID Configuration
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Tuned values for smooth F1 racing
 *===========================================================================*/

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

// Speed PID Constants (Drive Motor)
#define SPEED_KP        2.5f
#define SPEED_KI        0.1f
#define SPEED_KD        0.3f
#define SPEED_MAX       1000   // PWM 0-1000 (0.1% resolution)

// Steering PID Constants (Direction Motor)
#define STEER_KP        3.0f
#define STEER_KI        0.05f
#define STEER_KD        0.4f

// Target racing speed
#define TARGET_RPM      1200

#endif
