#include "IR_Markers.h"

void IR_Markers_Init(void) {
    Dio_SetPinDirection(IR_PORT, IR1_PIN, DIO_INPUT);
    Dio_SetPinDirection(IR_PORT, IR2_PIN, DIO_INPUT);
    Dio_SetPinDirection(IR_PORT, IR3_PIN, DIO_INPUT);
    Dio_SetPinDirection(IR_PORT, IR4_PIN, DIO_INPUT);
}

void IR_Markers_Scan(IR_Markers_DataType* data) {
    // Read sensors (0 = black line detected, 1 = white surface)
    data->sensor1 = Dio_ReadPin(IR_PORT, IR1_PIN);
    data->sensor2 = Dio_ReadPin(IR_PORT, IR2_PIN);
    data->sensor3 = Dio_ReadPin(IR_PORT, IR3_PIN);
    data->sensor4 = Dio_ReadPin(IR_PORT, IR4_PIN);
    
    // Check if any sensor detects black line (marker)
    if(data->sensor1 == DIO_LOW || data->sensor2 == DIO_LOW || 
       data->sensor3 == DIO_LOW || data->sensor4 == DIO_LOW) {
        if(!data->markerDetected) {
            data->markerDetected = 1;
            data->markerCount++;
        }
    } else {
        data->markerDetected = 0;
    }
}

uint8_t IR_Markers_IsOnLine(IR_Markers_DataType* data) {
    return data->markerDetected;
}
