
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stdlib.h"	
#include "system_typedef.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(char x,char y,char t);
void OLED_Fill(char x1,char y1,char x2,char y2,char dot);
void OLED_ShowChar(char x,char y,char chr,char Char_Size);
void OLED_ShowNum(char x,char y,int num,char len,char size);
void OLED_ShowString(char x,char y, char *p,char Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(char x,char y,char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_ShowNum_0(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);
void OLED_ShowNumf(unsigned char x,unsigned char y,float num,unsigned char len,unsigned char size);
void IIC_Wait_Ack(void);
#endif  
	 



