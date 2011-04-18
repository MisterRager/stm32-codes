// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include <AT89X52.H>
#include "MCU51_Types.h"
#include "key.h"

idata volatile u8  KeyCurrent,KeyOld,KeyNoChangedTime;
idata volatile u8  KeyPress;
idata volatile u8  KeyDown,KeyUp,KeyLast;
volatile u8 KeyCanChange;

void InitTimer0(void)
{
	TMOD&=0xf0;
	TMOD|=0x01;
	ET0=1;
	TR0=1;
}

void InitKeyBoard(void)
{
	KeyIO=0xFF;
	KeyPress=0;
	KeyNoChangedTime=0;
	KeyOld=0;
	KeyCurrent=0;
	KeyLast=0;
	KeyDown=0;
	KeyUp=0;
	InitTimer0();
	KeyCanChange=1;
}

void Timer0Isr(void) interrupt 1
{
	TH0=(65535-Fclk/1000/12*5+15)/256;
	TL0=(65535-Fclk/1000/12*5+15)%256;

	if(!KeyCanChange) return;
	KeyCurrent=GetKeyValue();

	if(KeyCurrent!=KeyOld)
	{
		KeyNoChangedTime=0;
		KeyOld=KeyCurrent;
		return;
	}
	else
	{
		KeyNoChangedTime++;
		if(KeyNoChangedTime>=1)
		{
			KeyNoChangedTime=1;
			KeyPress=KeyOld;
			KeyDown|=(~KeyLast)&(KeyPress);
			KeyUp|=KeyLast&(~KeyPress);
			KeyLast=KeyPress;
		}
	}
}



