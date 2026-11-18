



#ifndef __LED_H
#define __LED_H

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "my_board.h"


void LED_Init(void);
void LED1_On(void);
void LED1_Off(void);
void LED1_Toggle(void);


void led1_on(void);
void led1_off(void);
void led2_on(void);
void led2_off(void);
void led3_on(void);
void led3_off(void);
void led1_tog(void);
void led2_tog(void);
void led3_tog(void);
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址 
#endif





