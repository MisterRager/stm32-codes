// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include "d12.h"
void DelayXms(u16 x)
{
	u16 i,j;
	for(i=0;i<x;i++)
	for(j=0;j<227;j++);
}

void D12WriteCMD(u8 command)
{
	D12SetCMDAddr();
	D12ClrWR();
	D12SetPortOut();
	D12SetData(command);
	D12SetWR();
	D12SetPortIn();
}

u8 D12ReadByte(void)
{
	u8 temp;
	D12SetDataAddr();
	D12ClrRD();
	temp=D12GetData();
	D12SetRD();
	return temp;
}

void D12WriteByte(u8 value)
{
	D12SetDataAddr();
	D12ClrWR();
	D12SetPortOut();
	D12SetData(value);
	D12SetWR();
	D12SetPortIn();
}

void USBDisconnect(void)
{
	#ifdef DEBUG
	Prints("disconnect.\n");
	#endif
	D12WriteCMD(D12_SET_MODE);
	D12WriteByte(0x06);
	D12WriteByte(0x47);
	DelayXms(1000);
}

void USBConnect(void)
{
	#ifdef DEBUG
	Prints("connect.\n");
	#endif
	D12WriteCMD(D12_SET_MODE);
	D12WriteByte(0x16);
	D12WriteByte(0x47);
}

