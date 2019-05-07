#include "usart.h"




void usart_init(u32 boud)
{
	USART_InitTypeDef USART_InitTypeStruct;
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitTypeStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	USART_InitTypeStruct.USART_BaudRate = boud;
	USART_InitTypeStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitTypeStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitTypeStruct.USART_Parity = USART_Parity_No;
	USART_InitTypeStruct.USART_StopBits = USART_StopBits_1;
	USART_InitTypeStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitTypeStruct);
	
	USART_Cmd(USART1,ENABLE);
	
}




