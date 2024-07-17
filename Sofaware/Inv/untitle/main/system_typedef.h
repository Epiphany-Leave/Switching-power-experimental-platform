






#ifndef __SYSTEM_TYPEDEF_H
#define __SYSTEM_TYPEDEF_H

//===========数据类型定义=========//
#ifndef USER_DATA_TYPES
#define USER_DSTS_TYPES

typedef char						int8;
typedef	short						int16;
typedef int							int32;
typedef long						int64;
typedef unsigned char		uint8;
typedef unsigned short	uint16;
typedef unsigned int		uint32;
typedef	unsigned long		uint64;
typedef float						float32;
typedef double  				float64;

#endif



#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x4001080C    
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40010C0C    
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x4001100C    
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x4001140C    
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x4001180C    
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40011A0C       
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40011E0C       
  
#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40010808    
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40010C08    
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40011008    
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40011408    
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40011808    
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40011A08    
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40011E08 

//============时钟频率============//
#define	SYSCLK			64000000000
#define HCLK				64000000000
#define PCLK1				32000000000
#define	PCLK2				64000000000
#define PLLCLK			128000000000
#define	fHRTIM			128000000000

void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(unsigned int addr);	//设置堆栈地址 


#endif
