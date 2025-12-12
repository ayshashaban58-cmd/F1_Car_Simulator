// src/MCAL/Timer/Timer.h

#ifndef TIMER_H
#define TIMER_H

void Timer_Init(void);
void Timer_SetPWM(uint8_t channel, uint16_t duty);
uint32_t Timer_GetTick(void);

#endif
