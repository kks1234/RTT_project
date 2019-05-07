#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

rt_sem_t sem_temp;
rt_mq_t  mq_temp;

rt_thread_t led_thread;
void led_thread_enter(void * param);


rt_thread_t key_thread;
void key_thread_enter(void * param);





int main()
{
	
	mq_temp = rt_mq_create("mq",1,1,RT_IPC_FLAG_FIFO);
	if(mq_temp == RT_NULL)
		return -1;
	
	led_thread = rt_thread_create("led",led_thread_enter,RT_NULL,512,5,20);
	if(led_thread != RT_NULL) {
		rt_thread_startup(led_thread);
	}

	key_thread = rt_thread_create("key",key_thread_enter,RT_NULL,512,3,20);
	if(key_thread != RT_NULL) {
		rt_thread_startup(key_thread);
	}
					
			
					
}


void led_thread_enter(void * param)
{
	while(1)
	{
		rt_thread_delay(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}
}


void key_thread_enter(void * param)
{
	rt_err_t temp  = RT_EOK;
	uint8_t numb;
	while(1)
	{
		temp = rt_mq_recv(mq_temp,&numb,sizeof(numb),RT_WAITING_FOREVER);
		if(temp == RT_EOK) {
			switch(numb) {
				case 1:
					rt_kprintf("key%d´¥·¢\r\n",numb);
					break;
				default:
					break;
			}
		}
		
		
	}
}

