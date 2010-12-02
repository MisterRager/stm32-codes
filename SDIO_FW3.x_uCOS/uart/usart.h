#include "stm32f10x.h"
#ifndef __USART_H
#define __USART_H

struct USART_Data
{
	unsigned int ByteCount;
	unsigned int Value;
	bool Locked;
} ;

#define SEND_LENGTH 50
extern unsigned char Send_Length;
extern unsigned char Send_Data[SEND_LENGTH];

extern struct USART_Data USART2_Data;
extern struct USART_Data USART3_Data;
extern struct USART_Data UART4_Data;
extern struct USART_Data UART5_Data;

void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void UART4_Init(void);
void UART5_Init(void);

#endif



