#include "usart.h"
 
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
 * Function Name  : IAP_Init 
 * Description    : Initialize the IAP: Configure RCC, USART and GPIOs. 
 * Input          : None 
 * Output         : None 
 * Return         : None 
 * Note                   : You have to run RCC_Configuration() before calling this function 
 *******************************************************************************/ 
 void USART1_Init(void) 
 { 
   GPIO_InitTypeDef GPIO_InitStructure; 
   USART_InitTypeDef USART_InitStructure; 
  
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
   USART_InitStructure.USART_BaudRate = 9600; 
   USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
   USART_InitStructure.USART_StopBits = USART_StopBits_1; 
   USART_InitStructure.USART_Parity = USART_Parity_No; 
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  
   /* Configure the USART1 */ 
   USART_Init(USART1, &USART_InitStructure); 
  
   /* Enable the USART1 */ 
   USART_Cmd(USART1, ENABLE); 
 } 

/* usart.c end */
