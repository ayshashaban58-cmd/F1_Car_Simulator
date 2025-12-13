#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include <stdint.h>
#include "../MCAL/UART/UART.h"
#include "../Services/Odometry/Odometry.h"
#include "../HAL/MPU6050/MPU6050.h"
#include "../HAL/IR_Markers_4x/IR_Markers.h"
#include "../Application/F1_Car/F1_Car.h"

// Command definitions
#define CMD_START 'S'
#define CMD_STOP 'P'
#define CMD_RESET 'R'
#define CMD_SPEED 'V'

typedef struct {
    char command;
    uint8_t value;
} Telemetry_CommandType;

// Function Prototypes
void Telemetry_Init(void);
void Telemetry_SendData(Odometry_DataType* odom, MPU6050_DataType* imu, 
                        IR_Markers_DataType* irData, F1_Car_Type* car);
uint8_t Telemetry_ReceiveCommand(Telemetry_CommandType* cmd);
void Telemetry_ProcessCommand(Telemetry_CommandType* cmd, F1_Car_Type* car);

#endif /* TELEMETRY_H_ */
