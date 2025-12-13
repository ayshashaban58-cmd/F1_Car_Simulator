#include "Path_Planning.h"

void Path_Init(Path_PlanningType* path) {
    path->state = PATH_STRAIGHT;
    path->squareTarget = 4; // Travel 4 squares before turning
    path->targetAngle = 0.0f;
    path->turnCount = 0;
}

void Path_Update(Path_PlanningType* path, Odometry_DataType* odom) {
    switch(path->state) {
        case PATH_STRAIGHT:
            // Check if traveled 4 squares
            if(odom->squaresPassed >= path->squareTarget) {
                // Start turning left (add 90 degrees)
                path->state = PATH_TURN_LEFT;
                path->targetAngle = odom->theta + 90.0f;
                // Normalize to [-180, 180]
                while(path->targetAngle > 180.0f) path->targetAngle -= 360.0f;
                while(path->targetAngle < -180.0f) path->targetAngle += 360.0f;
            }
            break;
            
        case PATH_TURN_LEFT:
            // Check if turn is complete (within 5 degrees)
            float angleError = path->targetAngle - odom->theta;
            while(angleError > 180.0f) angleError -= 360.0f;
            while(angleError < -180.0f) angleError += 360.0f;
            
            if(angleError < 5.0f && angleError > -5.0f) {
                // Turn complete, reset for next straight section
                path->state = PATH_STRAIGHT;
                path->squareTarget = odom->squaresPassed + 4;
                path->turnCount++;
                
                // Check if completed full zigzag pattern (e.g., 4 turns)
                if(path->turnCount >= 8) {
                    path->state = PATH_COMPLETED;
                }
            }
            break;
            
        case PATH_COMPLETED:
        default:
            break;
    }
}

float Path_GetAngleError(Path_PlanningType* path, Odometry_DataType* odom) {
    float error = 0.0f;
    
    if(path->state == PATH_STRAIGHT) {
        // Maintain current target angle (0 for straight)
        float targetAngle = (path->turnCount % 4) * 90.0f;
        error = targetAngle - odom->theta;
    } else if(path->state == PATH_TURN_LEFT) {
        // Track target angle during turn
        error = path->targetAngle - odom->theta;
    }
    
    // Normalize error to [-180, 180]
    while(error > 180.0f) error -= 360.0f;
    while(error < -180.0f) error += 360.0f;
    
    return error;
}

uint8_t Path_IsCompleted(Path_PlanningType* path) {
    return (path->state == PATH_COMPLETED);
}
