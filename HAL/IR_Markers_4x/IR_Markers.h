/*============================================================================
 * 4 IR Markers Detection
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Pattern matching for 4 strategic markers
 *===========================================================================*/

#ifndef IR_MARKERS_H_
#define IR_MARKERS_H_

#include "../Config/Std_Types.h"
#include "../../Config/Markers_Cfg.h"

typedef enum {
    NO_MARKER = 0,
    MARKER_1, MARKER_2, 
    MARKER_3, MARKER_4
} Detected_Marker_t;

typedef struct {
    uint8_t S1, S2, S3, S4;
    Detected_Marker_t ID;
    float32_t Confidence;
    uint32_t Timestamp;
} IR_Marker_t;

Std_ReturnType IR_Markers_Init(void);
Detected_Marker_t IR_Markers_Scan(IR_Marker_t* Marker);
boolean IR_Marker_Detected(void);

#endif
