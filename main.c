/*============================================================================
 * F1 Simulator - Main Application
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 100Hz Autonomous Racing Car
 *===========================================================================*/

#include "Config/Std_Types.h"
#include "MCAL/Dio/Dio.h"
#include "MCAL/Timer/Timer.h"
#include "MCAL/UART/UART.h"
#include "HAL/Motor_L298N/Motor.h"
#include "HAL/Encoder/Encoder.h"
#include "HAL/IR_Markers_4x/IR_Markers.h"
#include "Services/Odometry/Odometry.h"
#include "Services/PID_Controller/PID.h"
#include "Services/Marker_Correction/Marker_Correction.h"
#include "Application/F1_Car/F1_Car.h"
#include "Application/UART_Telemetry/Telemetry.h"
#include <avr32/io.h>

F1_Car_t F1Car;
Position_t CarPosition;
PID_Controller_t SpeedPID, SteeringPID;
IR_Marker_t CurrentMarker;

int main(void) {
    // === INITIALIZATION ===
    Dio_Init();
    Timer_Init();
    UART_Init(115200);
    
    Motor_Init();
    Encoder_Init();
    IR_Markers_Init();
    
    Odometry_Init(0.0f, 0.0f);
    PID_Init(&SpeedPID, 2.5f, 0.1f, 0.3f, 0.0f, 1000.0f);
    PID_Init(&SteeringPID, 3.0f, 0.05f, 0.4f, -1000.0f, 1000.0f);
    
    F1_Car_Init();
    Telemetry_Init();
    
    Motor_Stop(MOTOR_STEER);
    Motor_Stop(MOTOR_DRIVE);
    
    // === 100Hz MAIN LOOP ===
    uint32_t lastTick = 0;
    while(1) {
        uint32_t currentTick = Timer_GetTick();
        
        // Execute every 10ms (100Hz)
        if(currentTick - lastTick >= 10) {
            ControlLoop();
            lastTick = currentTick;
        }
        
        Telemetry_ParseCommand();
    }
    
    return 0;
}

void ControlLoop(void) {
    // 1. SENSORS (2ms)
    Encoder_Update();
    IR_Markers_Scan(&CurrentMarker);  // 10Hz
    
    // 2. ODOMETRY (1ms)
    Odometry_Update();
    
    // 3. MARKER CORRECTION
    if(CurrentMarker.ID != NO_MARKER) {
        Marker_CorrectPosition(CurrentMarker.ID);
        Dio_ToggleChannel(LED_PIN);  // Blink on correction
    }
    
    // 4. PID CONTROL (2ms)
    SpeedPID.Setpoint = 1200.0f;  // Target RPM
    float32_t speedOutput = PID_Update(&SpeedPID, RearEncoder.RPM);
    
    // Simple steering (towards center)
    float32_t steerError = 4.0f - CarPosition.X;  // Center of track
    float32_t steerOutput = PID_Update(&SteeringPID, steerError);
    
    // 5. MOTORS (1ms)
    Motor_SetSpeed(MOTOR_DRIVE, (uint16_t)speedOutput);
    Motor_SetDirection(MOTOR_STEER, 
        steerOutput > 0 ? DIRECTION_FORWARD : DIRECTION_BACKWARD);
    Motor_SetSpeed(MOTOR_STEER, (uint16_t)(steerOutput < 0 ? -steerOutput : steerOutput));
    
    // 6. TELEMETRY (1ms)
    Telemetry_Send();
    
    // 7. STATE MACHINE
    F1_Car_Update();
}

/*============================================================================
 * END OF F1 SIMULATOR FIRMWARE
 * Ready for compilation and upload to AVR32
 *===========================================================================*/
