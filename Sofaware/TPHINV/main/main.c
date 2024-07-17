#include "private_TPHINV.h"

#include "TPHINV_correction.h"

#include "my_board.h"
//此处为变量自定义

float pwm_a;
float set_point_u=20;
float uout;
float iout;
float uin;
float iin;
u8 TEST=0;
u8 KEY_NUM=0;
PI voltage_pid;
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
    delay_ms(300);

	usart_set(115200);
    my_adc_init();
  
       ELAB_initialize();
       KEY_initialize();
   
//    my_pwm_init(MY_PWM_FREQUENCY,PWM_CHANNELA*PWMA_ENA|PWM_CHANNELB*PWMB_ENA|PWM_CHANNELC*PWMC_ENA|PWM_CHANNELD*PWMD_ENA,ctrl_FREQUENTCY_DIV);
   KEY_Init();
   OLED_Init();
      LED_Init();
   OLED_Clear();
	
	my_pwm_init(MY_PWM_FREQUENCY,PWM_CHANNELA*PWMA_ENA|PWM_CHANNELB*PWMB_ENA|PWM_CHANNELC*PWMC_ENA|PWM_CHANNELD*PWMD_ENA,ctrl_FREQUENTCY_DIV);
}
  void main_circle_func(void)
  {
          delay_ms(delay_time);
      KEY_NUM=KEY_Scan(0);
      if(KEY_NUM==1)
      {
    rtU_KEY.KEY_IN1=1;
    rtU_KEY.KEY_IN2=0;
    rtU_KEY.KEY_IN3=0;
      }
       if(KEY_NUM==2)
             {
    rtU_KEY.KEY_IN1=0;
    rtU_KEY.KEY_IN2=1;
    rtU_KEY.KEY_IN3=0;
      }
      if(KEY_NUM==3)
      {
    rtU_KEY.KEY_IN1=0;
    rtU_KEY.KEY_IN2=0;
    rtU_KEY.KEY_IN3=1;
      }
    
      OLED_ShowNumf(0,0,rtY_ELAB.signal1,4,16);
      OLED_ShowNumf(0,2,rtY_ELAB.signal2,4,16);
      OLED_ShowNumf(0,4,rtY_ELAB.signal3,4,16);
      OLED_ShowNumf(0,6,rtY_ELAB.signal4,4,16);
      if(rtY_ELAB.signal1b)
          LED1_ON;
      else
        LED1_OFF;
      
      if(rtY_ELAB.signal2b)
          LED2_ON;
      else
        LED2_OFF;
      
      if(rtY_ELAB.signal3b)
          LED3_ON;
      else
        LED3_OFF;
  }


void MY_IRQHandler(void)
{
      PWM_ClearITPendingBit();
     rtU_ELAB.KEY_INPUT_1= rtY_KEY.KEY_OUT_1;
     rtU_ELAB.KEY_INPUT_2= rtY_KEY.KEY_OUT_2;
     rtU_ELAB.KEY_INPUT_3= rtY_KEY.KEY_OUT_3;
     get_ADC_num
     KEY_step();
     ELAB_step();
#if PWMA_MODE==1
  my_pwm_update(rtY_ELAB.PWM_A ,PWM_UPDATE_CHANNELA);
#elif PWMA_MODE==2
my_pwm_fre_update(rtY_ELAB.PWM_A ,PWM_UPDATE_CHANNELA);
#elif PWMA_MODE==3
my_pwm_delay_update(rtY_ELAB.PWM_A ,PWM_UPDATE_CHANNELA);
#endif
#if PWMB_MODE==1
//  my_pwm_update(rtY_ELAB.PWM_B ,PWM_UPDATE_CHANNELB);
	my_pwm_update_gai(rtY_ELAB.PWM_B ,PWM_UPDATE_CHANNELB);
#elif PWMB_MODE==2
my_pwm_fre_update(rtY_ELAB.PWM_B ,PWM_UPDATE_CHANNELB);
#elif PWMB_MODE==3
my_pwm_delay_update(rtY_ELAB.PWM_B ,PWM_UPDATE_CHANNELB);
#endif
#if PWMC_MODE==1
//  my_pwm_update(rtY_ELAB.PWM_C ,PWM_UPDATE_CHANNELC);
my_pwm_update_gai(rtY_ELAB.PWM_C ,PWM_UPDATE_CHANNELC);
#elif PWMC_MODE==2
my_pwm_fre_update(rtY_ELAB.PWM_C ,PWM_UPDATE_CHANNELC);
#elif PWMC_MODE==3
my_pwm_delay_update(rtY_ELAB.PWM_C ,PWM_UPDATE_CHANNELC);
#endif
#if PWMD_MODE==1
  my_pwm_update(rtY_ELAB.PWM_D ,PWM_UPDATE_CHANNELD);
#elif PWMD_MODE==2
my_pwm_fre_update(rtY_ELAB.PWM_D ,PWM_UPDATE_CHANNELD);
#elif PWMD_MODE==3
my_pwm_delay_update(rtY_ELAB.PWM_D ,PWM_UPDATE_CHANNELD);
#endif
}




