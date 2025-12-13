#include "Marker_Correction.h"

void Marker_Init(Marker_CorrectionType* marker) {
    marker->marker1Passed = 0;
    marker->marker2Passed = 0;
    marker->marker3Passed = 0;
    marker->marker4Passed = 0;
    
    // Define expected squares for each marker (example positions)
    marker->expectedSquares[0] = 5;  // Marker 1 at 5 squares
    marker->expectedSquares[1] = 10; // Marker 2 at 10 squares
    marker->expectedSquares[2] = 15; // Marker 3 at 15 squares
    marker->expectedSquares[3] = 20; // Marker 4 at 20 squares
}

void Marker_CheckAndCorrect(Marker_CorrectionType* marker, IR_Markers_DataType* irData, 
                            Odometry_DataType* odom, MPU6050_DataType* imu) {
    if(IR_Markers_IsOnLine(irData)) {
        // Determine which marker based on squares passed
        if(!marker->marker1Passed && odom->squaresPassed >= marker->expectedSquares[0] - 1 
           && odom->squaresPassed <= marker->expectedSquares[0] + 1) {
            // Marker 1 detected - correct position
            marker->marker1Passed = 1;
            float correctedSquares = marker->expectedSquares[0];
            float correctedX = correctedSquares * GRID_SIZE * 0.707f; // Assuming 45° zigzag
            float correctedY = correctedSquares * GRID_SIZE * 0.707f;
            Odometry_ResetErrors(odom, correctedX, correctedY, odom->theta);
            MPU6050_ResetAngle(imu);
            odom->squaresPassed = marker->expectedSquares[0];
        }
        else if(!marker->marker2Passed && odom->squaresPassed >= marker->expectedSquares[1] - 1 
                && odom->squaresPassed <= marker->expectedSquares[1] + 1) {
            // Marker 2 detected
            marker->marker2Passed = 1;
            float correctedSquares = marker->expectedSquares[1];
            float correctedX = correctedSquares * GRID_SIZE * 0.707f;
            float correctedY = correctedSquares * GRID_SIZE * 0.707f;
            Odometry_ResetErrors(odom, correctedX, correctedY, odom->theta);
            MPU6050_ResetAngle(imu);
            odom->squaresPassed = marker->expectedSquares[1];
        }
        else if(!marker->marker3Passed && odom->squaresPassed >= marker->expectedSquares[2] - 1 
                && odom->squaresPassed <= marker->expectedSquares[2] + 1) {
            // Marker 3 detected
            marker->marker3Passed = 1;
            float correctedSquares = marker->expectedSquares[2];
            float correctedX = correctedSquares * GRID_SIZE * 0.707f;
            float correctedY = correctedSquares * GRID_SIZE * 0.707f;
            Odometry_ResetErrors(odom, correctedX, correctedY, odom->theta);
            MPU6050_ResetAngle(imu);
            odom->squaresPassed = marker->expectedSquares[2];
        }
        else if(!marker->marker4Passed && odom->squaresPassed >= marker->expectedSquares[3] - 1 
                && odom->squaresPassed <= marker->expectedSquares[3] + 1) {
            // Marker 4 detected
            marker->marker4Passed = 1;
            float correctedSquares = marker->expectedSquares[3];
            float correctedX = correctedSquares * GRID_SIZE * 0.707f;
            float correctedY = correctedSquares * GRID_SIZE * 0.707f;
            Odometry_ResetErrors(odom, correctedX, correctedY, odom->theta);
            MPU6050_ResetAngle(imu);
            odom->squaresPassed = marker->expectedSquares[3];
        }
    }
}
