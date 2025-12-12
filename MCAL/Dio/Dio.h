#ifndef DIO_H
#define DIO_H

void Dio_Init(void);
void Dio_WritePin(char port, uint8_t bit, uint8_t value); // e.g., 'B', PB0, 1
uint8_t Dio_ReadPin(char port, uint8_t bit);
void Dio_TogglePin(char port, uint8_t bit);

#endif
