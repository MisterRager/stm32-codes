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
u16 SendLength;
u8 NeedZeroPacket;

code u8 DeviceDescriptor[0x12]=
{
	0x12,//bLength
	0x01,//bDescriptorType
	0x10,//bcdUSB
	0x01,
	0x00,//bDeviceClass
	0x00,//bDeviceSubClass
	0x00,//bDeviceProtocol
	0x10,//bMaxPacketSize0
	0x88,//idVender
	0x88,
	0x01,//idProduct
	0x00,
	0x00,//bcdDevice
	0x01,
	0x01,//iManufacturer
	0x02,//iProduct
	0x03,//iSerialNumber
	0x01,//bNumConfigurations.
};

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
				Prints("Standard USB request.\r\n");
				#endif
			   	switch(bRequest)
				{
					case GET_CONFIGURATION:
					#ifdef DEBUG
					Prints("Get configuration.\r\n");
					#endif
					break;
	
					case GET_DESCRIPTOR:
					#ifdef DEBUG
					Prints("Get descriptor.\r\n");
					#endif
					switch((wValue>>8)&0xff)
					{
						case DEVICE_DESCRIPTOR:
						#ifdef DEBUG
						Prints("-Get device descriptor.\r\n");
						#endif
						pSendData=DeviceDescriptor;
						if(wLength>DeviceDescriptor[0])
						{
						#ifdef DEBUG
							Prints("Host want length of device descriptor is:");
							PrintShortIntHex(DeviceDescriptor[0]);
							Prints("\r\n");
						#endif
							SendLength=DeviceDescriptor[0];
							if(SendLength%DeviceDescriptor[7]==0)
							{
								NeedZeroPacket=1;
							}
						}
						else
						{
							SendLength=wLength;
						}
						UsbEp0SendData();
						break;

						case CONFIGURATION_DESCRIPTOR:
						#ifdef DEBUG
						Prints("-Get configuration descriptor.\r\n");
						#endif
						break;

						case STRING_DESCRIPTOR:
						#ifdef DEBUG
						Prints("-Get string descriptor.\r\n");
						#endif
						break;

						default:
						#ifdef DEBUG
						Prints("-Get other descriptor(unrecognized).\r\n");
						#endif
						break;
					}
					break;
	
					case GET_INTERFACE:
					#ifdef DEBUG
					Prints("Get Interface.\r\n");
					#endif
					break;
	
					case GET_STATUS:
					#ifdef DEBUG
					Prints("Get status.\r\n");
					#endif
					break;
	
					case SYNCH_FRAME:
					#ifdef DEBUG
					Prints("Synch frame.\r\n");
					#endif
					break;
	
					default:
					#ifdef DEBUG
					Prints("Error,undefined standard device request.\r\n");
					#endif
					break;
				}
				break;
	
				case 1:   //Class request.
				#ifdef DEBUG
				Prints("Class request.\r\n");
				#endif
				break;
	
				case 2: //³§ÉÌÇëÇó
				#ifdef DEBUG
				Prints("Vendor request.\r\n");
				#endif
				break;
	
				default:
				#ifdef DEBUG
				Prints("Error,undefined request.\r\n");
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
				Prints("Standard out.\r\n");
				#endif
	
				switch(bRequest)
				{
					case CLEAR_FEATURE:
					#ifdef DEBUG
					Prints("Clear feature.\r\n");
					#endif
					break;
	
					case SET_ADDRESS:
					#ifdef DEBUG
					Prints("Set address.\r\n");
					#endif
					break;
	
					case SET_CONFIGURATION:
					#ifdef DEBUG
					Prints("Set configuration.\r\n");
					#endif
					break;
	
					case SET_DESCRIPTOR:
					#ifdef DEBUG
					Prints("Set descriptor.\r\n");
					#endif
					break;
	
					case SET_FEATURE:
					#ifdef DEBUG
					Prints("Set feature.\r\n");
					#endif
					break;
	
					case SET_INTERFACE:
					#ifdef DEBUG
					Prints("Set interface.\r\n");
					#endif
					break;
	
					default:
					#ifdef DEBUG
					Prints("Error,undefined output request.\r\n");
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
				Prints("Vendor output request.\r\n");
				#endif
				break;
	
				default:
				#ifdef DEBUG
				Prints("Error,undefined output request.\r\n");
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
{
	#ifdef DEBUG
	Prints("USB ep0 in interrupt.\r\n");
	#endif
	D12ReadEndPointLastStatus(1);
	UsbEp0SendData();
}
void UsbEp1Out(void)
{}
void UsbEp1In(void)
{}
void UsbEp2Out(void)
{}
void UsbEp2In(void)
{}