

#include "dr_led.h"


void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin		= MY_LED1_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MY_LED1_PORT, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin		= MY_LED2_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MY_LED2_PORT, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin		= MY_LED3_PIN;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MY_LED3_PORT, &GPIO_InitStructure);
}
	


void led1_on(void)
{
	MY_LED1_PORT->BSRR = MY_LED1_PIN;
}
void led1_off(void)
{
	MY_LED1_PORT->BRR = MY_LED1_PIN;
}
void led1_tog(void)
{
	  MY_LED1_PORT->ODR ^= MY_LED1_PIN;
}


void led2_on(void)
{
	MY_LED2_PORT->BSRR = MY_LED2_PIN;
}
void led2_off(void)
{
	MY_LED2_PORT->BRR = MY_LED2_PIN;
}
void led2_tog(void)
{
	  MY_LED2_PORT->ODR ^= MY_LED2_PIN;
}

void led3_on(void)
{
	MY_LED3_PORT->BSRR = MY_LED3_PIN;
}
void led3_off(void)
{
	MY_LED3_PORT->BRR = MY_LED3_PIN;
}
void led3_tog(void)
{
	  MY_LED3_PORT->ODR ^= MY_LED3_PIN;
}

