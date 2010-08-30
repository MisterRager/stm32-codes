#include <stm32f10x_lib.h>
#include "tty.h"


/* Usart functions ---------------------------------  ------------------------*/
/*******************************************************************************
* Function Name  : SerialPutChar
* Description    : Print a character on the HyperTerminal
* Input          : - c: The character to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void SerialPutChar(u8 c)
{
  	USART_SendData(USART1, c);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}




/*******************************************************************************
* Function Name  : Serial_PutString
* Description    : Print a string on the HyperTerminal
* Input          : - s: The string to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void Serial_PutString(u8 *s)
{
  	while (*s != '\0')
  	{
    	SerialPutChar(*s);
    	s ++;
  	}
}
/*******************************************************************************
* Function Name  : USART1_Init
* Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
* Input          : None
* Output         : None
* Return         : None
* Note			 : You have to run RCC_Configuration() before calling this function
*******************************************************************************/
void USART1_Init(void)
{
		
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 	\
											  |	RCC_APB2Periph_GPIOB	\
											 |	RCC_APB2Periph_GPIOC	\
											  |	RCC_APB2Periph_GPIOD	\
											 |	RCC_APB2Periph_TIM1 	\
											 |	RCC_APB2Periph_GPIOE	\
											 | RCC_APB2Periph_AFIO  \
                       | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);


  	/* Clock configuration -------------------------------------------------------*/

  	/* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  	/* Configure the USART1_Tx as Alternate function Push-Pull */
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Configure the USART1_Rx as input floating */
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* USART1 configuration ------------------------------------------------------*/
  	/* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 115200;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure the USART1 */
  	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 interrupt */
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1,USART_IT_TXE,ENABLE);


  	/* Enable the USART1 */
  	USART_Cmd(USART1, ENABLE);
}

void USART2_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;

  	/* Clock configuration -------------------------------------------------------*/

  	/* Configure the GPIO ports( USART2 Transmit and Receive Lines) */
  	/* Configure the USART2_Tx as Alternate function Push-Pull */
  	/* Configure USART2_Tx as alternate function push-pull */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	/* Configure USART2_Rx as input floating 	*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  


  	/* USART2 configuration ------------------------------------------------------*/
  	/* USART2 configured as follow:
        - BaudRate = 960000 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure the USART2 */
  	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART2 interrupt */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);
}

void USART3_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;

  	/* Clock configuration -------------------------------------------------------*/

  	/* Configure the GPIO ports( USART3 Transmit and Receive Lines) */
  	/* Configure the USART3_Tx as Alternate function Push-Pull */
  	/* Configure USART3_Tx as alternate function push-pull */
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);


  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	/* Configure USART3_Rx as input floating 		*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  


  	/* USART3 configuration ------------------------------------------------------*/
  	/* USART3 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure the USART3 */
  	USART_Init(USART3, &USART_InitStructure);

	/* Enable USART3 interrupt */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  	/* Enable the USART3 */
  	USART_Cmd(USART3, ENABLE);
}

void UART4_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;

  	/* Clock configuration -------------------------------------------------------*/

  	/* Configure the GPIO ports( UART4 Transmit and Receive Lines) */
  	/* Configure the UART4_Tx as Alternate function Push-Pull */
  	/* Configure UART4_Tx as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

  	/* Configure UART4_Rx as input floating */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);  


  	/* UART4 configuration ------------------------------------------------------*/
  	/* UART4 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure the UART4 */
  	USART_Init(UART4, &USART_InitStructure);

	/* Enable UART4 interrupt */
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

  	/* Enable the UART4 */
  	USART_Cmd(UART4, ENABLE);
}

void UART5_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

  	/* Clock configuration -------------------------------------------------------*/

  	/* Configure the GPIO ports( UART5 Transmit and Receive Lines) */
  	/* Configure the UART5_Tx as Alternate function Push-Pull */
  	/* Configure UART5_Tx as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

  	/* Configure UART5_Rx as input floating */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  


  	/* UART5 configuration ------------------------------------------------------*/
  	/* UART5 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
  	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure the UART5 */
  	USART_Init(UART5, &USART_InitStructure);

	/* Enable UART5 interrupt */
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

  	/* Enable the UART5 */
  	USART_Cmd(UART5, ENABLE);
}

