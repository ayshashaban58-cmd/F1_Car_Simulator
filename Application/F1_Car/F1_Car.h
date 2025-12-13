#ifndef F1_CAR_H_
#define F1_CAR_H_

#include <stdint.h>

typedef enum {
    CAR_IDLE = 0,
    CAR_RUNNING,
    CAR_STOPPED,
    CAR_ERROR
} F1_Car_StateType;

typedef struct {
    F1_Car_StateType state;
    uint8_t motorSpeed;
    uint8_t isRunning;
} F1_Car_Type;

// Function Prototypes
void F1_Car_Init(F1_Car_Type* car);
void F1_Car_Start(F1_Car_Type* car);
void F1_Car_Stop(F1_Car_Type* car);
void F1_Car_Reset(F1_Car_Type* car);
void F1_Car_SetSpeed(F1_Car_Type* car, uint8_t speed);
F1_Car_StateType F1_Car_GetState(F1_Car_Type* car);

#endif /* F1_CAR_H_ */
