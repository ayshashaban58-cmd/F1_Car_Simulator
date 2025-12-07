/*
 * Timer.h - Timer Driver for PWM and System Tick
 * Timer0: 100Hz system tick (CTC mode)
 * Timer1: PWM for motor and servo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

// PWM channels
#define PWM_MOTOR   0  // OC1A (PD5)
#define PWM_SERVO   1  // OC1B (PD4)

// Function prototypes
void Timer_Init(void);
void Timer_SetPWM(uint8_t channel, uint16_t duty);
uint32_t Timer_GetTicks(void);

#endif /* TIMER_H_ */
