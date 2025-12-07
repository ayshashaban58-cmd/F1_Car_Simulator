/*
 * IR_Markers.c - IR Sensor Array Implementation
 * Detects black line markers on white background
 */

#include "IR_Markers.h"
#include "../../MCAL/Dio/Dio.h"

#define IR_SENSOR_PORT PORTA_REG
#define IR_SENSOR_PIN_0 0
#define IR_SENSOR_PIN_1 1
#define IR_SENSOR_PIN_2 2
#define IR_SENSOR_PIN_3 3

static IR_Markers_Data_t ir_data = {0};
static uint8_t marker_count = 0;
static uint8_t last_detection = 0;

void IR_Markers_Init(void) {
    // Set IR sensor pins as input
    Dio_SetPinDirection(IR_SENSOR_PORT, IR_SENSOR_PIN_0, DIO_INPUT);
    Dio_SetPinDirection(IR_SENSOR_PORT, IR_SENSOR_PIN_1, DIO_INPUT);
    Dio_SetPinDirection(IR_SENSOR_PORT, IR_SENSOR_PIN_2, DIO_INPUT);
    Dio_SetPinDirection(IR_SENSOR_PORT, IR_SENSOR_PIN_3, DIO_INPUT);
    
    // Enable pull-up resistors
    Dio_WritePin(IR_SENSOR_PORT, IR_SENSOR_PIN_0, DIO_HIGH);
    Dio_WritePin(IR_SENSOR_PORT, IR_SENSOR_PIN_1, DIO_HIGH);
    Dio_WritePin(IR_SENSOR_PORT, IR_SENSOR_PIN_2, DIO_HIGH);
    Dio_WritePin(IR_SENSOR_PORT, IR_SENSOR_PIN_3, DIO_HIGH);
    
    ir_data.detected = MARKER_NOT_DETECTED;
    ir_data.marker_id = 0;
    marker_count = 0;
}

void IR_Markers_Scan(void) {
    // Read all 4 IR sensors (inverted: 0=white, 1=black)
    ir_data.sensor[0] = !Dio_ReadPin(IR_SENSOR_PORT, IR_SENSOR_PIN_0);
    ir_data.sensor[1] = !Dio_ReadPin(IR_SENSOR_PORT, IR_SENSOR_PIN_1);
    ir_data.sensor[2] = !Dio_ReadPin(IR_SENSOR_PORT, IR_SENSOR_PIN_2);
    ir_data.sensor[3] = !Dio_ReadPin(IR_SENSOR_PORT, IR_SENSOR_PIN_3);
    
    // Check if any sensor detects black line
    uint8_t current_detection = 0;
    for(uint8_t i = 0; i < 4; i++) {
        if(ir_data.sensor[i] == 1) {
            current_detection = 1;
            break;
        }
    }
    
    // Detect rising edge (new marker detection)
    if(current_detection && !last_detection) {
        marker_count++;
        ir_data.marker_id = marker_count;
        ir_data.detected = MARKER_DETECTED;
        
        // Limit marker count to 4
        if(marker_count > 4) marker_count = 4;
    }
    
    last_detection = current_detection;
}

IR_Markers_Data_t* IR_Markers_GetData(void) {
    return &ir_data;
}

uint8_t IR_Markers_IsDetected(void) {
    return ir_data.detected;
}

void IR_Markers_ClearDetection(void) {
    ir_data.detected = MARKER_NOT_DETECTED;
}
