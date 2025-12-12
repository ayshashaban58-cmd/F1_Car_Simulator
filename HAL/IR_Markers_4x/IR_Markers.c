// src/HAL/IR_Markers_4x/IR_Markers.c

#include "IR_Markers.h"
#include "../../MCAL/Dio/Dio.h"

// Assume 4 IR sensors on PC0-PC3

void IR_Markers_Init(void) {
    // Inputs
}

void IR_Markers_Scan(void) {
    // Read pins
}

uint8_t IR_Markers_GetPattern(void) {
    uint8_t pattern = 0;
    pattern |= Dio_ReadPin(16) << 0; // PC0
    pattern |= Dio_ReadPin(17) << 1;
    pattern |= Dio_ReadPin(18) << 2;
    pattern |= Dio_ReadPin(19) << 3;
    if (pattern == 0x0F) return 1; // Example marker 1 when all high (black line)
    if (pattern == 0x07) return 2;
    if (pattern == 0x03) return 3;
    if (pattern == 0x01) return 4;
    return 0;
}
