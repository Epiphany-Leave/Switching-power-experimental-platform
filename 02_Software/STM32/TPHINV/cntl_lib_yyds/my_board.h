



#ifndef _DPS_CNTL_LIB_H
#define _DPS_CNTL_LIB_H

#include "stm32f30x.h"
#include "system_typedef.h"
#include "pid_yyds.h"
#include "stdlib.h"
#include "math.h"
#include "dr_led.h"
#include "oled.h"
#include "stdio.h"
#include "string.h"
#include "key.h"
#include "spll_1ph_sogi.h" 
#include "arm_math.h" 
#include "SVPWM_CTR.h" 
#include "power_meas_sine_analyzer.h" 
#define MY_IRQHandler  HRTIM1_Master_IRQHandler

#define MYBOARD_ADC1  get_middle_num_adc(adc_sample_buff[15],adc_sample_buff[20],adc_sample_buff[25])
#define MYBOARD_ADC2  get_middle_num_adc(adc_sample_buff[16],adc_sample_buff[21],adc_sample_buff[26])
#define MYBOARD_ADC3  get_middle_num_adc(adc_sample_buff[17],adc_sample_buff[22],adc_sample_buff[27])
#define MYBOARD_ADC4  get_middle_num_adc(adc_sample_buff[18],adc_sample_buff[23],adc_sample_buff[28])
#define MYBOARD_ADC5  get_middle_num_adc(adc_sample_buff[0],adc_sample_buff[5],adc_sample_buff[10])
#define MYBOARD_ADC6  get_middle_num_adc(adc_sample_buff[19],adc_sample_buff[24],adc_sample_buff[29])
#define MYBOARD_ADC7  get_middle_num_adc(adc_sample_buff[2],adc_sample_buff[7],adc_sample_buff[12])
#define MYBOARD_ADC8  get_middle_num_adc(adc_sample_buff[3],adc_sample_buff[8],adc_sample_buff[13])
#define MYBOARD_ADC9  get_middle_num_adc(adc_sample_buff[4],adc_sample_buff[9],adc_sample_buff[14])
#define MYBOARD_ADC10 get_middle_num_adc(adc_sample_buff[1],adc_sample_buff[6],adc_sample_buff[11])
#define PWM_CHANNELA 0x04
#define PWM_CHANNELB 0x08
#define PWM_CHANNELC 0x01
#define PWM_CHANNELD 0x02

#define my_sin arm_sin_f32
#define my_cos arm_cos_f32

#define PWM_UPDATE_CHANNELA HRTIM_TIMERINDEX_TIMER_C
#define PWM_UPDATE_CHANNELB HRTIM_TIMERINDEX_TIMER_D
#define PWM_UPDATE_CHANNELC HRTIM_TIMERINDEX_TIMER_A
#define PWM_UPDATE_CHANNELD HRTIM_TIMERINDEX_TIMER_B

#define MYBOARDIO3_PIN  GPIO_Pin_7 
#define MYBOARDIO3_PORT  GPIOB

#define MYBOARDIO4_PIN  GPIO_Pin_6
#define MYBOARDIO4_PORT  GPIOB

#define MYBOARDIO5_PIN  GPIO_Pin_5
#define MYBOARDIO5_PORT   GPIOC

#define MYBOARDIO7_PIN  GPIO_Pin_3
#define MYBOARDIO7_PORT GPIOB

#define MYBOARDIO13_PIN  GPIO_Pin_0
#define MYBOARDIO13_PORT  GPIOC

#define MYBOARDIO14_PIN  GPIO_Pin_1
#define MYBOARDIO14_PORT  GPIOC

#define MYBOARDIO15_PIN  GPIO_Pin_2
#define MYBOARDIO15_PORT  GPIOC

#define MYBOARDIO16_PIN  GPIO_Pin_3
#define MYBOARDIO16_PORT  GPIOC

#define MYBOARDIO17_PIN  GPIO_Pin_4
#define MYBOARDIO17_PORT  GPIOC

