// src/Services/Path_Planning/Path_Planning.h

#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

void Path_Planning_Init(void);
void Path_Planning_Update(void);
float Path_Planning_GetTargetX(void);
float Path_Planning_GetTargetY(void);
uint8_t Path_Planning_CheckLap(void);

#endif
