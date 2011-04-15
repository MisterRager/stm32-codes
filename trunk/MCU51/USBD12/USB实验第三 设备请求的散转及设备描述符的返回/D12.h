// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

# ifndef  __D12_H__
# define __D12_H__
#include <at89x52.h>
#include "MCU51_Types.h"
#include "uart.h"

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
#define D12_READ_INTERRUPT_REGISTER 0xF4
#define D12_READ_BUFFER  0xF0
#define D12_VALIDATE_BUFFER 0xFA
#define D12_WRITE_BUFFER 0xF0


#define D12ClearBuffer(void) D12WriteCMD(D12_CLEAR_BUFFER)
#define D12_CLEAR_BUFFER 0xF2
#define D12_ACKNOWLEGDE_SETUP	  0xF1
#define D12SelectEndPoint(x) D12WriteCMD(x)	 //只能为下面的六个宏之一的值
#define D12_EP0_OUT 0
#define D12_EP0_IN 1
#define D12_EP1_OUT 2
#define D12_EP1_IN	3
#define D12_EP2_OUT 4
#define D12_EP2_IN 5


void D12WriteCMD(u8);
u8 D12ReadByte(void);
void D12WriteByte(u8 value);

void USBConnect(void);
void USBDisconnect(void);
void D12AckSetup(void) ;
u8 D12ReadEndPointBuffer(u8 ep,u8 len,u8 *buf);
u8 D12ReadEndPointLastStatus(u8 ep);


#define D12ReadID(id)	\
{						  \
	D12WriteCMD(Read_ID);  \
	*id=D12ReadByte();		\
	*id|=((u16)D12ReadByte())<<8; \
}



				

# endif 