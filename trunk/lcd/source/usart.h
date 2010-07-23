#ifndef __USART_H
#define __USART_H

#include "stm32f10x_type.h" 
#include "stm32f10x_lib.h" 
 
void SerialPutChar(u8 c); 
void Serial_PutString(u8 *s); 
void USART1_Init(void);
#endif

/* usart.h end */   
