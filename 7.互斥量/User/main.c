#include "board.h"
#include "rtthread.h"


ALIGN(RT_ALIGN_SIZE)

/* �߳̿��ƿ� */
rt_thread_t send = RT_NULL;
rt_thread_t recv = RT_NULL;
rt_thread_t led	 = RT_NULL;

/* ������ */
rt_mutex_t mutex_text;

u32 val1 = 0, val2 = 0;



/* �̺߳��� */
void send_data_enter(void* param);
void recv_data_enter(void* param);
void led_enter(void* param);


int main()
{
	mutex_text = rt_mutex_create("mutex_text",RT_IPC_FLAG_FIFO);
	if(mutex_text == RT_NULL) {
		return -1;
	} else {
		rt_kprintf("�����������ɹ�\r\n");
	}
	send = rt_thread_create("send",send_data_enter,RT_NULL,512,2,20);
	if(send != RT_NULL) {
		rt_thread_startup(send);
	} else {
		rt_kprintf("�̴߳���ʧ��\r\n");
	}
	
	recv = rt_thread_create("recv",recv_data_enter,RT_NULL,512,3,20);
	if(recv != RT_NULL) {
		rt_thread_startup(recv);
	} else {
		rt_kprintf("�̴߳���ʧ��\r\n");
	}
	
	led = rt_thread_create("led",led_enter,RT_NULL,512,5,20);
	if(led != RT_NULL) {
		rt_thread_startup(led);
	} else {
		rt_kprintf("�����߳�ʧ��\r\n");
	}
}




void send_data_enter(void* param)
{
	while(1) {
		rt_mutex_take(mutex_text,RT_WAITING_FOREVER);
		val1 ++;
		rt_thread_delay(100);
		val2 ++;
		rt_mutex_release(mutex_text);
		
		rt_thread_yield(); //����ʣ��ʱ��Ƭ,����һ���߳��л�
	}
	
}
void recv_data_enter(void* param)
{
	while(1) {
		rt_mutex_take(mutex_text,RT_WAITING_FOREVER);
		if(val1 == val2) {
			rt_kprintf("Successful\r\n");
		} else {
			rt_kprintf("Fail\r\n");
		}
		rt_mutex_release(mutex_text);
		rt_thread_delay(1000);
	}
	
}


void led_enter(void* param)
{
	while(1) {
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(300);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		rt_thread_delay(300);		
	}
}



