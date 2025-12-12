// src/Services/Marker_Correction/Marker_Correction.c

#include "Marker_Correction.h"
#include "../../HAL/IR_Markers_4x/IR_Markers.h"
#include "../Odometry/Odometry.h"
#include "../PID_Controller/PID.h"

float known_positions[4][2] = { // Random positions for 4 markers
    {2*49.5, 0.5*49.5}, {3.5*49.5, 1.5*49.5}, {1*49.5, 2.5*49.5}, {2.5*49.5, 3.5*49.5}
};

void Marker_Correction_Init(void) {}

void Marker_Correction_Correct(void) {
    uint8_t marker_id = IR_Markers_GetPattern();
    if (marker_id > 0 && marker_id <= 4) {
        // Reset position to known
        // For simplicity, set x,y to known
        // Odometry_SetPosition(known_positions[marker_id-1][0], known_positions[marker_id-1][1]); // Add setter if needed
        PID_Reset();
    }
}
