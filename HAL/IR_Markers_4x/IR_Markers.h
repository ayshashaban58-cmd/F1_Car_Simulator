/*
 * IR_Markers.h - IR Sensor Array for Marker Detection
 * 4 IR sensors on PA0-PA3 for black line detection
 * Returns marker ID when detected
 */

#ifndef IR_MARKERS_H_
#define IR_MARKERS_H_

#include <stdint.h>

// Marker detection status
#define MARKER_NOT_DETECTED 0
#define MARKER_DETECTED     1

// IR sensor readings (0 = white, 1 = black)
typedef struct {
    uint8_t sensor[4];  // 4 IR sensors
    uint8_t detected;   // Marker detected flag
    uint8_t marker_id;  // Current marker ID (1-4)
} IR_Markers_Data_t;

// Function prototypes
void IR_Markers_Init(void);
void IR_Markers_Scan(void);
IR_Markers_Data_t* IR_Markers_GetData(void);
uint8_t IR_Markers_IsDetected(void);
void IR_Markers_ClearDetection(void);

#endif /* IR_MARKERS_H_ */
