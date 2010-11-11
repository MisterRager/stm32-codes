 #include "stm32f10x.h"
 #include "lcd.h"
 #include "delay.h"



#define SPI_DDR  LCD_DDR 
#define SPI_PORT LCD_PORT
#define SPI_MOSI LCD_SDIN
#define SPI_SCK  LCD_SCLK

void SpiInit(void)  //SPI��ʼ������
{
	//SPI_DDR |= _BV(SPI_MOSI) | _BV(SPI_SCK);//MOSI��SCK����Ϊ���
	//SPI_PORT |= _BV(SPI_MOSI) | _BV(SPI_SCK);  
	//SPSR |= _BV(SPI2X);  //����ģʽ��fosc/2��
	//SPCR |= _BV(SPE) | _BV(MSTR);  //SPI�ӿ�ʹ�ܡ�����ģʽ��
	LCD_SDIN_HIGH() ;	
	LCD_SCLK_HIGH();
	Delay(50);
}
void SpiSendByte(uint8_t byte)  //SPI���ݷ��ͺ���
{
	uint8_t i ;
        u8 tbyte = byte ;	
	
	LCD_SCLK_HIGH( );
	
	for(i = 0 ; i < 8 ; i++)
	{
		
		if( tbyte & 0x80 )			
			LCD_SDIN_HIGH() ;			
		else	
			LCD_SDIN_LOW() ;	 
                
    LCD_SCLK_LOW() ;                	
		LCD_SCLK_HIGH( );	
                tbyte  <<= 1;		
	}	
	
}


