/*============================================================================
 * Timer Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * TC0: PWM Motors, TC2: 100Hz Tick
 *===========================================================================*/

#include "Timer.h"
#include <avr32/io.h>

static volatile uint32_t SystemTick = 0;

__attribute__((__interrupt__))
static void TC2_IRQ(void) {
    SystemTick++;
    avr32_tc2.icr = 1;
}

Std_ReturnType Timer_Init(void) {
    // PWM: 20kHz (50MHz / 1000 / 50us)
    avr32_tc0.rc0 = 1000;
    avr32_tc0.ra0 = 500;  // 50% initial
    avr32_tc0.ier = 1;
    avr32_tc0.ccr0 = 5;   // Enable
    
    // System Tick: 100Hz (10ms)
    avr32_tc2.rc2 = 500000;
    avr32_tc2.ier = 1;
    avr32_tc2.ccr2 = 5;
    
    return E_OK;
}

Std_ReturnType Timer_SetPWM(uint8_t Channel, PWM_DutyType Duty) {
    if(Duty > 1000) Duty = 1000;
    if(Channel == 0) avr32_tc0.ra0 = Duty;  // Steering
    else avr32_tc0.rb0 = Duty;              // Drive
    return E_OK;
}

uint32_t Timer_GetTick(void) { return SystemTick; }
