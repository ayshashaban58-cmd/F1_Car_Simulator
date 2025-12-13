#include "F1_Car.h"

void F1_Car_Init(F1_Car_Type* car) {
    car->state = CAR_IDLE;
    car->motorSpeed = 50; // Default 50%
    car->isRunning = 0;
}

void F1_Car_Start(F1_Car_Type* car) {
    if(car->state == CAR_IDLE || car->state == CAR_STOPPED) {
        car->state = CAR_RUNNING;
        car->isRunning = 1;
    }
}

void F1_Car_Stop(F1_Car_Type* car) {
    car->state = CAR_STOPPED;
    car->isRunning = 0;
}

void F1_Car_Reset(F1_Car_Type* car) {
    car->state = CAR_IDLE;
    car->motorSpeed = 50;
    car->isRunning = 0;
}

void F1_Car_SetSpeed(F1_Car_Type* car, uint8_t speed) {
    if(speed > 100) speed = 100;
    car->motorSpeed = speed;
}

F1_Car_StateType F1_Car_GetState(F1_Car_Type* car) {
    return car->state;
}
