// src/Services/Path_Planning/Path_Planning.c

#include "Path_Planning.h"
#include "../Odometry/Odometry.h"

const float SQUARE_SIZE = 49.5;
uint8_t current_waypoint = 0;
float waypoints[9][2] = { // Zigzag in 4x4 grid, example path: row1 right, row2 left, etc.
    {0, 0}, {4*SQUARE_SIZE, 0}, {4*SQUARE_SIZE, SQUARE_SIZE}, {0, SQUARE_SIZE},
    {0, 2*SQUARE_SIZE}, {4*SQUARE_SIZE, 2*SQUARE_SIZE}, {4*SQUARE_SIZE, 3*SQUARE_SIZE}, {0, 3*SQUARE_SIZE},
    {0, 4*SQUARE_SIZE} // End
};

void Path_Planning_Init(void) {}

void Path_Planning_Update(void) {
    float x = Odometry_GetX();
    float y = Odometry_GetY();
    float dist = sqrt(pow(waypoints[current_waypoint][0] - x, 2) + pow(waypoints[current_waypoint][1] - y, 2));
    if (dist < 5.0) { // Threshold
        current_waypoint++;
        if (current_waypoint >= 9) current_waypoint = 0; // Loop or stop
    }
}

float Path_Planning_GetTargetX(void) { return waypoints[current_waypoint][0]; }
float Path_Planning_GetTargetY(void) { return waypoints[current_waypoint][1]; }
uint8_t Path_Planning_CheckLap(void) { return (current_waypoint == 0); }
