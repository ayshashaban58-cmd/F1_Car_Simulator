/*
 * Path_Planning.h - Zigzag Pattern Navigation
 * Moves 8 cells forward, turns 90°, moves 1 cell, turns 90°, repeat
 * Creates zigzag pattern across 8x8 grid
 */

#ifndef PATH_PLANNING_H_
#define PATH_PLANNING_H_

#include <stdint.h>

// Navigation states
typedef enum {
    PATH_STATE_FORWARD,     // Moving forward
    PATH_STATE_TURN_LEFT,   // Turning left 90°
    PATH_STATE_TURN_RIGHT,  // Turning right 90°
    PATH_STATE_COMPLETED    // Pattern completed
} Path_State_t;

// Path planning data
typedef struct {
    Path_State_t state;
    uint8_t cells_traveled;
    uint8_t zigzag_count;
    float target_angle;
    uint8_t turn_direction;  // 0=left, 1=right
} Path_Planning_Data_t;

// Function prototypes
void Path_Planning_Init(void);
void Path_Planning_Update(void);
Path_Planning_Data_t* Path_Planning_GetData(void);
void Path_Planning_Reset(void);

#endif /* PATH_PLANNING_H_ */
