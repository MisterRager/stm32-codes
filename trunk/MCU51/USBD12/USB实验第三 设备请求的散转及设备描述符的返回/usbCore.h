// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com
# ifndef  __USBCORE_H__
# define __USBCORE_H__

#include "MCU51_Types.h"
#include <at89x52.h>
#include "uart.h"
#include "d12.h"

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