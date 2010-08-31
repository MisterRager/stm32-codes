#ifndef __USART_H
#define __USART_H
#include "../Config.h"
#if	(USE_USART1==1 )
#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"
#include "stdio.h"

#if(TTY_AS_USART1==1)
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
#endif
void TTY_USART1_Init(void);
void TTY_USART1_GPIO_Configuration(void);
#endif
#endif



