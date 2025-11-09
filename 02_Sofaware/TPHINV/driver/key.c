#include "key.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;


 
  GPIO_InitStructure.GPIO_Pin = MY_KEY1_PIN; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(MY_KEY1_PORT, &GPIO_InitStructure);//初始化GPIOE2,3,4


	GPIO_InitStructure.GPIO_Pin = MY_KEY2_PIN;//WK_UP对应引脚PA0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//下拉
  GPIO_Init(MY_KEY2_PORT, &GPIO_InitStructure);//初始化GPIOA0
	 
  GPIO_InitStructure.GPIO_Pin = MY_KEY3_PIN;//WK_UP对应引脚PA0
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//下拉
  GPIO_Init(MY_KEY3_PORT, &GPIO_InitStructure);//初始化GPIOA0
 
} 

u8 KEY_Scan(u8 mode)
{	 
	if(KEY1==0||KEY2==0||KEY3==0)
	{
		delay_ms(10);
		     if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
	  else return 0;    
  }
	return 0;
}














