#include "F28x_Project.h"

#include "timer.h"
#include "epwm.h"
#include "hrpwm.h"
#include "SFO_V8.h"
#include "adc.h"
#include "sci.h"
#include "tz.h"

/*  */
#include "analog.h"

/**
 * main.c
 */

/* SFO相关内容 */
#define PWM_CH 5
#define STATUS_SUCCESS 1
#define STATUS_FAIL    0
volatile struct EPWM_REGS *ePWM[PWM_CH]={0, &EPwm1Regs,&EPwm2Regs,&EPwm3Regs,&EPwm4Regs};
Uint16 status = SFO_INCOMPLETE;
extern uint32_t MEP_ScaleFactor;

/* 全局变量定义区 时基变量 */
unsigned char flag_1ms      = 0;
unsigned char flag_10ms     = 0;
unsigned char flag_100ms    = 0;
unsigned char flag_1s       = 0;
unsigned char cnt_1ms       = 0;
unsigned char cnt_10ms      = 0;
unsigned char cnt_100ms     = 0;
unsigned char cnt_1s        = 0;

/* SPWM 测试相关变量 */
Uint16 sine_index = 0;
Uint32 duty = 0;
float Duty;

/* ADC相关变量 */
volatile Uint16 A0,A1,A2,A3,C0,C1,C2,C3;
volatile Uint32 TEMP;
/* RMS&Inter */
//static Inert_t filt;
//static Rms_t   rms;

// 中断声明
__interrupt void CPUTIMER0_ISR(void);

int main(void)
{

    InitSysCtrl();
    DELAY_US(30);   // 完全上电
    InitCpuTimers();
    InitGpio();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    // 指向shell Interrupt的指针初始化PIE向量表
    InitPieVectTable();

    // 修改时钟
    EALLOW;
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0; // 提高慢速时钟为120MHz  用于提高通信速度
    EDIS;

    Timer0Init(100, 1000);
    ADCA_Init();
//    SCIA_Init(1152000, 10);
//    TZ_Cmpss_1_Init(0, 0, 1); // 测试TZ功能

//    HRPWM1_Init(1000);
    EPwm_Init(5000);

    // 中断注册
    EALLOW;
    PieVectTable.TIMER0_INT = &CPUTIMER0_ISR;
    EDIS;

    /* GPIO应用 
    // GPIO_SetupPinMux(31, GPIO_MUX_CPU1, 0);
    // GPIO_SetupPinOptions(31, GPIO_MUX_CPU1, GPIO_PUSHPULL);

    // GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; // 输出
    // GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0; // 输入

    // GpioCtrlRegs.GPAGMUX1.bit.GPIO32 = 0; // 不复用，普通IO

    // GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1; // 上拉失能

    // GpioDataRegs.GPASET.bit.GPIO31 = 1; // 拉高
    // GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; // 拉低
     */

    // --- 配置 GPIO23 为普通输出IO ---
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;   // 普通IO
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;    // 输出
    // GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;    // 上拉失能（可选）
    GpioDataRegs.GPASET.bit.GPIO23 = 1;
    EDIS;

    // 选择中断向量表
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // X选中(Cpu定时器)
    IER |= M_INT1;                     // Y选中(Cpu定时器)
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // 没有这句，进不去中断

    // 启用全局中断（INTM）和实时中断（DBGM）
    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM

    // SFO校验
    status = SFO_INCOMPLETE;
    status = SFO();             // 每5s/10s/1min执行一次
    if(status == SFO_ERROR)
    {
        ESTOP0;
    }
     EPwm1Regs.CMPA.bit.CMPA = 1250; // A:50%
     EPwm1Regs.CMPB.bit.CMPB = 1250; // B:50%

    while(1)
    {
        if(flag_1ms)
        {
            flag_1ms = 0;cnt_1ms++;if(cnt_1ms == 10){cnt_1ms = 0;flag_10ms = 1;}
            /*1ms时基代码编写区*/


            /*1ms时基代码结束*/
        }
        if(flag_10ms)   
        {
            flag_10ms = 0;cnt_10ms++;if(cnt_10ms == 10){cnt_10ms = 0;flag_100ms = 1;}
            /*10ms时基代码编写区*/

            /*10ms时基代码结束*/
        }
        if(flag_100ms)
        {
            flag_100ms = 0;cnt_100ms++;if(cnt_100ms == 10){cnt_100ms = 0;flag_1s = 1;}
            /*100ms时基代码编写区*/

            /*100ms时基代码结束*/
        }       
        if(flag_1s)
        {
            flag_1s = 0;
            /*1s时基代码编写区*/
            GpioDataRegs.GPATOGGLE.bit.GPIO23 = 1; // 翻转LED
            
            status = SFO_INCOMPLETE;
            while(status == SFO_INCOMPLETE)
            {
                status = SFO();
            }
            if(status == 2)
            {
                /* 可以写处理，如禁用HRPWM */
                ESTOP0;
            }
            /*1s时基代码结束*/
        }      
        
    }
}

__interrupt void adcA1ISR()
{
    A0 = AdcaResultRegs.ADCRESULT0;
    A1 = AdcaResultRegs.ADCRESULT1;
    A2 = AdcaResultRegs.ADCRESULT2;
    A3 = AdcaResultRegs.ADCRESULT3;
    // 更新 Rms 和 Inert 类的实例
//    rms.next(A0);  // 将采样值传入 Rms 类计算 RMS
//    inert.next(A0); // 将采样值传入 Inert 类进行滤波

    C0 = AdccResultRegs.ADCRESULT0;
    C1 = AdccResultRegs.ADCRESULT1;
    C2 = AdccResultRegs.ADCRESULT2;
    C3 = AdccResultRegs.ADCRESULT3;

    TEMP = A0+A1+A2+A3+C0+C1+C2+C3;

    /* 效果：中间高，两边低。CMPA越大，脉宽越窄 */
    Uint16 cmp_val_1 = (Uint16)(5000/2 * (1-Duty));
    Uint16 cmp_val_2 = (Uint16)(5000/2 * (1+Duty));

    // 写入寄存器
    EPwm1Regs.CMPA.bit.CMPA = cmp_val_1;
    EPwm2Regs.CMPA.bit.CMPA = cmp_val_2;

    // 清除 ADC 中断标志
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
    // 中断标志清除并响应中断
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

// 中断函数
__interrupt void CPUTIMER0_ISR(void)
{
    flag_1ms = 1;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
