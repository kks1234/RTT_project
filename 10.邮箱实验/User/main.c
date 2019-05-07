#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

u8 led_stack[1024];
struct rt_thread led_thread;
void led_thread_enter(void * param);

u8 key_stack[1024];
struct rt_thread key_thread;
void key_thread_send(void * param);

u8 mb_stack[1024];
struct rt_thread mb_thread;
void mb_thread_recv(void * param);

rt_mailbox_t mb_bock = RT_NULL;


char* mb_message =  "邮箱测试实验\r\n";

int main()
{
	mb_bock = rt_mb_create("mb_bock",10,RT_IPC_FLAG_FIFO);
	if(mb_bock != RT_NULL) {
		rt_kprintf("邮箱创建成功\r\n");
	}
	
	rt_thread_init(&led_thread,"led",
					led_thread_enter,
					RT_NULL,
					led_stack,
					sizeof(led_stack),
					5,
					20);
	
	rt_thread_startup(&led_thread);

					
	rt_thread_init(&key_thread,"key",
					key_thread_send,
					RT_NULL,
					key_stack,
					sizeof(key_stack),
					2,
					20);	
	rt_thread_startup(&key_thread);

					
	rt_thread_init(&mb_thread,"mb_recv",
					mb_thread_recv,
					RT_NULL,
					mb_stack,
					sizeof(mb_stack),
					3,
					20);
	rt_thread_startup(&mb_thread);
	
					
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


void key_thread_send(void * param)
{
	rt_err_t temp;
	while(1)
	{
		if(Key_Scan(0))
		{										/* 带不带取地址 */
			temp = rt_mb_send(mb_bock,(rt_uint32_t)mb_message);
			if(temp == RT_EOK) {
				rt_kprintf("邮箱发送成功\r\n");
			} else {
				rt_kprintf("邮箱发送失败\r\n");
			}
		}	
		rt_thread_delay(5);
	}
}


void mb_thread_recv(void * param)
{
	rt_err_t temp;
	char *s;
	while(1)
	{
		temp = rt_mb_recv(mb_bock,(rt_uint32_t*)&s,RT_WAITING_FOREVER);
		if(temp == RT_EOK) {
			rt_kprintf("邮箱内容: %s",s);
		} else {
			rt_kprintf("数据接收失败\r\n");
		}
	}
}
