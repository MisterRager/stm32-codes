//******************************************************************************
//
//
//
//
//
//
//******************************************************************************


// *****************************************************************************
// Description: Includes
// *****************************************************************************
#include "stm32f10x_lib.h"



// *****************************************************************************
// Description: Private defines
// *****************************************************************************
#define VECT_TAB_FLASH



// *****************************************************************************
// Description: Private variables
// *****************************************************************************

// *****************************************************************************
// Description: Private functions prototypes
// *****************************************************************************
extern void RCC_Configuration(void); 
extern void NVIC_Configuration(void);
extern void GPIO_Configuration(void);
extern void SysTick_Configuration(void);
extern void SysTick_Start(void);
extern void USART1_Init(void);
unsigned int sig=0;





// *****************************************************************************
// Function Name  : main
// Description    : Main program.
// Input          : None
// Output         : None
// Return         : None
// *****************************************************************************
int main(void)
{
#ifdef DEBUG
	debug();
#endif
		int led=0;
		led=0;
    //  System clock configuration
    RCC_Configuration();    
    // Nested Vector Interrupt Controller configuration
    NVIC_Configuration();   
    // General Purpose I/O default configration
    GPIO_Configuration();
		SysTick_Configuration();
		SysTick_Start();
		USART1_Init();
		//GPIO_SetBits(GPIOE, GPIO_Pin_3);
    while(1)
    {	
			if(sig==0)
					GPIO_SetBits(GPIOB, GPIO_Pin_5);
			else GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}


#ifdef  DEBUG
void assert_failed(u8* file, u32 line)
{ 
  	// User can add his own implementation to report the file name and line number,
  	//   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)

  	while (1)
  	{

  	}
}
#endif

// ******************************** END OF FILE ********************************

