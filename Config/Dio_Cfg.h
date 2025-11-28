/*============================================================================
 * DIO Configuration - Pin Assignments
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * All pins for Motors, IR Markers, Encoders, I2C
 *===========================================================================*/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Std_Types.h"

// Motor L298N Pins
#define MOTOR_DIR_IN1    0   // PA0 - Direction Motor IN1
#define MOTOR_DIR_IN2    1   // PA1 - Direction Motor IN2  
#define MOTOR_DRV_IN1    2   // PA2 - Drive Motor IN1
#define MOTOR_DRV_IN2    3   // PA3 - Drive Motor IN2

// 4 IR Markers Sensors
#define IR_S1_PIN        0   // PB0 - IR Sensor 1 (Top-Left)
#define IR_S2_PIN        1   // PB1 - IR Sensor 2 (Top-Right)
#define IR_S3_PIN        2   // PB2 - IR Sensor 3 (Bottom-Left)
#define IR_S4_PIN        3   // PB3 - IR Sensor 4 (Bottom-Right)

// Encoder Pins
#define ENCODER1_A       4   // PE0 - Encoder 1 Channel A
#define ENCODER1_B       5   // PE1 - Encoder 1 Channel B


// I2C Pins for MPU6050
#define I2C_SCL_PIN      0   // PC0
#define I2C_SDA_PIN      1   // PC1

#endif
