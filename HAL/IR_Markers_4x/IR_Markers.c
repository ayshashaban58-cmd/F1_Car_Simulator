#include "IR_Markers.h"
#include "../../MCAL/Dio/Dio.h"

void IR_Markers_Init(void) {
    // Inputs already in Dio_Init
}

void IR_Markers_Scan(void) {
    // Scan if needed
}

uint8_t IR_Markers_GetPattern(void) {
    uint8_t pattern = 0;
    pattern |= Dio_ReadPin('C', PC2) << 0;
    pattern |= Dio_ReadPin('C', PC3) << 1;
    pattern |= Dio_ReadPin('C', PC4) << 2;
    pattern |= Dio_ReadPin('C', PC5) << 3;
    // Example patterns for 4 markers (adjust based on your IR logic for black line)
    if (pattern == 0b1111) return 1;
    if (pattern == 0b0111) return 2;
    if (pattern == 0b0011) return 3;
    if (pattern == 0b0001) return 4;
    return 0;
}
