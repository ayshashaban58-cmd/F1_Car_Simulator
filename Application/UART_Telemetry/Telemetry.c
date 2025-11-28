/*============================================================================
 * Telemetry Implementation
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * 100Hz packet transmission to ESP32
 *===========================================================================*/

#include "Telemetry.h"
#include "../../MCAL/UART/UART.h"
#include "../F1_Car/F1_Car.h"
#include "../Odometry/Odometry.h"
#include "../../HAL/Encoder/Encoder.h"
#include "../../HAL/IR_Markers_4x/IR_Markers.h"

static IR_Marker_t CurrentMarker;

Std_ReturnType Telemetry_Init(void) {
    UART_Init(115200);
    return E_OK;
}

Std_ReturnType Telemetry_Send(void) {
    // Scan markers every 100ms
    static uint8_t counter = 0;
    if(++counter >= 10) {
        IR_Markers_Scan(&CurrentMarker);
        counter = 0;
    }
    
    // Format: [F1][X:4.25][Y:3.87][T:45.2][S:1250][L:2][M:3]\r\n
    char buffer[100];
    float theta_deg = CarPosition.Theta * 180.0f / 3.14159f;
    snprintf(buffer, sizeof(buffer), 
        "[F1][X:%.2f][Y:%.2f][T:%.1f][S:%d][L:%d][M:%d]\r\n",
        CarPosition.X, CarPosition.Y, theta_deg,
        (int)RearEncoder.RPM, F1Car.CurrentLap, 
        (int)CurrentMarker.ID);
    
    UART_SendString(buffer);
    return E_OK;
}

Std_ReturnType Telemetry_ParseCommand(void) {
    uint8_t cmd;
    if(UART_Available()) {
        UART_ReceiveByte(&cmd);
        if(cmd == 'S') F1_Car_Start();      // START
        if(cmd == 'P') F1_Car_Stop();       // STOP
        if(cmd == 'R') F1_Car_Reset();      // RESET
    }
    return E_OK;
}
