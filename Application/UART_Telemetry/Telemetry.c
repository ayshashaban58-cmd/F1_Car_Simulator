// src/Application/UART_Telemetry/Telemetry.c

#include "Telemetry.h"
#include "../../MCAL/UART/UART.h"
#include "../Odometry/Odometry.h"

// Simple protocol: send string "x:y:theta\n"

void Telemetry_Send(void) {
    char buf[50];
    sprintf(buf, "%.2f:%.2f:%.2f\n", Odometry_GetX(), Odometry_GetY(), Odometry_GetTheta());
    UART_SendString(buf);
}

void Telemetry_ParseCommand(uint8_t cmd) {
    if (cmd == 'S') F1_Car_Start();
    if (cmd == 'T') F1_Car_Stop();
    if (cmd == 'R') F1_Car_Reset();
}
