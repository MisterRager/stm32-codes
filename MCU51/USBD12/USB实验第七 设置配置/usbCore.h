// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com
# ifndef  __USBCORE_H__
# define __USBCORE_H__

#include "MCU51_Types.h"
#include "config.h"
#include <at89x52.h>
#include "uart.h"
#include "d12.h"

#define GET_STATUS         0
#define CLEAR_FEATURE      1
#define SET_FEATURE        3
#define SET_ADDRESS        5
#define GET_DESCRIPTOR     6
#define SET_DESCRIPTOR     7
#define GET_CONFIGURATION  8
#define SET_CONFIGURATION  9
#define GET_INTERFACE      10
#define SET_INTERFACE      11
#define SYNCH_FRAME        12

#define DEVICE_DESCRIPTOR         1
#define CONFIGURATION_DESCRIPTOR  2
#define STRING_DESCRIPTOR         3
#define INTERFACE_DESCRIPTOR      4
#define ENDPOINT_DESCRIPTOR       5
#define REPORT_DESCRIPTOR         0x22

#define SET_IDLE 0x0A

extern idata u8 Buffer[16];
extern u8 bmRequestType;
extern u8 bRequest;
extern u16 wValue;
extern u16 wIndex;
extern u16 wLength;
extern u8 * pSendData;
extern u16 SendLength;
extern u8 NeedZeroPacket;
extern code u8 DeviceDescriptor[];
extern code u8 ReportDescriptor[];
extern code u8 ConfigurationDescriptor[];
extern u8 ConfigValue;
extern u8 Ep1InIsBusy;

void UsbBusSuspend(void);
void UsbBusReset(void);
void UsbEp0Out(void)   ;
void UsbEp0In(void)    ;
void UsbEp1Out(void)   ;
void UsbEp1In(void)	   ;
void UsbEp2Out(void)   ;
void UsbEp2In(void)	   ;
void UsbEp0SendData(void);


# endif 