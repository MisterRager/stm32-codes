// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

#include "d12.h"
#include "config.h"

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

void D12AckSetup(void)
{
	D12SelectEndPoint(1);
	D12WriteCMD(D12_ACKNOWLEGDE_SETUP);
	D12SelectEndPoint(0);
	D12WriteCMD(D12_ACKNOWLEGDE_SETUP);
}

u8 D12ReadEndPointLastStatus(u8 ep)
{
	D12WriteCMD(0x40+ep);
	return D12ReadByte();
}

u8 D12ReadEndPointBuffer(u8 ep,u8 len,u8 *buf)
{
	u8 i,j;
	D12SelectEndPoint(ep);
	D12WriteCMD(D12_READ_BUFFER);
	D12ReadByte();
	j=D12ReadByte();
#ifdef DEBUG
	Prints("Read endpoint");
	PrintShortIntHex((u16)(ep/2));
	Prints("  want ");
	PrintShortIntHex((u16)j);
	Prints("bytes of total ");
	PrintShortIntHex((u16)j);
	Prints("\n");
#endif
	j=j>len?len:j;
	for(i=0;i<j;i++)
	{
		D12ClrRD();
		*(buf+i)=D12GetData();
		D12SetRD();
#ifdef DEBUG
		PrintShortIntHex((u16)*(buf+i));
#endif
	}
	return j;
}

void D12ValidateBuffer(void)
{
	D12WriteCMD(D12_VALIDATE_BUFFER);
}

u8 D12WriteEndPointBuffer(u8 ep,u8 len,u8 *buf)
{
	u8 i;
	D12SelectEndPoint(ep);
	D12WriteCMD(D12_WRITE_BUFFER);
	D12WriteByte(0);
	D12WriteByte(len);

#ifdef DEBUG
	Prints("Write to endpoint:");
	PrintShortIntHex((u16)ep/2);
	Prints(", ");
	PrintShortIntHex((u16)len);
	Prints("bytes.\n");
#endif

	D12SetPortOut();
	for(i=0;i<len;i++)
	{
		D12ClrWR();
		D12SetData(*(buf+i));
		D12SetWR();
	}
	D12SetPortIn();
	D12ValidateBuffer();
	return len;
}
	
	



