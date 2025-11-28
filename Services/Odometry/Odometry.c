/*============================================================================
 * Odometry Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * X = X + (Distance * cos(Theta))
 * Y = Y + (Distance * sin(Theta))
 *===========================================================================*/

#include "Odometry.h"
#include "../../HAL/Encoder/Encoder.h"

Position_t CarPosition = {0};
static float32_t LastDistance = 0;

Std_ReturnType Odometry_Init(float32_t StartX, float32_t StartY) {
    CarPosition.X = StartX;
    CarPosition.Y = StartY;
    CarPosition.Theta = 0.0f;
    LastDistance = 0.0f;
    return E_OK;
}

Std_ReturnType Odometry_Update(void) {
    float32_t CurrentDistance = Encoder_GetDistance();
    float32_t DeltaDistance = CurrentDistance - LastDistance;
    
    // Update position
    CarPosition.X += DeltaDistance * cosf(CarPosition.Theta);
    CarPosition.Y += DeltaDistance * sinf(CarPosition.Theta);
    
    // Constrain to 8x8 grid
    if(CarPosition.X < 0.0f) CarPosition.X = 0.0f;
    if(CarPosition.X > 8.0f) CarPosition.X = 8.0f;
    if(CarPosition.Y < 0.0f) CarPosition.Y = 0.0f;
    if(CarPosition.Y > 8.0f) CarPosition.Y = 8.0f;
    
    // Update velocity
    CarPosition.Vx = DeltaDistance / 0.01f * cosf(CarPosition.Theta);
    CarPosition.Vy = DeltaDistance / 0.01f * sinf(CarPosition.Theta);
    
    LastDistance = CurrentDistance;
    CarPosition.Timestamp = Timer_GetTick();
    
    return E_OK;
}
