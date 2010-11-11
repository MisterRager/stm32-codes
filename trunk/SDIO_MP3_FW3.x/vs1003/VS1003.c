/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "vs1003.h"
#include "stm32f10x_spi.h"

/* Const define  -------------------------------------------------------------*/
#define RXNE    0x01
#define TXE     0x02
#define BSY     0x80

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay
* Input          : nTime--delay time 
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(u32 nTime)
{
	unsigned int i;
	unsigned long j;
	for(i = nTime;i > 0;i--)
		for(j = 1000;j > 0;j--);	
}

/*******************************************************************************
* Function Name  : SPIPutChar
* Description    : Send one byte by SPI1
* Input          : outb--the byte to be sended 
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char  SPIPutChar(unsigned char outb)
{   
   /* Write and Read a byte on SPI interface. */
   unsigned char inb;

   /* Wait if TXE cleared, Tx FIFO is full. */
   while ((SPI1->SR & TXE) == 0);
   SPI1->DR = outb;
   /* Wait if RNE cleared, Rx FIFO is empty. */
   while ((SPI1->SR & RXNE) == 0);
   inb = SPI1->DR;
   return (inb);

}

/*******************************************************************************
* Function Name  : SPIGetChar
* Description    : Read a byte from the SPI.
* Input          : None.
* Output         : None
* Return         : The received byte.
*******************************************************************************/
u8 SPIGetChar(void)
{
  u8 Data = 0;

  /* Wait until the transmit buffer is empty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  /* Send the byte */
  SPI_I2S_SendData(SPI1, 0xFF);

  /* Wait until a data is received */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
  /* Get the received data */
  Data = SPI_I2S_ReceiveData(SPI1);

  /* Return the shifted data */
  return Data;
}

