/*============================================================================
 * F1 Car State Machine
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * IDLE → READY → RACING → FINISHED
 *===========================================================================*/

#ifndef F1_CAR_H_
#define F1_CAR_H_

#include "../Config/Std_Types.h"

typedef enum {
    F1_STATE_IDLE = 0,
    F1_STATE_READY,
    F1_STATE_RACING,
    F1_STATE_FINISHED,
    F1_STATE_ERROR
} F1_State_t;

typedef struct {
    F1_State_t CurrentState;
    uint8_t CurrentLap;
    uint32_t LapStartTime;
    float32_t BestLapTime;
    boolean RaceActive;
} F1_Car_t;

extern F1_Car_t F1Car;

Std_ReturnType F1_Car_Init(void);
Std_ReturnType F1_Car_Update(void);
void F1_Car_Start(void);
void F1_Car_Stop(void);
void F1_Car_Reset(void);

#endif
