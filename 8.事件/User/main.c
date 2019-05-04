#include "board.h"
#include "rtthread.h"

#define k0_event (0x01<<0)


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

u8 led_stack[1024];
struct rt_thread led_thread;
void led_thread_enter(void * param);

u8 key_stack[1024];
struct rt_thread key_thread;
void key_thread_enter(void * param);


struct rt_event event_text;

int main()
{
	rt_event_init(&event_text,"event_text",RT_IPC_FLAG_FIFO);
	
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
	rt_uint32_t recved = 0;
	while(1)
	{
		rt_event_recv(&event_text,
						k0_event,
						RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,
						RT_WAITING_FOREVER,
						&recved);
		if(recved == k0_event)
			flag_key = ~flag_key;
		
		if(flag_key) {
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
		} else {
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		rt_thread_delay(5);
	}
}


void key_thread_enter(void * param)
{
	while(1)
	{
		if(Key_Scan(0))
		{
			rt_kprintf("Key ±»µã»÷\r\n");
			rt_event_send(&event_text,k0_event);
		}	
		rt_thread_delay(5);
	}
}

