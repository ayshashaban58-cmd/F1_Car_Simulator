#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// Timer channels for PWM
typedef enum {
    TIMER0_CHANNEL = 0,
    TIMER1_CHANNELA,
    TIMER1_CHANNELB,
    TIMER2_CHANNEL
} Timer_ChannelType;

// Function Prototypes
void Timer0_Init(void);
void Timer1_Init_PWM(void);
void Timer2_Init(void);
void Timer_SetPWM(Timer_ChannelType channel, uint8_t duty);
uint32_t Timer_GetSystemTick(void);
void Timer_DelayMs(uint16_t ms);

#endif /* TIMER_H_ */
