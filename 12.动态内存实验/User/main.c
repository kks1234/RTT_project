#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

rt_thread_t led_thread = RT_NULL;
rt_thread_t malloc_tnread = RT_NULL;
rt_thread_t free_thread = RT_NULL;



char* p_test = RT_NULL;

void led_thread_enter(void * param);
void free_thread_enter(void * param);
void malloc_thread_enter(void * param);



int main()
{

	
	led_thread = rt_thread_create("led",led_thread_enter,RT_NULL,512,5,20);
	if(led_thread != RT_NULL) {
		rt_thread_startup(led_thread);
	} else {
		return -1;
	}
	
	malloc_tnread = rt_thread_create("alloc",malloc_thread_enter,RT_NULL,512,3,20);
	if(malloc_tnread != RT_NULL) {
		rt_thread_startup(malloc_tnread);
	} else {
		return -1;
	}
					
	
	free_thread = rt_thread_create("free",free_thread_enter,RT_NULL,512,4,20);
	if(free_thread != RT_NULL) {
		rt_thread_startup(free_thread);
	} else {
		return -1;
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


void malloc_thread_enter(void * param)
{
	p_test = rt_malloc(100);
	if(p_test != RT_NULL) {
		rt_kprintf("内存申请成功\r\n");
	} else {
		rt_kprintf("内存申请失败\r\n");
	}
	rt_kprintf("p_test内存赋值....\r\n");
	rt_memcpy(p_test,"ptest ok",sizeof("ptest ok"));

	rt_kprintf("p_test赋值内容:\"%s\"\r\n",p_test);
	
	while(1) {
			rt_thread_delay(1000);
	}
}


void free_thread_enter(void * param)
{
	rt_kprintf("p_test释放内存....\r\n");
	rt_free(p_test);
	rt_kprintf("p_test释放内存成功\r\n\r\n");
	
	while(1) {
		rt_thread_delay(500);
	}
}






