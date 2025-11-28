/*============================================================================
 * UART Telemetry Protocol
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * [F1][X:4.25][Y:3.87][T:45.2][S:1250][L:2][M:3]\r\n
 *===========================================================================*/

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "../Config/Std_Types.h"

Std_ReturnType Telemetry_Init(void);
Std_ReturnType Telemetry_Send(void);
Std_ReturnType Telemetry_ParseCommand(void);

#endif
