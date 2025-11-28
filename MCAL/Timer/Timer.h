/*============================================================================
 * Timer Driver - PWM + System Tick
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 20kHz PWM for motors + 100Hz control loop
 *===========================================================================*/

#ifndef TIMER_H_
#define TIMER_H_

#include "../Config/Std_Types.h"

typedef uint16_t PWM_DutyType;  // 0-1000

Std_ReturnType Timer_Init(void);
Std_ReturnType Timer_SetPWM(uint8_t Channel, PWM_DutyType Duty);
uint32_t Timer_GetTick(void);  // System time in ms

#endif
