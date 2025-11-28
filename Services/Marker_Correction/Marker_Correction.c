/*============================================================================
 * Marker Correction Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Snap position to exact marker coordinates
 *===========================================================================*/

#include "Marker_Correction.h"
#include "../../HAL/Encoder/Encoder.h"
#include "../Odometry/Odometry.h"
#include "../../Config/Markers_Cfg.h"

Std_ReturnType Marker_Correction_Init(void) {
    return E_OK;
}

Std_ReturnType Marker_CorrectPosition(Detected_Marker_t MarkerID) {
    if(MarkerID == NO_MARKER || MarkerID > NUM_MARKERS) {
        return E_NOT_OK;
    }
    
    uint8_t index = MarkerID - 1;
    
    // Snap to exact marker position
    CarPosition.X = Known_Markers[index].X;
    CarPosition.Y = Known_Markers[index].Y;
    CarPosition.Theta = 0.0f;  // Assume facing forward
    
    // Reset encoder offset
    RearEncoder.Distance = 0.0f;
    
    // Reset PID integrals
    PID_Reset(&SpeedPID);
    PID_Reset(&SteeringPID);
    
    return E_OK;
}
