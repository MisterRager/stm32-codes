// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#ifndef  __KEY_H__
#define __KEY_H__

#include <at89x52.h>
#include "MCU51_Types.h"
#include "config.h"


extern volatile u8 idata KeyCurrent,KeyOld,KeyNoChangedTime;
extern volatile u8 idata KeyPress;
extern volatile u8 idata KeyDown,KeyUp,KeyLast;
extern volatile u8 KeyCanChange;

void InitKeyBoard(void);

#define KeyIO P1

#define GetKeyValue() (~KeyIO)

#define	KEY1 0x01
#define KEY2 0x02
#define KEY3 0x03
#define KEY4 0x04
#define KEY5 0X05
#define KEY6 0X06
#define KEY7 0X07
#define KEY8 0X08

#endif 
