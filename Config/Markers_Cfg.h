/*============================================================================
 * 4 IR Markers Configuration
 * author : Aysha Shaban Galal  
 * Date: Nov 2025
 * Exact positions in 8x8 grid (12.5cm per cell)
 *===========================================================================*/

#ifndef MARKERS_CFG_H_
#define MARKERS_CFG_H_

#include "Std_Types.h"

typedef struct {
    float32_t X, Y;           // Grid coordinates (0.0-8.0)
    uint8_t Pattern[4];       // S1,S2,S3,S4 signature
} Marker_t;

const Marker_t Known_Markers[4] = {
    {0.0f, 0.0f, {1, 0, 0, 1}},  // Marker 1 - START/FINISH
    {2.0f, 4.0f, {1, 1, 0, 0}},  // Marker 2 - Mid Straight
    {4.0f, 3.0f, {0, 1, 1, 0}},  // Marker 3 - Turn 1
    {3.0f, 2.0f, {0, 0, 1, 1}}   // Marker 4 - Turn 2
};

#define NUM_MARKERS     4

#endif