/*******************************************************************************
* Function Name  : Mp3SoftReset
* Description    : Soft reset the VS1003 chip
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void Mp3SoftReset(void)
{

	Mp3WriteRegister (SPI_MODE, 0x08, 0x04); 			// �����λ

	Delay(1); 	
	while (GPIO_ReadInputData(GPIOC) & MP3_DREQ == 0); 	// �ȴ������λ����
	Mp3WriteRegister(SPI_CLOCKF, 0x98, 0x00);			// ����vs1003��ʱ��,3��Ƶ
	Mp3WriteRegister (SPI_AUDATA, 0xac, 0x44); 			// ������48k��������
	Mp3WriteRegister(SPI_BASS, 0x00, 0x55);				// ��������
	Mp3SetVolume(0,0);									// ��������
    Delay(1);	
    	
    //��vs1003����4���ֽ���Ч���ݣ���������SPI����
    Mp3SelectData();
	SPIPutChar(0);
	SPIPutChar(0);
	SPIPutChar(0);
	SPIPutChar(0);
	Mp3DeselectData();

}

/*******************************************************************************
* Function Name  : Mp3Reset
* Description    : Reset the VS1003 chip
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void Mp3Reset(void)
{
	Mp3PutInReset();									//xReset = 0   ��λvs1003      
	Delay(100);		
	SPIPutChar(0xff);									//����һ���ֽڵ���Ч���ݣ�����SPI����
	Mp3DeselectControl();   							//xCS = 1
	Mp3DeselectData();     								//xDCS = 1
	Mp3ReleaseFromReset(); 								//xRESET = 1
	Delay(100);	           								//��ʱ100ms
	while (GPIO_ReadInputData(GPIOC) & MP3_DREQ == 0);	//�ȴ�DREQΪ��
    Delay(100);	
    Mp3SoftReset();										//vs1003��λ

}

/*******************************************************************************
* Function Name  : VsSineTest
* Description    : VS1003 sine test
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void VsSineTest(void)
{
	Mp3PutInReset();  //xReset = 0   ��λvs1003
	Mp3Reset();
	Delay(1000);//wait(100);        //��ʱ100ms     
	SPIPutChar(0xff);//����һ���ֽڵ���Ч���ݣ�����SPI����
	Mp3DeselectControl();  
	Mp3DeselectData();     
	Mp3ReleaseFromReset(); 
	
	Mp3Reset();
	Delay(500);//wait(100);	  
	
	Mp3SetVolume(50,50);//��������
             
 	Mp3WriteRegister(SPI_MODE,0x08,0x20);//����vs1003�Ĳ���ģʽ
	Delay(500);
	while (GPIO_ReadInputData(GPIOC) & MP3_DREQ == 0);     //�ȴ�DREQΪ��

 	Mp3SelectData();       //xDCS = 1��ѡ��vs1003�����ݽӿ�
 	
 	//��vs1003�������Ҳ������0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
 	//����n = 0x24, �趨vs1003�����������Ҳ���Ƶ��ֵ��������㷽����vs1003��datasheet
    SPIPutChar(0x53);      
	SPIPutChar(0xef);      
	SPIPutChar(0x6e);      
	SPIPutChar(0x24);      
	SPIPutChar(0x00);      
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(1000);
	Mp3DeselectData();//����ִ�е������Ӧ���ܴӶ�������һ����һƵ�ʵ�����
  
    //�˳����Ҳ���
	Mp3SelectData();
	SPIPutChar(0x45);
	SPIPutChar(0x78);
	SPIPutChar(0x69);
	SPIPutChar(0x74);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(1000);
	Mp3DeselectData();

    //�ٴν������Ҳ��Բ�����nֵΪ0x44���������Ҳ���Ƶ������Ϊ�����ֵ
    Mp3SelectData();       
	SPIPutChar(0x53);      
	SPIPutChar(0xef);      
	SPIPutChar(0x6e);      
	SPIPutChar(0x44);      
	SPIPutChar(0x00);      
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(1000);
	Mp3DeselectData(); 

	//�˳����Ҳ���
	Mp3SelectData();
	SPIPutChar(0x45);
	SPIPutChar(0x78);
	SPIPutChar(0x69);
	SPIPutChar(0x74);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(1000);
	Mp3DeselectData();

 }

/*******************************************************************************
* Function Name  : VsRamTest
* Description    : Test VS1003's register,if received value is 0x807F,then 
				   indicate the VS1003 is OK.
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void VsRamTest(void)
{
	u16 regvalue ;

	regvalue = 0;
	Mp3PutInReset();  	
	Delay(100);	      
	SPIPutChar(0xff);										//����һ���ֽڵ���Ч���ݣ�����SPI����
	Mp3DeselectControl();  
	Mp3DeselectData();     
	Mp3ReleaseFromReset(); 
	Delay(100);	           
 	Mp3WriteRegister(SPI_MODE,0x08,0x20);					// ����vs1003�Ĳ���ģʽ
	while (GPIO_ReadInputData(GPIOC) & MP3_DREQ == 0);     	// �ȴ�DREQΪ��
 	Mp3SelectData();       									// xDCS = 1��ѡ��vs1003�����ݽӿ�
 	
    SPIPutChar(0x4d);      
	SPIPutChar(0xea);      
	SPIPutChar(0x6d);      
	SPIPutChar(0x54);      
	SPIPutChar(0x00);      
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(500);	
	Mp3DeselectData();					
  
	regvalue = Mp3ReadRegister(SPI_HDAT0);      				// ����õ���ֵΪ0x807F���������á�

}

/*******************************************************************************
* Function Name  : Mp3WriteRegister
* Description    : Write VS1003 register
* Input          : addressbyte--the vs1003 register address
				   highbyte--the hight 8 bits
				   lowbyte--the low 8 bits
* Output         : None
* Return         : None
*******************************************************************************/
void Mp3WriteRegister(unsigned char addressbyte, unsigned char highbyte, unsigned char lowbyte)
{
	Mp3DeselectData();
	Mp3SelectControl();				//XCS = 0
	SPIPutChar(VS_WRITE_COMMAND); 	//����д�Ĵ�������
	SPIPutChar(addressbyte);      	//���ͼĴ����ĵ�ַ
	SPIPutChar(highbyte);         	//���ʹ�д���ݵĸ�8λ
	SPIPutChar(lowbyte);          	//���ʹ�д���ݵĵ�8λ
	Mp3DeselectControl();
}

/*******************************************************************************
* Function Name  : Mp3ReadRegister
* Description    : Read VS1003 register
* Input          : addressbyte--the vs1003 register address
* Output         : None
* Return         : The register value
*******************************************************************************/
u16 Mp3ReadRegister(unsigned char addressbyte)
{
	u16 resultvalue = 0;
	Mp3DeselectData();
	Mp3SelectControl();				//XCS = 0
	SPIPutChar(VS_READ_COMMAND); 	//���Ͷ��Ĵ�������
	SPIPutChar(addressbyte);	 	//���ͼĴ����ĵ�ַ
	resultvalue = SPIGetChar() << 8;//��ȡ��8λ����
	resultvalue |= SPIGetChar();  	//��ȡ��8λ����
	Mp3DeselectControl();              
	return resultvalue;           	//����16λ�Ĵ�����ֵ

}

/*******************************************************************************
* Function Name  : VS1003_Config
* Description    : Configures the GPIO ports and SPI1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VS1003_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* PC2->DREQ 
     PC1->XRESET
     PC4->XDCS,all low lever avalible 
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* PA4->CS */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Disable all pins */
//  GPIOA->ODR = 0xFF;  

  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI1 Config --------------------------------------------------*/ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  SPI_SSOutputCmd(SPI1, ENABLE);

  /* Enable SPI1 */			 
  SPI_Cmd(SPI1, ENABLE);

}


