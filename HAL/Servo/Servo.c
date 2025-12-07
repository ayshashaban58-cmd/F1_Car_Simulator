/*
 * Servo.c - Servo Motor Driver Implementation
 * Standard servo: 1ms (0°) to 2ms (180°) pulse width, 20ms period
 * For steering: 1.5ms = center, 1ms = -45°, 2ms = +45°
 */

#include "Servo.h"
#include "../../MCAL/Timer/Timer.h"

// Servo PWM values for 10-bit PWM (~977Hz)
// For standard servo timing:
// 1ms pulse = 49 counts, 1.5ms = 73 counts, 2ms = 98 counts
// We'll use center = 77, min = 52, max = 102 for -45° to +45°
#define SERVO_PWM_MIN 52     // -45° (left)
#define SERVO_PWM_CENTER 77  // 0° (center)
#define SERVO_PWM_MAX 102    // +45° (right)

void Servo_Init(void) {
    // Center the servo
    Servo_Center();
}

void Servo_SetAngle(int8_t angle) {
    // Limit angle to -45° to +45°
    if(angle < SERVO_ANGLE_MIN) angle = SERVO_ANGLE_MIN;
    if(angle > SERVO_ANGLE_MAX) angle = SERVO_ANGLE_MAX;
    
    // Map angle (-45 to +45) to PWM (52 to 102)
    // PWM = CENTER + (angle * (MAX-MIN) / (ANGLE_MAX - ANGLE_MIN))
    int16_t pwm_range = SERVO_PWM_MAX - SERVO_PWM_MIN;
    int16_t angle_range = SERVO_ANGLE_MAX - SERVO_ANGLE_MIN;
    uint16_t pwm_value = SERVO_PWM_CENTER + ((angle * pwm_range) / angle_range);
    
    Timer_SetPWM(PWM_SERVO, pwm_value);
}

void Servo_Center(void) {
    Timer_SetPWM(PWM_SERVO, SERVO_PWM_CENTER);
}
