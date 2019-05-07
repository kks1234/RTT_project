#include "board.h"
#include "rtthread.h"


u8 flag_key = 0;


ALIGN(RT_ALIGN_SIZE)

rt_thread_t led_thread = RT_NULL;
rt_thread_t alloc_tnread = RT_NULL;
rt_thread_t free_thread = RT_NULL;

rt_mp_t mp_test = RT_NULL;

char* p_test = RT_NULL;

void led_thread_enter(void * param);
void free_thread_enter(void * param);
void alloc_thread_enter(void * param);



int main()
{
	mp_test = rt_mp_create("mp_test",10,20);
	if(mp_test != RT_NULL) {
		rt_kprintf("内存池创建成功\r\n");
	} else {
		return -1;
	}
	
	led_thread = rt_thread_create("led",led_thread_enter,RT_NULL,512,5,20);
	if(led_thread != RT_NULL) {
		rt_thread_startup(led_thread);
	} else {
		return -1;
	}
	
	alloc_tnread = rt_thread_create("alloc",alloc_thread_enter,RT_NULL,512,3,20);
	if(alloc_tnread != RT_NULL) {
		rt_thread_startup(alloc_tnread);
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


void alloc_thread_enter(void * param)
{
	p_test = (char*)rt_mp_alloc(mp_test,0);
	if(p_test != RT_NULL) {
		rt_kprintf("内存申请成功\r\n");
	} else {
		rt_kprintf("内存申请失败\r\n");
	}
	rt_kprintf("p_test内存赋值....\r\n");
	rt_memcpy(p_test,"p_test ok",sizeof("p_test ok"));
	
	rt_kprintf("p_test赋值内容:\"%s\"\r\n",p_test);
	
	while(1) {
			rt_thread_delay(1000);
	}
}


void free_thread_enter(void * param)
{
	rt_err_t temp;
	rt_kprintf("p_test释放内存....\r\n");
	rt_mp_free(p_test);
	rt_kprintf("p_test释放内存成功\r\n\r\n");
	
	rt_kprintf("mp_test删除内存....\r\n");
	temp = rt_mp_delete(mp_test);
	if(temp == RT_EOK) {
		rt_kprintf("删除内存成功\r\n");
	} else {
		rt_kprintf("删除内存失败\r\n");	
	}
	while(1) {
		rt_thread_delay(500);
	}
}






