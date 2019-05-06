#include "board.h"
#include "rtthread.h"


ALIGN(RT_ALIGN_SIZE)

rt_timer_t 		timer1 = RT_NULL;
rt_timer_t 		timer2 = RT_NULL;

uint32_t 		numb1 = 0;
uint32_t 		numb2 = 0;


void timer1_callback(void* parameter);
void timer2_callback(void* parameter);



int main()
{
	timer1 = rt_timer_create("timer1",
								timer1_callback,
								RT_NULL,
								5000,
								RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_SOFT_TIMER);
	if(timer1 != RT_NULL) {
		rt_timer_start(timer1);
	}
	
	timer2 = rt_timer_create("timer2",
								timer2_callback,
								RT_NULL,
								1000,
								RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);
	if(timer2 != RT_NULL) {
		rt_timer_start(timer2);
	}
	
	
}


void timer1_callback(void* parameter)
{
	rt_tick_t tick_curr;
	
	numb1 ++;
	
	tick_curr = rt_tick_get();
	
	rt_kprintf("timer1_callback()函数执行 %d 次\r\n",numb1);
	rt_kprintf("滴答计数器值= %d\r\n",tick_curr);
	
}



void timer2_callback(void* parameter)
{
	rt_tick_t tick_curr;
	
	numb2 ++;
	
	tick_curr = rt_tick_get();
	
	rt_kprintf("timer2_callback()函数执行 %d 次\r\n",numb2);
	rt_kprintf("滴答计数器值= %d\r\n",tick_curr);
	
	
}


