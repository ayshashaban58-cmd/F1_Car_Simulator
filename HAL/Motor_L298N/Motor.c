#include "Motor.h"
#include "../../MCAL/Dio/Dio.h"
#include "../../MCAL/Timer/Timer.h"

void Motor_Init(void) {
    Dio_WritePin('B', PB0, 0);
    Dio_WritePin('B', PB1, 0);
}

void Motor_SetSpeed(int16_t speed) {
    uint16_t abs_speed = (speed < 0) ? -speed : speed;
    Timer_SetPWM(0, abs_speed); // Channel 0 for Motor

    if (speed > 0) {
        Dio_WritePin('B', PB0, 1);
        Dio_WritePin('B', PB1, 0);
    } else if (speed < 0) {
        Dio_WritePin('B', PB0, 0);
        Dio_WritePin('B', PB1, 1);
    } else {
        Dio_WritePin('B', PB0, 0);
        Dio_WritePin('B', PB1, 0);
        Timer_SetPWM(0, 0);
    }
}
