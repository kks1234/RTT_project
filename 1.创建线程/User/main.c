#include "board.h"
#include "rtthread.h"


ALIGN(RT_ALIGN_SIZE)

static rt_uint8_t stack_led[1024];

struct rt_thread led1;

void led_entry(void*parameter)
{
	while(1)
	{
		rt_thread_delay(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		rt_thread_delay(500);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		
	}
	
}


ALIGN(RT_ALIGN_SIZE)

rt_thread_t led2;

void led2_entry(void*parameter)
{
	while(1)
	{
		rt_thread_delay(500);
		GPIO_SetBits(GPIOE, GPIO_Pin_5);
		rt_thread_delay(500);
		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		
	}
	
}


int main()
{
	rt_thread_init(&led1,"led",led_entry,RT_NULL,stack_led,sizeof(stack_led),3,20);
	
	rt_thread_startup(&led1);
	
	led2 = rt_thread_create("led2",led2_entry,RT_NULL,500,4,20);
	
	if(led2 != RT_NULL)
		rt_thread_startup(led2);
	else
		return -1;
	
	
}





