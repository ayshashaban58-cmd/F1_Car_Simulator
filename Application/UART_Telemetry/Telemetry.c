#include "Telemetry.h"
#include <stdio.h>
#include <string.h>

void Telemetry_Init(void) {
    UART_Init(9600); // 9600 baud
}

void Telemetry_SendData(Odometry_DataType* odom, MPU6050_DataType* imu, 
                        IR_Markers_DataType* irData, F1_Car_Type* car) {
    char buffer[128];
    
    // Format: {x:%.2f,y:%.2f,theta:%.2f,speed:%.2f,squares:%d,markers:%d,state:%d}\n
    sprintf(buffer, "{\"x\":%.2f,\"y\":%.2f,\"theta\":%.2f,\"speed\":%.2f,\"squares\":%d,\"markers\":%d,\"state\":%d}\n",
            odom->x, odom->y, odom->theta, odom->speed, 
            odom->squaresPassed, irData->markerCount, car->state);
    
    UART_SendString(buffer);
}

uint8_t Telemetry_ReceiveCommand(Telemetry_CommandType* cmd) {
    if(UART_Available()) {
        cmd->command = UART_ReceiveByte();
        
        // If command expects a value, read it
        if(cmd->command == CMD_SPEED) {
            if(UART_Available()) {
                cmd->value = UART_ReceiveByte();
            } else {
                cmd->value = 50; // Default
            }
        } else {
            cmd->value = 0;
        }
        return 1;
    }
    return 0;
}

void Telemetry_ProcessCommand(Telemetry_CommandType* cmd, F1_Car_Type* car) {
    switch(cmd->command) {
        case CMD_START:
            F1_Car_Start(car);
            break;
        case CMD_STOP:
            F1_Car_Stop(car);
            break;
        case CMD_RESET:
            F1_Car_Reset(car);
            break;
        case CMD_SPEED:
            F1_Car_SetSpeed(car, cmd->value);
            break;
        default:
            break;
    }
}
