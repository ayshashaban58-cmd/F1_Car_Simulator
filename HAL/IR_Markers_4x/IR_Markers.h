#ifndef IR_MARKERS_H_
#define IR_MARKERS_H_

#include <stdint.h>
#include "../MCAL/Dio/Dio.h"

// IR sensor pins (4 sensors): PC0-PC3
#define IR_PORT DIO_PORTC
#define IR1_PIN DIO_PIN0
#define IR2_PIN DIO_PIN1
#define IR3_PIN DIO_PIN2
#define IR4_PIN DIO_PIN3

typedef struct {
    uint8_t sensor1;
    uint8_t sensor2;
    uint8_t sensor3;
    uint8_t sensor4;
    uint8_t markerDetected;
    uint8_t markerCount;
} IR_Markers_DataType;

// Function Prototypes
void IR_Markers_Init(void);
void IR_Markers_Scan(IR_Markers_DataType* data);
uint8_t IR_Markers_IsOnLine(IR_Markers_DataType* data);

#endif /* IR_MARKERS_H_ */
