#include "tty.h"
#if	(USE_USART1==1 )

#if(TTY_AS_USART1==1)
/*******************************************************************************
* Function Name  : fputc
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
	USART_SendData(USART1, (unsigned char) ch);
	/* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}

/*******************************************************************************
* Function Name  : fgetc
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int fgetc(FILE *f)
{
  /* Waiting for user input */
  while ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return (unsigned char)USART1->DR;
}

#endif //tty as usart1

void TTY_USART1_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure the USART1_Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : TTY_USART1_Init
* Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
*******************************************************************************/
void TTY_USART1_Init(void)
{ 	
  	USART_InitTypeDef USART_InitStructure;

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

  	/* Enable the USART1 */
  	USART_Cmd(USART1, ENABLE);
}
#endif
