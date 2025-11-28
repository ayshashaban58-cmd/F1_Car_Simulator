/*============================================================================
 * Single Encoder Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Rear drive wheels only - PE0, PE1
 *===========================================================================*/

#include "Encoder.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../Config/Dio_Cfg.h"

Encoder_Data_t RearEncoder = {0};
static int32_t LastTicks = 0;
static uint32_t LastTime = 0;

__attribute__((__interrupt__))
static void Encoder_ISR(void) {
    static uint8_t LastA = 0;
    uint8_t A = Dio_ReadChannel(ENCODER_A, NULL);
    uint8_t B = Dio_ReadChannel(ENCODER_B, NULL);
    
    if(A != LastA) {
        if(A == B) RearEncoder.Ticks++;
        else RearEncoder.Ticks--;
    }
    LastA = A;
}

Std_ReturnType Encoder_Init(void) {
    LastTime = Timer_GetTick();
    // Enable encoder interrupts (handled by ISR)
    return E_OK;
}

Std_ReturnType Encoder_Update(void) {
    uint32_t CurrentTime = Timer_GetTick();
    float32_t dt = (CurrentTime - LastTime) / 1000.0f;
    
    if(dt > 0.0f) {
        float32_t DeltaTicks = RearEncoder.Ticks - LastTicks;
        RearEncoder.RPM = (DeltaTicks / dt) * 60.0f / 360.0f;  // 360 PPR
        RearEncoder.Distance += DeltaTicks / 1250.0f;          // 1250 ticks/grid
    }
    
    LastTicks = RearEncoder.Ticks;
    LastTime = CurrentTime;
    RearEncoder.Timestamp = CurrentTime;
    
    return E_OK;
}

float32_t Encoder_GetRPM(void) { return RearEncoder.RPM; }
float32_t Encoder_GetDistance(void) { return RearEncoder.Distance; }
