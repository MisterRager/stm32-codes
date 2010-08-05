#include "spi.h"
#include "nRF24L01.h"
#include "stm32f10x_lib.h"
#include "secondarylib.h"
#include "stepmotor.h"
#include "usart.h"
#include "timer.h"
u8 TxBuf[32]={0};
unsigned int sta;

unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static TX address
unsigned char rx_buf[TX_PLOAD_WIDTH];
unsigned char tx_buf[TX_PLOAD_WIDTH];
unsigned char flag;
unsigned char rx_com_buffer[10];
unsigned char tx_com_buffer[10];
unsigned char i;
unsigned char accept_flag;
// SPI(nRF24L01) commands

#define RF_READ_REG    0x00  // Define read command to register
#define RF_WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

#define  RX_DR  ((sta>>6)&0X01)
#define  TX_DS  ((sta>>5)&0X01)
#define  MAX_RT  ((sta>>4)&0X01)

//Chip Enable Activates RX or TX mode
#define CE_H()   GPIO_SetBits(GPIOE, GPIO_Pin_1) 
#define CE_L()   GPIO_ResetBits(GPIOE, GPIO_Pin_1)

//SPI Chip Select
#define CSN_H()  GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define CSN_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_12)

void SPI2_Init(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
  GPIO_InitTypeDef 	GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //enable spi2 clock.
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;// |GPIO_Pin_14 |GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	//CE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	//IRQ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	 SPI_Cmd(SPI2, DISABLE); 
	/* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //SPI设置为双线双向全双工 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //设置为主 SPI 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //SPI发送接收 8 位帧结构 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //时钟悬空高 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //数据捕获于第二个时钟沿 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;// 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//波特率预分频值为 256 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//数据传输从 MSB 位开始 
  SPI_InitStructure.SPI_CRCPolynomial = 7;//定义了用于 CRC值计算的多项式 7
  SPI_Init(SPI2, &SPI_InitStructure);
  /* Enable SPI2   */
  SPI_Cmd(SPI2, ENABLE);	
}

void Delay_us(unsigned int  n)
{
	u32 i;
	
	while(n--)
	{
 	   i=2;
 	   while(i--);
  }
}



/*******************************************************************************
* Function Name   : SPI2_RW
* Description : Sends a byte through the SPI interface and return the byte
*                received from the SPI bus.
* Input       : byte : byte to send.
* Output       : None
* Return       : The value of the received byte.
*******************************************************************************/
u8 SPI2_readWrite(u8 byte)
{
   /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
   /* Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(SPI2, byte);
   /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
   /* Return the byte read from the SPI bus */
   return SPI_I2S_ReceiveData(SPI2);
}


unsigned char SPI2_readWriteReg(unsigned char reg, unsigned char value)
{
	unsigned char status;
	CSN_L();
	// select register 
	status = SPI2_readWrite(reg);
	// set value
	SPI2_readWrite(value);
	CSN_H();
	return(status);
}

unsigned char SPI2_readReg(unsigned char reg)
{
	unsigned char reg_val;
   CSN_L();                    // CSN置低，开始传输数据
   SPI2_readWrite(reg);                // 选择寄存器
   reg_val = SPI2_readWrite(0);        // 然后从该寄存器读数据
   CSN_H();                    // CSN拉高，结束数据传输
   return(reg_val);            // 返回寄存器数据
}

unsigned char SPI2_readBuf(unsigned char reg,unsigned char *pBuf, unsigned char bytes)
{
	unsigned char status,i;
	CSN_L();
	// Select register to write to and read status byte
	status = SPI2_readWrite(reg);
	for(i=0;i<bytes;i++)
		pBuf[i] = SPI2_readWrite(0);
	CSN_H();
	return(status);
}

unsigned char SPI2_writeBuf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
	unsigned char status,i;
	CSN_L();
	// Select register to write to and read status byte
	status = SPI2_readWrite(reg);
	for(i=0; i<bytes; i++) // then write all byte in buffer(*pBuf)
		SPI2_readWrite(*pBuf++);
	CSN_H();
	return(status);
}

void RX_Mode(void)
{
	 CE_L();
	SPI2_writeBuf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
	SPI2_readWriteReg(WRITE_REG + EN_AA, 0x01);
	// Enable Auto.Ack:Pipe0
	SPI2_readWriteReg(WRITE_REG + EN_RXADDR, 0x01); // Enable Pipe0
	SPI2_readWriteReg(WRITE_REG + RF_CH, 40);
	// Select RF channel 40
	SPI2_readWriteReg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
	SPI2_readWriteReg(WRITE_REG + RF_SETUP, 0x07);
	SPI2_readWriteReg(WRITE_REG + CONFIG, 0x0f);
	// Set PWR_UP bit, enable CRC(2 bytes)
	//& Prim:RX. RX_DR enabled..
	 CE_H(); // Set CE pin high to enable RX device
	// This device is now ready to receive one packet of 16 bytes payload from a TX device
	//sending to address
	// '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and
	//datarate = 2Mbps.
}

void TX_Mode(unsigned char * BUF)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);//CE=0
	SPI2_writeBuf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPI2_writeBuf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
	SPI2_writeBuf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH); // Writes data to TX payload
	SPI2_readWriteReg(WRITE_REG + EN_AA, 0x01);
	// Enable Auto.Ack:Pipe0
	SPI2_readWriteReg(WRITE_REG + EN_RXADDR, 0x01); // Enable Pipe0
	SPI2_readWriteReg(WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
	SPI2_readWriteReg(WRITE_REG + RF_CH, 40);
	// Select RF channel 40
	SPI2_readWriteReg(WRITE_REG + RF_SETUP, 0x07);
	// TX_PWR:0dBm, Datarate:2Mbps,
//	LNA:HCURR
	SPI2_readWriteReg(WRITE_REG + CONFIG, 0x0e);
	// Set PWR_UP bit, enable CRC(2 bytes)
	//& Prim:TX. MAX_RT & TX_DS enabled..
	GPIO_SetBits(GPIOE,GPIO_Pin_1); // Set CE pin high 
}





void init_NRF24L01(void)
{
 u8 buf[5]={0};
 
  Delay_us(100);


  CE_L();    // chip enable
  //CSN_H();   // Spi disable 
  
  SPI2_readBuf(TX_ADDR, buf, TX_ADR_WIDTH);
}

void init_io(void)
{
 CE_L();        // 待机
 CSN_H();        // SPI禁止
 RX_Mode(); //接收
}



int main(void)
{
	unsigned int nCount;
	unsigned char vEncoder[30]="abcdgsdfgdfgsdfgsdffgsdfgsdf";
	int i;
  RCC_Configuration();
	NVIC_Configuration();
  USART1_Init();
	USART2_Init();															
	USART3_Init();
	UART4_Init();
	UART5_Init();
	SPI2_Init();
	SysTick_Init();
	init_NRF24L01();
  while(1)
{
	//Serial_PutString("Running"); 
	RX_Mode();		              // 设置为接收模式
	//TX_Mode(vEncoder);			// 把nRF24L01设置为发送模式并发送数据
  //SPI2_readWriteReg(WRITE_REG+STATUS,(SPI2_readReg(READ_REG+STATUS)));	// clear interrupt flag(TX_DS)
	Delayms(100);
	RX_Mode();			        // 设置为接收模式


	

			SPI2_readBuf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);
			Serial_PutString(rx_buf);

}
}	 









