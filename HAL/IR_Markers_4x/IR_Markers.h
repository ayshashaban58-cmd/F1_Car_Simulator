#ifndef IR_MARKERS_H
#define IR_MARKERS_H

void IR_Markers_Init(void);
void IR_Markers_Scan(void);
uint8_t IR_Markers_GetPattern(void); // Returns marker ID 1-4 or 0

#endif
