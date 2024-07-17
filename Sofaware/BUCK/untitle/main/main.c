#include "private_inv.h"

#include "inv_correction.h"

#include "my_board.h"
float K1 = 0.024169921875f;
float K2 = 0.001611328125f;
float A1 = -3.3f;
float K3 = 0.024169921875f;
float A2 = -49.5f;

u32 cnt;
u32 cnt_all = 400;
SPLL_1PH_SOGI PH3_PLL;
PI pid_voltage_loop;
PI pid_Id_loop;
PI pid_Iq_loop;
u8 KEY_NUM = 0;
u8 KEY_MODE = 0; //0是幅值，1是频率
float ua, UB, UC;
float UA, ub, uc;
float UBUS;
float ia, ib, ic;
void my_board_init(void);
void main_circle_func(void);
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

//    OLED_Init();
//    OLED_Clear();
//    KEY_Init();
//    LED_Init();


    my_adc_init();
    my_pwm_init(MY_PWM_FREQUENCY, PWM_CHANNELA  | PWM_CHANNELB | PWM_CHANNELC| PWM_CHANNELD, ctrl_FREQUENTCY_DIV);

    OLED_Init();
    OLED_Clear();
    KEY_Init();
    LED_Init();



}
void main_circle_func(void)
{
//      delay_ms(300);
    KEY_NUM = KEY_Scan(0);
    OLED_ShowNumf(0, 0, KEY_NUM, 4, 16);
    OLED_ShowNumf(0, 2, MYBOARD_ADC2, 4, 16);
    OLED_ShowNumf(0, 4, MYBOARD_ADC3, 4, 16);
    OLED_ShowNumf(0, 6, MYBOARD_ADC4, 4, 16);
}


void MY_IRQHandler(void)
{
    PWM_ClearITPendingBit();
    UBUS = MYBOARD_ADC1 * BK1 + BA1;
    ua = MYBOARD_ADC2 * BK2 + BA2;
    ub = MYBOARD_ADC3 * BK3 + BA3;
    uc = MYBOARD_ADC4 * BK4 + BA4;
    ia = MYBOARD_ADC5 * BK5 + BA5;
    ib = MYBOARD_ADC6 * BK6 + BA6;
    ic = MYBOARD_ADC7 * BK7 + BA7;
    my_pwm_update(0.5f, PWM_UPDATE_CHANNELA);
    my_pwm_update(0.5f, PWM_UPDATE_CHANNELB);
    my_pwm_update(0.5f, PWM_UPDATE_CHANNELC);
    my_pwm_update(0.5f, PWM_UPDATE_CHANNELD);

}