#define MYBOARDIO21_PIN  GPIO_Pin_12
#define MYBOARDIO21_PORT   GPIOB

#define MYBOARDIO22_PIN  GPIO_Pin_13
#define MYBOARDIO22_PORT   GPIOB

#define MYBOARDIO23_PIN  GPIO_Pin_14
#define MYBOARDIO23_PORT   GPIOB

#define MYBOARDIO24_PIN  GPIO_Pin_15
#define MYBOARDIO24_PORT   GPIOB

#define MYBOARDIO27_PIN  GPIO_Pin_2
#define MYBOARDIO27_PORT  GPIOD

#define MYBOARDIO28_PIN  GPIO_Pin_12
#define MYBOARDIO28_PORT    GPIOC

#define MYBOARDIO29_PIN  GPIO_Pin_11
#define MYBOARDIO29_PORT    GPIOC

#define MYBOARDIO30_PIN  GPIO_Pin_10
#define MYBOARDIO30_PORT    GPIOC

#define MYBOARDIO32_PIN  GPIO_Pin_5
#define MYBOARDIO32_PORT    GPIOA

#define MYBOARDIO36_PIN  GPIO_Pin_4
#define MYBOARDIO36_PORT  GPIOB

#define MYBOARDIO37_PIN  GPIO_Pin_5
#define MYBOARDIO37_PORT   GPIOB

#define MYBOARDIO38_PIN  GPIO_Pin_15
#define MYBOARDIO38_PORT    GPIOC

#define MYBOARDIO39_PIN  GPIO_Pin_14
#define MYBOARDIO39_PORT  GPIOC

#define MYBOARDIO40_PIN  GPIO_Pin_13
#define MYBOARDIO40_PORT  GPIOC

#define MYBOARDIO43_PIN  GPIO_Pin_8
#define MYBOARDIO43_PORT  GPIOB

#define MYBOARDIO44_PIN  GPIO_Pin_9
#define MYBOARDIO44_PORT GPIOB

#define MYBOARDIO45_PIN  GPIO_Pin_5
#define MYBOARDIO45_PORT  GPIOA

#define MYBOARDIO49_PIN  GPIO_Pin_10
#define MYBOARDIO49_PORT GPIOB

#define MYBOARDIO50_PIN  GPIO_Pin_11
#define MYBOARDIO50_PORT GPIOB

#define MYBOARDIO53_PIN  GPIO_Pin_0
#define MYBOARDIO53_PORT  GPIOA

#define MYBOARDIO54_PIN  GPIO_Pin_1
#define MYBOARDIO54_PORT  GPIOA

#define MYBOARDIO55_PIN  GPIO_Pin_2
#define MYBOARDIO55_PORT  GPIOA

#define MYBOARDIO56_PIN  GPIO_Pin_3
#define MYBOARDIO56_PORT  GPIOA

#define MYBOARDIO57_PIN  GPIO_Pin_4
#define MYBOARDIO57_PORT  GPIOA

#define MYBOARDIO61_PIN  GPIO_Pin_8
#define MYBOARDIO61_PORT  GPIOA

#define MYBOARDIO62_PIN  GPIO_Pin_9
#define MYBOARDIO62_PORT  GPIOA

#define MYBOARDIO63_PIN  GPIO_Pin_10
#define MYBOARDIO63_PORT  GPIOA

#define MYBOARDIO64_PIN  GPIO_Pin_11
#define MYBOARDIO64_PORT  GPIOA

#define MYBOARDIO67_PIN  GPIO_Pin_9
#define MYBOARDIO67_PORT  GPIOC

#define MYBOARDIO68_PIN  GPIO_Pin_8
#define MYBOARDIO68_PORT  GPIOC

#define MYBOARDIO69_PIN  GPIO_Pin_7
#define MYBOARDIO69_PORT  GPIOC

#define MYBOARDIO70_PIN  GPIO_Pin_6
#define MYBOARDIO70_PORT  GPIOC

#define MYBOARDIO72_PIN  GPIO_Pin_12
#define MYBOARDIO72_PORT  GPIOA

