#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

/* 线程控制指针 */
rt_thread_t receive_thread = RT_NULL;
rt_thread_t send_thread = RT_NULL;
rt_thread_t led_thread = RT_NULL;

/* 线程函数声明 */
void receive_thread_enter(void * param);
void send_thread_enter(void * param);
void led_thread_enter(void* param);

/* 消息队列 */
rt_mq_t test_mq = RT_NULL;


int main()
{
	
	test_mq = rt_mq_create("test_mq",
							10,
							20,
							RT_IPC_FLAG_FIFO);
	if(test_mq != RT_NULL)
		rt_kprintf("消息队列创建成功\r\n");
	
	receive_thread = rt_thread_create("receive_thread",
										receive_thread_enter,
										RT_NULL,
										512,
										10,
										20); 
	if(receive_thread != RT_NULL)
		rt_thread_startup(receive_thread);
	else
		return -1;
	
	send_thread = rt_thread_create("send_thread",
										send_thread_enter,
										RT_NULL,
										512,
										9,
										20); 				
				
	if(send_thread != RT_NULL)
		rt_thread_startup(send_thread);
	else
		return -1;
	
	
	led_thread = rt_thread_create("led_thread_enter",
										led_thread_enter,
										RT_NULL,
										512,
										20,
										20); 				
				
	if(led_thread != RT_NULL)
		rt_thread_startup(led_thread);
	else
		return -1;
	
	
}








void receive_thread_enter(void * param)
{
	rt_err_t uwret = RT_EOK;
	uint32_t r_queue;
	/* 线程都是一个无限循环,不能返回 */
	while(1) {
		/* 队列接收,等待时间为一直等待 */
		uwret = rt_mq_recv(test_mq,&r_queue,sizeof(r_queue),RT_WAITING_FOREVER);
		if(uwret == RT_EOK) {
			rt_kprintf("本次接收到的数据是 %d\n",r_queue);
		} else {
			rt_kprintf("接收数据失败, 错误代码 0x%lx\n",uwret);
		}
		
		rt_thread_delay(200);
		
	}
}


void send_thread_enter(void * param)
{
	rt_err_t uwret = RT_EOK;
	static uint32_t t = 0;
	while(1)
	{
		if(Key_Scan(0) == 1)
		{
			t++;
			if(t > 100)
				t = 0;
			uwret = rt_mq_send(test_mq,&t,sizeof(t));
			
			if(uwret != RT_EOK) {
				rt_kprintf("消息发送失败\r\n");
			}
			
		}	
		rt_thread_delay(20);
	}
}



void led_thread_enter(void* param)
{
	while(1) {
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(300);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(300);			
	}
}






