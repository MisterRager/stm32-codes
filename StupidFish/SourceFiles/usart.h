#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"
#ifndef __USART_H
#define __USART_H

#define SEND_LENGTH 50
extern unsigned char Send_Length;
extern unsigned char Send_Data[SEND_LENGTH];

void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void UART4_Init(void);
void UART5_Init(void);

#endif



