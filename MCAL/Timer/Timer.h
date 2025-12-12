#ifndef TIMER_H
#define TIMER_H

void Timer_Init(void);
void Timer_SetPWM(uint8_t channel, uint16_t duty); // channel 0 for Motor (Timer0), 1 for Servo (Timer1)
uint32_t Timer_GetTick(void);

#endif
