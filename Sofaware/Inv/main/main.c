#include "private_Inv.h"

#include "Inv_correction.h"

#include "my_board.h"
//此处为变量自定义

#define LPF_B0	166.877556f
#define LPF_B1	-166.322444f

float sin_out;
float pwm_a;
float pwm;
float set_point_u=15;
float uout;
float iout;
float uin;
float iin;
float iref;
u8 TEST=0;
u32 time_cnt;
u32 time_cnt_all=400;
float aim_fre=50;
POWER_MEAS_SINE_ANALYZER AC_SIN;
u8 KEY_NUM=0;
u8 KEY_MODE=0;  //0是幅值，1是频率
PI voltage_pid;
PI current_pid;
void my_board_init(void);
void main_circle_func(void);

SPLL_1PH_SOGI spll;

//***************************************//
//***************************************//
//***************************************//
//***************************************//
//***************************************//
//***************************************//
//自定义函数区
void my_board_init(void)
{
    my_system_config();
    time_cnt_all=MY_PWM_FREQUENCY/aim_fre;
    delay_ms(100);

    my_adc_init();
    PI_clc(&voltage_pid);
    PI_Init(&voltage_pid,0.001f,30.0f,0.45f,-0.45f);
//	PI_Init(&voltage_pid,0.002f,0.006f,0.45f,-0.45f);
    my_pwm_init(MY_PWM_FREQUENCY,PWM_CHANNELA,ctrl_FREQUENTCY_DIV);
    voltage_pid.Output=0.0f;
    POWER_MEAS_SINE_ANALYZER_reset(&AC_SIN);
    POWER_MEAS_SINE_ANALYZER_config(&AC_SIN,MY_PWM_FREQUENCY/ctrl_FREQUENTCY_DIV,0,110,20);
    KEY_Init();
    OLED_Init();
    OLED_Clear();
    LED_Init();

    // 初始化SOGI_PLL
    SPLL_1PH_SOGI_reset(&spll);
    SPLL_1PH_SOGI_config(&spll, 50.0, MY_PWM_FREQUENCY, LPF_B0, LPF_B1); // 50Hz 电网频率，假设MY_PWM_FREQUENCY为ISR频率
	SPLL_1PH_SOGI_coeff_calc(&spll);
}

void main_circle_func(void)
{
    delay_ms(300);

    KEY_NUM = KEY_Scan(0);
    if(KEY_NUM == 1)
        KEY_MODE = !KEY_MODE;
    if(KEY_NUM == 2)
    {
        if(!KEY_MODE)
            set_point_u += 0.1f;
        else
            aim_fre += 0.1f;
    }
    if(KEY_NUM == 3)
    {
        if(!KEY_MODE)
            set_point_u -= 0.1f;
        else
            aim_fre -= 0.1f;  
    }
    if(set_point_u < 5)
        set_point_u = 5;
    if(set_point_u > 50)
        set_point_u = 50;
    
    OLED_ShowNumf(0, 0, AC_SIN.vRms, 4, 16);
    OLED_ShowNumf(0, 2, AC_SIN.iRms, 4, 16);
//    OLED_ShowNumf(0, 4, aim_fre, 4, 16);
//    OLED_ShowNumf(0, 6, set_point_u, 4, 16);
    OLED_ShowNumf(0, 4, spll.sine, 4, 16); // 显示锁相环正弦波
    OLED_ShowNumf(0, 6, spll.theta, 4, 16); // 显示锁相环相位
}

void MY_IRQHandler(void)
{
    PWM_ClearITPendingBit();
	
    uin =  MYBOARD_ADC1*BK1+BA1;
    uout= MYBOARD_ADC2*BK2+BA2;
    iout= MYBOARD_ADC4*BK4+BA4;
    iin = MYBOARD_ADC3*BK3+BA3;
    AC_SIN.i=iout;
    AC_SIN.v=uout;
    
	POWER_MEAS_SINE_ANALYZER_run(&AC_SIN);

    // 运行SOGI_PLL
    SPLL_1PH_SOGI_run(&spll, AC_SIN.v);
	
    if(time_cnt<time_cnt_all)
        time_cnt++;
    else
    {
        time_cnt=0;
        sin_out=IncPIDCal(&voltage_pid, AC_SIN.vRms, set_point_u );
    }
	
	//LPF
	static float smoothede_sin_out = 0.0f;
	smoothede_sin_out = 0.9f *smoothede_sin_out + 0.1f *sin_out;
	
//    pwm_a=0.5f+sin_out*my_sin(time_cnt*6.28f/time_cnt_all);
	pwm_a = 0.5f + smoothede_sin_out*spll.sine;

    my_pwm_update(pwm_a,PWM_UPDATE_CHANNELA);
}



