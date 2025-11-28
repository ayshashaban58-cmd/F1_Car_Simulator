/*============================================================================
 * DIO Driver - Digital I/O Control
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * Controls motors, IR sensors, encoder, LED
 *===========================================================================*/

#ifndef DIO_H_
#define DIO_H_

#include "../Config/Std_Types.h"
#include "../Config/Dio_Cfg.h"

typedef enum { STD_LOW=0, STD_HIGH=1 } Dio_LevelType;
typedef enum { INPUT=0, OUTPUT=1 } Dio_DirectionType;

Std_ReturnType Dio_Init(void);
Std_ReturnType Dio_WriteChannel(uint8_t Channel, Dio_LevelType Level);
Std_ReturnType Dio_ReadChannel(uint8_t Channel, Dio_LevelType* Level);
Std_ReturnType Dio_ToggleChannel(uint8_t Channel);

#endif
