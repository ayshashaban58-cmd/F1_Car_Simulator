// src/MCAL/Dio/Dio.h

#ifndef DIO_H
#define DIO_H

void Dio_Init(void);
void Dio_WritePin(uint8_t pin, uint8_t value);
uint8_t Dio_ReadPin(uint8_t pin);
void Dio_TogglePin(uint8_t pin);

#endif
