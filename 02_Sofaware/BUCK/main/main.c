#include "private_BUCK.h"

#include "BUCK_correction.h"


#include "my_board.h"


float pwm_a;
float set_point_u=5.2;	//设定电压

float uout;
float iout;
float uin;
float iin;
float iref;

u8 TEST=0;
u8 KEY_NUM=0;
PI voltage_pid;
PI current_pid;
//***************************************//

void my_board_init(void);
void main_circle_func(void);

//***************************************//
//***************************************//
//***************************************//
//***************************************//
//***************************************//
//自定义函数区
void my_board_init(void)
{	
    my_system_config();
    delay_ms(300);
    KEY_Init();
    OLED_Init();
    OLED_Clear();
    LED_Init();
    my_adc_init();
    PI_clc(&voltage_pid);
    PI_Init(&voltage_pid,0.001f,0.0005f,4.00f,0.0f);
    PI_Init(&current_pid,0.005f,0.002f,0.95f,0.1f);
    my_pwm_init(MY_PWM_FREQUENCY,PWM_CHANNELA,ctrl_FREQUENTCY_DIV);
}

void main_circle_func(void)
{
    delay_ms(300);
    KEY_NUM=KEY_Scan(0);
    if(KEY_NUM==1)
		set_point_u+=0.1f;
    else if(KEY_NUM==2)
		set_point_u-=0.1f;
	
    if(set_point_u<0.5f)
        set_point_u=0.5f;
    else if(set_point_u>80)
		set_point_u=80;
	
    OLED_ShowNumf(0,0,uout,4,16);
    OLED_ShowNumf(0,2,uin,4,16);
    OLED_ShowNumf(0,4,iout,4,16);
    OLED_ShowNumf(0,6,set_point_u,4,16);
	
    if(iout>4.0f)
      LED1_ON;
    else
      LED1_OFF;
	
	if(uout<4.8f)
		LED2_ON;
	else
		LED2_OFF;
}


void MY_IRQHandler(void)
{   
     PWM_ClearITPendingBit();
     uout= MYBOARD_ADC2*BK2+BA2;
     uin = MYBOARD_ADC1*BK1+BA1;
     iout= MYBOARD_ADC4*BK4+BA4;
     iin = MYBOARD_ADC3*BK3+BA3;
	 iref=IncPIDCal(&voltage_pid,uout, set_point_u) ; 
	 pwm_a=IncPIDCal(&current_pid,iout, iref) ; 
	 my_pwm_update(pwm_a,PWM_UPDATE_CHANNELA);
}

