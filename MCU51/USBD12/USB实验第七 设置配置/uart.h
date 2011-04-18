// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

# ifndef  __UART_H__
# define __UART_H__
#include "MCU51_Types.h"
void InitUart(void);
void Prints(u8* pd);
void PrintShortIntHex(u16 x);
void UartPutChar(u8 d);
# endif 