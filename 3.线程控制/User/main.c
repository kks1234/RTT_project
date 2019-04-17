#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

u8 led_stack[1024];
struct rt_thread led_thread;
void led_thread_enter(void * param);

u8 key_stack[1024];
struct rt_thread key_thread;
void key_thread_enter(void * param);


int main()
{
	rt_thread_init(&led_thread,"led",
					led_thread_enter,
					RT_NULL,
					led_stack,
					sizeof(led_stack),
					3,
					20);
	
	rt_thread_startup(&led_thread);

					
	rt_thread_init(&key_thread,"key",
					key_thread_enter,
					RT_NULL,
					key_stack,
					sizeof(key_stack),
					2,
					20);				
	
	rt_thread_startup(&key_thread);
					
}


void led_thread_enter(void * param)
{
	while(1)
	{
		rt_thread_delay(500);
		rt_kprintf("off  led\n");
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(500);
		rt_kprintf("on led\n");
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}
}


void key_thread_enter(void * param)
{
	rt_err_t t;
	while(1)
	{
		if(Key_Scan(0))
		{
			flag_key = ~flag_key;
			if(flag_key)
			{
				t = rt_thread_suspend(&led_thread);
				   if(RT_EOK == t)
					{
						rt_kprintf("挂起LED1线程成功！\n");
					}
			}
			else
			{
				t = rt_thread_resume(&led_thread);
				   if(RT_EOK == t)
					{
						rt_kprintf("恢复LED1线程成功！\n");
					}
			}
		}	
		rt_thread_delay(5);
	}
}

