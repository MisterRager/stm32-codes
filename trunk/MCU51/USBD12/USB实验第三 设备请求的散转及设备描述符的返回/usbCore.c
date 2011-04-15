// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include "usbCore.h"

idata u8 Buffer[16];

u8 bmRequestType;
u8 bRequest;
u16 wValue;
u16 wIndex;
u16 wLength;
u8 * pSendData;
u16 wSendLength;
u8 NeedZeroPacket;

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

		bmRequestType=Buffer[0];
		bRequest=Buffer[1];
		wValue=Buffer[2]+(((u16)Buffer[3])<<8);
		wIndex=Buffer[4]+(((u16)Buffer[5])<<8);
		wLength=Buffer[6]+(((u16)Buffer[7])<<8);

		if((bmRequestType&0x80)==0x80)
		{
			switch((bmRequestType>>5)&0x03)
			{
				case 0:
				#ifdef DEBUG
				Prints("Standard USB request.\n");
				#endif
			   	switch(bRequest)
				{
					case GET_CONFIGURATION:
					#ifdef DEBUG
					Prints("Get configuration.\n");
					#endif
					break;
	
					case GET_DESCRIPTOR:
					#ifdef DEBUG
					Prints("Get descriptor.\n");
					#endif
					break;
	
					case GET_INTERFACE:
					#ifdef DEBUG
					Prints("Get Interface.\n");
					#endif
					break;
	
					case GET_STATUS:
					#ifdef DEBUG
					Prints("Get status.\n");
					#endif
					break;
	
					case SYNCH_FRAME:
					#ifdef DEBUG
					Prints("Synch frame.\n");
					#endif
					break;
	
					default:
					#ifdef DEBUG
					Prints("Error,undefined standard device request.\n");
					#endif
					break;
				}
				break;
	
				case 1:   //Class request.
				#ifdef DEBUG
				Prints("Class request.\n");
				#endif
				break;
	
				case 2: //³§ÉÌÇëÇó
				#ifdef DEBUG
				Prints("Vendor request.\n");
				#endif
				break;
	
				default:
				#ifdef DEBUG
				Prints("Error,undefined request.\n");
				#endif
				break;
			}
		}
		else
		{
			switch((bmRequestType>>5)&0x03)
			{
				case 0:
				#ifdef DEBUG
				Prints("Standard out.\n");
				#endif
				break;
	
				switch(bRequest)
				{
					case CLEAR_FEATURE:
					#ifdef DEBUG
					Prints("Clear feature.\n");
					#endif
					break;
	
					case SET_ADDRESS:
					#ifdef DEBUG
					Prints("Set address.\n");
					#endif
					break;
	
					case SET_CONFIGURATION:
					#ifdef DEBUG
					Prints("Set configuration.\n");
					#endif
					break;
	
					case SET_DESCRIPTOR:
					#ifdef DEBUG
					Prints("Set descriptor.\n");
					#endif
					break;
	
					case SET_FEATURE:
					#ifdef DEBUG
					Prints("Set feature.\n");
					#endif
					break;
	
					case SET_INTERFACE:
					#ifdef DEBUG
					Prints("Set interface.\n");
					#endif
					break;
	
					default:
					#ifdef DEBUG
					Prints("Error,undefined output request.\n");
					#endif
					break;
				}
	
				case 1:  //class request.
				#ifdef DEBUG
				Prints("Class output request.");
				#endif
				break;
	
				case 2: //vendor request.
				#ifdef DEBUG 
				Prints("Vendor output request.\n");
				#endif
				break;
	
				default:
				#ifdef DEBUG
				Prints("Error,undefined output request.\n");
				#endif
				break;
			}
		}
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