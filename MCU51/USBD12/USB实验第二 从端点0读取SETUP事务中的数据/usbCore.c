// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include "usbCore.h"

idata u8 Buffer[16];

void UsbBusSuspend(void)
{}
void UsbBusReset(void)
{}
void UsbEp0Out(void)
{
#ifdef DEBUG
	Prints("USB ep0 out interrupt.");
#endif 
	if(D12ReadEndPointLastStatus(0)&0x20)
	{
		D12ReadEndPointBuffer(0,16,Buffer);
		D12AckSetup();
		D12ClearBuffer();
	}
	else
	{
		D12ReadEndPointBuffer(0,16,Buffer);
		D12ClearBuffer();
	}
}
void UsbEp0In(void) 
{}
void UsbEp1Out(void)
{}
void UsbEp1In(void)
{}
void UsbEp2Out(void)
{}
void UsbEp2In(void)
{}