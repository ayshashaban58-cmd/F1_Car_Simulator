/*============================================================================
 * DIO Configuration - Pin Assignments
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 1 Encoder only + 4 IR Markers + Motors + I2C
 *===========================================================================*/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Std_Types.h"

// Motor L298N Pins (PA0-PA3)
#define MOTOR_DIR_IN1    0   // PA0 - Steering Direction IN1
#define MOTOR_DIR_IN2    1   // PA1 - Steering Direction IN2
#define MOTOR_DRV_IN1    2   // PA2 - Drive Direction IN1  
#define MOTOR_DRV_IN2    3   // PA3 - Drive Direction IN2

// 4 IR Markers Sensors (PB0-PB3)
#define IR_S1_PIN        0   // PB0 - Top-Left IR
#define IR_S2_PIN        1   // PB1 - Top-Right IR
#define IR_S3_PIN        2   // PB2 - Bottom-Left IR
#define IR_S4_PIN        3   // PB3 - Bottom-Right IR

// 1 Encoder Only - Rear Wheels (PE0-PE1)
#define ENCODER_A        0   // PE0 - Channel A
#define ENCODER_B        1   // PE1 - Channel B

// I2C Pins for MPU6050 (PC0-PC1)
#define I2C_SCL_PIN      0   // PC0 - SCL
#define I2C_SDA_PIN      1   // PC1 - SDA

// Status LED
#define LED_PIN          4   // PD4 - Status LED

#endif
