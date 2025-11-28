/*============================================================================
 * 4 IR Markers Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 2x2 sensor array with pattern recognition
 *===========================================================================*/

#include "IR_Markers.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../Config/Dio_Cfg.h"
#include "../../Config/Markers_Cfg.h"

static Detected_Marker_t LastMarker = NO_MARKER;

Std_ReturnType IR_Markers_Init(void) {
    return E_OK;  // Pins configured in Dio_Init
}

Detected_Marker_t IR_Markers_Scan(IR_Marker_t* Marker) {
    Dio_LevelType S1, S2, S3, S4;
    
    // Read 4 IR sensors (LOW = marker detected)
    Dio_ReadChannel(IR_S1_PIN, &S1);
    Dio_ReadChannel(IR_S2_PIN, &S2);
    Dio_ReadChannel(IR_S3_PIN, &S3);
    Dio_ReadChannel(IR_S4_PIN, &S4);
    
    // Invert: LOW=1 (detected), HIGH=0
    Marker->S1 = (S1 == STD_LOW) ? 1 : 0;
    Marker->S2 = (S2 == STD_LOW) ? 1 : 0;
    Marker->S3 = (S3 == STD_LOW) ? 1 : 0;
    Marker->S4 = (S4 == STD_LOW) ? 1 : 0;
    
    uint8_t Active = Marker->S1 + Marker->S2 + Marker->S3 + Marker->S4;
    Marker->Confidence = (float32_t)Active / 4.0f;
    
    if(Active < 3) {
        Marker->ID = NO_MARKER;
        return NO_MARKER;
    }
    
    // Pattern matching
    for(uint8_t i = 0; i < NUM_MARKERS; i++) {
        if(Marker->S1 == Known_Markers[i].Pattern[0] &&
           Marker->S2 == Known_Markers[i].Pattern[1] &&
           Marker->S3 == Known_Markers[i].Pattern[2] &&
           Marker->S4 == Known_Markers[i].Pattern[3]) {
            Marker->ID = (Detected_Marker_t)(i + 1);
            LastMarker = Marker->ID;
            Marker->Timestamp = Timer_GetTick();
            return Marker->ID;
        }
    }
    
    return NO_MARKER;
}

boolean IR_Marker_Detected(void) {
    return (LastMarker != NO_MARKER);
}
