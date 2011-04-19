// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include <at89x52.h>

#include "uart.h"
#include "MCU51_Types.h"
#include "config.h"

void InitUart(void)
{
	EA=0;
	TMOD&=0X0F;
	TMOD|=0X20;
	SCON=0X50;
	TH1=256-Fclk/(BaudRate*12*16);
	TL1=256-Fclk/(BaudRate*12*16);
	PCON|=0X80;
	ES=1;
	TR1=1;
	REN=1;
	EA=1;
}

volatile u8 Sending;

void UartIsr(void) interrupt 4
{
	if(RI)  RI=0;
//	else {	TI=0; }
}

void UartPutChar(u8 d)
{
	SBUF=d;
	while(!TI);
	TI=0;
}
void Prints(u8 * pd)
{
	while((*pd)!='\0')
	{
		UartPutChar(*pd);
		pd++;
	}
}

code u8 HexTable[]={ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void PrintShortIntHex(u16 x)
{
	u8 i;
	u8 display_buffer[7];
	display_buffer[6]=0;
	display_buffer[0]='0';
	display_buffer[1]='x';
	for(i=5;i>=2;i--)
	{
		display_buffer[i]=HexTable[(x&0xf)];
		x>>=4;
	}
	Prints(display_buffer);
}
