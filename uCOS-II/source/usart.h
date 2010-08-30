#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"
#ifndef __USART_H
#define __USART_H


void SerialPutChar(u8 c);
void	Serial_PutString(unsigned char * str);

void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void UART4_Init(void);
void UART5_Init(void);

#endif



