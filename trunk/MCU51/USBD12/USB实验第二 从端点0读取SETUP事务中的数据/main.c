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
#include "usbCore.h"

void main(void)
{
	u16 id;
	u8 InterruptSource;
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
	while(1)
	{
		if(D12GetIntPin()==0)
		{
			D12WriteCMD(D12_READ_INTERRUPT_REGISTER);
			InterruptSource=D12ReadByte();
			if(InterruptSource&0x80) UsbBusSuspend();
			if(InterruptSource&0x40) UsbBusReset();
			if(InterruptSource&0x01) UsbEp0Out();
			if(InterruptSource&0x02) UsbEp0In();
			if(InterruptSource&0x04) UsbEp1Out();
			if(InterruptSource&0x08) UsbEp1In();
			if(InterruptSource&0x10) UsbEp2Out();
			if(InterruptSource&0x20) UsbEp2In();
		}
	}
}
