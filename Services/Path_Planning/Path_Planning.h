#ifndef PATH_PLANNING_H_
#define PATH_PLANNING_H_

#include <stdint.h>
#include "../Services/Odometry/Odometry.h"

typedef enum {
    PATH_STRAIGHT = 0,
    PATH_TURN_LEFT,
    PATH_COMPLETED
} Path_StateType;

typedef struct {
    Path_StateType state;
    uint8_t squareTarget; // Number of squares to travel before turning
    float targetAngle; // Target angle for turning
    uint8_t turnCount; // Number of turns completed
} Path_PlanningType;

// Function Prototypes
void Path_Init(Path_PlanningType* path);
void Path_Update(Path_PlanningType* path, Odometry_DataType* odom);
float Path_GetAngleError(Path_PlanningType* path, Odometry_DataType* odom);
uint8_t Path_IsCompleted(Path_PlanningType* path);

#endif /* PATH_PLANNING_H_ */
