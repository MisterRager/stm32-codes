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

extern idata u8 Buffer[16];
void UsbBusSuspend(void);
void UsbBusReset(void);
void UsbEp0Out(void)   ;
void UsbEp0In(void)    ;
void UsbEp1Out(void)   ;
void UsbEp1In(void)	   ;
void UsbEp2Out(void)   ;
void UsbEp2In(void)	   ;
# endif 