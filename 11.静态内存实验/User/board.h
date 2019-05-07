#ifndef __BOARD_H__
#define __BOARD_H__


/* STM32 库函数头文件 */
#include "stm32f10x.h"

#include "led.h"
#include "key.h"
#include "usart.h"


/* 函数声明 */
void rt_hw_board_init(void);

void SysTick_Handler(void);

   




#endif  /* __BOARD_H__ */


