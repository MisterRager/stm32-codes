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

code u8 ReportDescriptor[]=
{
	0x00,
};

code u8 ConfigurationDescriptor[9+9+9+7]=
{
/*********************configuration descriptor,9bytes**************************/
0x09, //1  bLength
0x02, //2  bDescriptorType.
sizeof(ConfigurationDescriptor)&0xff,//3  lower byte of wTotalLength
(sizeof(ConfigurationDescriptor)>>8)&0xff,//4  higher byte of wTotalLength
0x01,//5  bNumInterface
0x01,//6  bNumConfiguration
0x00,//7  iConfiguration
0x80,//8  bmAttributes
0x32,//9  mMaxPower.
/********************Interface descriptor,9bytes*******************************/
0x09, //1  bLength
0x04, //2  bDescriptorType
0x00, //3  bInterfaceNumber
0x00, //4  bAlternateSetting
0x01, //5  bNumEndpoints
0x03, //6  bInterfaceClass
0x01, //7  bInterfaceSubClass
0x02, //8  bInterfaceProtocol
0x00, //9  iConfiguration
/*********************HID descriptor,9bytes*****************************************/
0x09, //1  bLength
0x21, //2  bDescriptorType
0x10, //3  bcdHID
0x01, //4  bcdHID
0x21, //5  bCountryCode
0x01, //6  bNumDescriptors
0x22, //7  bDescriptorType
sizeof(ReportDescriptor)&0xff,
(sizeof(ReportDescriptor)>>8)&0xff,
/*************************Endpoint descriptor**************************************/
0x07, //1  bLength
0x05, //2  bDescriptorType
0x81, //3  bEndpointAddress
0x03, //4  bmAttributes
0x10, //5  wMaxPacketSize
0x00, //6  wMaxPacketSize
0x0A, //7  bInterval
};

code u8 LanguageId[4]=
{
0x04, //1  bLength
0x03, //2  bDescriptorType
0x09, //3  //american english
0x04,
};

code u8 ManufacturerStringDescriptor[]=
{
0x08,	 //bLength
0x03,//bDescriptorType
0x20,0x5F,
0x8F,0x79,
0x87,0x65,
};

code u8 ProductStringDescriptor[]=
{
0x08,
0x03,
0x2A, 0x67,
0xE5, 0x77,
0x0D, 0x54,	
};

code u8 SerialNumberStringDescriptor[]=
{
0x08,
0x03,
0x32, 0x4E,
0x4C, 0x88,
0x26, 0x7B,
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
						pSendData=ConfigurationDescriptor;
						SendLength=ConfigurationDescriptor[3];
						SendLength=SendLength*256+ConfigurationDescriptor[2];
						if(wLength>SendLength)
						{
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

						case STRING_DESCRIPTOR:
						#ifdef DEBUG
						Prints("-Get string descriptor.\r\n");
						#endif
						switch(wValue&0xff)
						{
							case 0:
							#ifdef DEBUG 
							Prints("--Get Language ID.\r\n");
							#endif
							pSendData=LanguageId;
							SendLength=LanguageId[0];
							break;

							case 1:
							#ifdef DEBUG
							Prints("--Get Manufacturer string.\r\n");
							#endif
							pSendData=ManufacturerStringDescriptor;
							SendLength=ManufacturerStringDescriptor[0];
							break;

							case 2:
							#ifdef DEBUG
							Prints("--Get product string.\r\n");
							#endif
							pSendData=ProductStringDescriptor;
							SendLength=ProductStringDescriptor[0];

							case 3:
							#ifdef DEBUG
							Prints("--Get serial string.\r\n");
							#endif
							pSendData=SerialNumberStringDescriptor;
							SendLength=SerialNumberStringDescriptor[0];
							break;

							default:
							#ifdef DEBUG
							Prints("Undefined index.\r\n");
							#endif
							SendLength=0;
							NeedZeroPacket=1;
							break;
						}
						if(wLength>SendLength)
						{
							if(SendLength%DeviceDescriptor[7]==0)
								NeedZeroPacket=1;
						}
						else 
						{
							SendLength=wLength;
						}
						UsbEp0SendData();
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
					Prints("Address is :");
					PrintShortIntHex(wValue&0xff);
					Prints("\r\n");
					#endif
					D12SetAddress(wValue&0xff);
					SendLength=0;
					NeedZeroPacket=1;
					UsbEp0SendData();
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