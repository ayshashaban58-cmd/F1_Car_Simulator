// src/HAL/IR_Markers_4x/IR_Markers.h

#ifndef IR_MARKERS_H
#define IR_MARKERS_H

void IR_Markers_Init(void);
void IR_Markers_Scan(void);
uint8_t IR_Markers_GetPattern(void); // Returns detected marker ID or 0

#endif
