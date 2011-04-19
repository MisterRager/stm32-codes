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

void SendReport(void);

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
		if(ConfigValue!=0)
		{
			LEDs=~KeyPress;
			if(!Ep1InIsBusy)
			{
				KeyCanChange=0;
				if(KeyUp||KeyDown||KeyPress)
				{
					SendReport();
				}
				KeyCanChange=1;
			}
		}
	}
}

/********************************************************************
函数功能：根据按键情况返回报告的函数。
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void SendReport(void)
{
 //需要返回的8字节报告的缓冲。但在本测试程序中，只使用前5字节。
	 u8 Buf[4]={0,0,0,0};
	 
	 KeyUp&=~(KEY1|KEY2|KEY3|KEY4);
	 KeyDown&=~(KEY1|KEY2|KEY3|KEY4);
	 if((KeyPress&(~(KEY7|KEY8)))||KeyUp||KeyDown)
	 {
	 	if(KeyPress&KEY1)
		{
			Buf[1]=-1;	
		}
		 	if(KeyPress&KEY2)
		{
			Buf[1]=-1;	
		}
		 	if(KeyPress&KEY3)
		{
			Buf[2]=-1;	
		}
		 	if(KeyPress&KEY4)
		{
			Buf[2]=-1;	
		}
		 	if(KeyPress&KEY5)
		{
			Buf[3]=-1;	
		}
		 	if(KeyPress&KEY6)
		{
			Buf[3]=1;	
		}
		 	if(KeyPress&KEY7)
		{
			Buf[0]|=0x01;	
		}
		 	if(KeyPress&KEY8)
		{
			Buf[0]|=0x02;	
		}
	   	D12WriteEndPointBuffer(3,4,Buf);
		Ep1InIsBusy=1;
	}
	KeyUp=0;
	KeyDown=0;
}
