/*============================================================================
 * F1 Simulator - Standard Types
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 *===========================================================================*/
 
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef signed char        sint8_t;
typedef signed short       sint16_t;
typedef signed long        sint32_t;
typedef float              float32_t;

typedef enum {
    E_OK = 0,
    E_NOT_OK
} Std_ReturnType;

typedef enum {
    FALSE = 0,
    TRUE = 1
} boolean;

#endif
