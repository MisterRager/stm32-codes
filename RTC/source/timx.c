/******************************************************************************
 * Function Name  : TM2_Configuration
 * Description    : Timer2 configuration: overflow interrupt
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void TIMx_Configuration(void)
{
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef			TIM_OCInitStruct;

	// Enable TIMx clock: TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  


	// Time base configuration
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 35999; //CK_CNT=fck_psc/(TIMx_PSC+1),
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0; //TIMx_CR1->CKD
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIMx_CR1->CMS.
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	// Output compare active mode configuration: channel1
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Active;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 500;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);

	// Enable or disable the TIMx peripheral Preload rigister on CCR1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

	// Enable or disable the TIMx peripheral register on ARR
	TIM_ARRPreloadConfig(TIM2, ENABLE);

	// Enable or disable the specified TIMx interrupts
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

	// Enable or disable the specified TIMx peripheral
	TIM_Cmd(TIM2, ENABLE);
}
