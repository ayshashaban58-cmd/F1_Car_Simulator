/*============================================================================
 * Marker Correction Service
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Reset odometry errors on marker detection
 *===========================================================================*/

#ifndef MARKER_CORRECTION_H_
#define MARKER_CORRECTION_H_

#include "../Config/Std_Types.h"
#include "../../Config/Markers_Cfg.h"
#include "../../HAL/IR_Markers_4x/IR_Markers.h"
#include "../Odometry/Odometry.h"

Std_ReturnType Marker_Correction_Init(void);
Std_ReturnType Marker_CorrectPosition(Detected_Marker_t MarkerID);

#endif
