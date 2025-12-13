#ifndef MARKER_CORRECTION_H_
#define MARKER_CORRECTION_H_

#include <stdint.h>
#include "../HAL/IR_Markers_4x/IR_Markers.h"
#include "../Services/Odometry/Odometry.h"
#include "../HAL/MPU6050/MPU6050.h"

typedef struct {
    uint8_t marker1Passed;
    uint8_t marker2Passed;
    uint8_t marker3Passed;
    uint8_t marker4Passed;
    uint8_t expectedSquares[4]; // Expected squares for each marker
} Marker_CorrectionType;

// Function Prototypes
void Marker_Init(Marker_CorrectionType* marker);
void Marker_CheckAndCorrect(Marker_CorrectionType* marker, IR_Markers_DataType* irData, 
                            Odometry_DataType* odom, MPU6050_DataType* imu);

#endif /* MARKER_CORRECTION_H_ */
