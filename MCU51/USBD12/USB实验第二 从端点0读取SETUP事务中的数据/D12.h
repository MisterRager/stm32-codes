// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

# ifndef  __D12_H__
# define __D12_H__
#include <at89x52.h>
#include "MCU51_Types.h"

#define D12_CMD_ADDR  1
#define D12_DATA_ADDR 0
#define D12_DATA P0
#define D12_A0		P3_5
#define D12_WR		P3_6
#define D12_RD		P3_7
#define D12_INT		P3_2

#define D12SetWR()	D12_WR=1
#define D12ClrWR()	D12_WR=0
#define D12SetRD() 	D12_RD=1
#define D12ClrRD() 	D12_RD=0

#define D12SetCMDAddr() D12_A0=D12_CMD_ADDR
#define D12SetDataAddr() D12_A0=D12_DATA_ADDR


#define D12GetIntPin()	D12_INT
#define D12GetData()	D12_DATA
#define D12SetData(value)	D12_DATA=(value)
#define D12SetPortIn() 	D12_DATA=0xFF
#define D12SetPortOut()	
#define Read_ID	0xFD
#define D12_SET_MODE 0xF3

void D12WriteCMD(u8);
u8 D12ReadByte(void);
void D12WriteByte(u8 value);

void USBConnect(void);
void USBDisconnect(void);


#define D12ReadID(id)	\
{						  \
	D12WriteCMD(Read_ID);  \
	*id=D12ReadByte();		\
	*id|=((u16)D12ReadByte())<<8; \
}

				

# endif 