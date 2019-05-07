#include "key.h"
#include "rtthread.h"


uint8_t numb1 = 1;

extern rt_mq_t  mq_temp;

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	EXTI_InitTypeDef EXTI_InitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitTypeStruct);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel =  EXTI0_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	
}


u8 Key_Scan(u8 mode)
{
	static u8 flag = 1;
	if(mode) flag = 1;
	
	if(flag && (WEKUP == 1) )
	{
		//rt_thread_delay(5);
		flag = 0;
		if(WEKUP == 1)
		{
			return 1;
		}	
	}else if(WEKUP == 0) flag = 1;
	
	return 0;	
}



void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET) {
		
		rt_mq_send(mq_temp,&numb1,sizeof(numb1));
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	
}


