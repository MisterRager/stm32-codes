// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include <AT89X52.H>
#include "key.h"
#include "uart.h"
#include "MCU51_Types.h"
#include "config.h"
#include "led.h"
#include "d12.h"

void main(void)
{
	u16 id;
	InitUart();
	InitKeyBoard();
	//***********************************
//	Prints("adfasdfadsfasf");
//	LightUpLed(LED1);
//	TurnOffLed(LED2);
	Prints("\nGetting chip ID...");
	D12ReadID(&id);
	PrintShortIntHex(id);
	Prints(",over\n");
	
	USBConnect();
   	
	//************************************
	while(1);
}