#define MYBOARDIO73_PIN  GPIO_Pin_6
#define MYBOARDIO73_PORT  GPIOA

#define MYBOARDIO74_PIN  GPIO_Pin_7
#define MYBOARDIO74_PORT  GPIOA

#define MYBOARDIO78_PIN  GPIO_Pin_2
#define MYBOARDIO78_PORT GPIOB

#define MYBOARDIO79_PIN  GPIO_Pin_1
#define MYBOARDIO79_PORT GPIOB

#define MYBOARDIO80_PIN  GPIO_Pin_0
#define MYBOARDIO80_PORT GPIOB


#define KEY1 		GPIO_ReadInputDataBit(MY_KEY1_PORT,MY_KEY1_PIN) //PG4
#define KEY2    GPIO_ReadInputDataBit(MY_KEY2_PORT,MY_KEY2_PIN)	//PG5
#define KEY3    GPIO_ReadInputDataBit(MY_KEY3_PORT,MY_KEY3_PIN) //PE2

#define LED1_ON   led1_on()
#define LED2_ON   led2_on()
#define LED3_ON   led3_on()
#define LED1_OFF  led1_off()
#define LED2_OFF  led2_off()
#define LED3_OFF  led3_off()
#define LED1_TOG  led1_tog()
#define LED2_TOG  led2_tog()
#define LED3_TOG  led3_tog()

void my_system_config(void);
void my_adc_init(void);
void my_pwm_init(u32 fsw,uint8 HTIM_CHANNEL,u32 divide_num);
void usart_set(u32 baudrate);

void my_pwm_update( float duty,uint32 pwm_chennel);
void my_pwm_update_gai(float duty, uint32 pwm_chennel);
void my_pwm_fre_update(float fre,uint32 pwm_chennel);
void my_delay_update(float duty, uint32 pwm_chennel);

void Dac1_Init(void);
void PWM_ClearITPendingBit(void);
extern uint16  adc_sample_buf[10];
extern uint16  adc_sample_buff[30];

extern abc_to_alpha_beta_struct abc_to_alpha_beta_struct_U;
extern abc_to_alpha_beta_struct abc_to_alpha_beta_struct_I;
extern alpha_beta_to_dq_struct alpha_beta_to_dq_struct_U;  
extern alpha_beta_to_dq_struct alpha_beta_to_dq_struct_I;  
extern dq_to_alpha_beta_struct dq_to_alpha_beta_struct_0;
extern feedforward_and_decoupling_control_struct feedforward_and_decoupling_control_struct_0;
extern sector_struct sector_struct_0;
extern alpha_beta_to_A_B_C_struct alpha_beta_to_A_B_C_struct_0;
extern  FOC_struct FOC_struct_0;
extern SPLL_1PH_SOGI PH3_PLL;
u16 get_middle_num_adc(u16 temp1,u16 temp2,u16 temp3);
void my_board_init(void);
void main_circle_func(void);
//////////  configeration by yourself


//#define MY_PWM_FREQUENCY				40000									//PWM 开关频率,单位HZ
#define DeadTime_Value	300	//死区时间

#define MY_LED1_PIN MYBOARDIO38_PIN
#define MY_LED1_PORT MYBOARDIO38_PORT 
#define MY_LED2_PIN MYBOARDIO39_PIN
#define MY_LED2_PORT MYBOARDIO39_PORT 
#define MY_LED3_PIN MYBOARDIO40_PIN
#define MY_LED3_PORT MYBOARDIO40_PORT 

#define MY_KEY1_PIN MYBOARDIO80_PIN
#define MY_KEY1_PORT MYBOARDIO80_PORT 
#define MY_KEY2_PIN MYBOARDIO79_PIN
#define MY_KEY2_PORT MYBOARDIO79_PORT 
#define MY_KEY3_PIN MYBOARDIO78_PIN
#define MY_KEY3_PORT MYBOARDIO78_PORT 






/////////    configeration over
#endif
