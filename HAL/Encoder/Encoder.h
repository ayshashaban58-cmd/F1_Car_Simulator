/*============================================================================
 * Single Encoder Driver - Rear Wheels Only
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Measures speed and distance
 *===========================================================================*/

#ifndef ENCODER_H_
#define ENCODER_H_

#include "../Config/Std_Types.h"

typedef struct {
    int32_t Ticks;
    float32_t RPM;
    float32_t Distance;  // Grid units
    uint32_t Timestamp;
} Encoder_Data_t;

extern Encoder_Data_t RearEncoder;

Std_ReturnType Encoder_Init(void);
Std_ReturnType Encoder_Update(void);
float32_t Encoder_GetRPM(void);
float32_t Encoder_GetDistance(void);

#endif
