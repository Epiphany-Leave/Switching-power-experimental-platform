/*
 * epwm.c
 *
 *  Created on: 2025年11月13日
 *      Author: 45276
 */

#include "epwm.h"

__interrupt void EPWM1_CONFIG(void);
__interrupt void EPWM2_CONFIG(void);

void EPwm_Init(Uint16 tbprd)
{
    EALLOW;
    /* 失能EPWM时基模块时钟 */
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    EPwm1_Init(tbprd); // 20KHz
    EPwm2_Init(tbprd);
    /* 使能时基模块时钟 */
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void InitEPwm1Gpio(void)
{
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;  // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;  // Disable pull-up on GPIO1 (EPWM1B)

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // Configure GPIO1 as EPWM1B

    EDIS;
}

void EPwm1_Init(Uint16 tbprd)
{
//    EALLOW;
//    /* 失能时基模块时钟 */
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
//    /* 使能ePWM外设时钟 */
//    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
//    EDIS;

    /* GPIO初始化 */
    InitEPwm1Gpio();

    /* 使能EPWM1中断 */
    EALLOW;
    PieVectTable.EPWM1_INT  = &EPWM1_CONFIG;
    EDIS;

    /* 配置TB相关寄存器 */
    EPwm1Regs.TBCTL.bit.SWFSYNC     = 0;                // 0脉冲不同步；1同步
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;       // 相位负载使能，初始相位偏移 EPwm1Regs.TBPRD
//    EPwm1Regs.TBCTL.bit.PHSDIR      = 1;              // 只在上下计数起作用；0:选择向下计数触发，1:选择向上计数触发
    EPwm1Regs.TBCTR                 = 0x0000;           // 清除计数器的数值
    EPwm1Regs.TBPRD                 = tbprd;            // 设置计数值
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // 计数模式：0向上计数；1向下计数；2双向计数；3冻结 
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // 不分频
    EPwm1Regs.TBCTL.bit.CLKDIV      = TB_DIV1;          // 不分频

    /* 比较模块配置（CC寄存器） 0 0 0 0 */
    EPwm1Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;        // 影子模式 影子寄存器是一种双缓冲机制（在修改的下一个周期执行，防止计数太突兀导致异常）
    EPwm1Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;        // 当用户需要改变PWM参数时，先将新值写入对应影子寄存器
                                                        // 通过影子寄存器，DSP能够再不影响当前操作的情况下预装载新的参数或数据
    EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // CTR=0时加载
    EPwm1Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // CTR=0时加载

    /* 初始化动作限定模块（AQ寄存器） */
    /* 当ePwmA计数器计数到 0 时输出低电平， 当ePwmA计数器向上计数到 CMAP 时输出高电平*/
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;                // 将PWMA1置零
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;                  // 在事件A上清除PWM1A，计数向上
    /* 当ePwmB计数器计数到 0 时输出低电平， 当ePwmB计数器向上计数到 CMBP 时输出高电平*/
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;                // 将PWMB1置零
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;                  // 在事件B上清除PWM1B，计数向上
    
    /* 比较值设置*/
    EPwm1Regs.CMPA.bit.CMPA = (EPwm1Regs.TBPRD)*(1-0);  // 占空比设置为0    //设置比较值A
    EPwm1Regs.CMPB.bit.CMPB = (EPwm1Regs.TBPRD)*(1-0);  // 占空比设置为1    //设置比较值B
    /* 死区控制模块（DB寄存器） */
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;         // 高有效互补，使用DB_ACTV_HIC时，比较值B设置被忽略；B直接取A输出的反相
    EPwm1Regs.DBCTL.bit.IN_MODE  = DBA_ALL;
    EPwm1Regs.DBRED.all          = 10;                  // 上升沿死区时间(1/主频*RED)   100ns
    EPwm1Regs.DBFED.all          = 10;                  // 下降沿死区时间

    /* 中断控制模块（ET寄存器） */
//    EPwm1Regs.ETSEL.bit.INTSEL   = ET_CTR_PRD;          // ET_CTR_PRD:计数器计到最大值（三角波的顶峰）时触发中断 ET_CTR_PRDZERD:计数器计到最小值（三角波的低谷）时触发中断
//    EPwm1Regs.ETSEL.bit.INTEN    = 1;                   // 使能中断
//    EPwm1Regs.ETPS.bit.INTPRD    = ET_1ST;              // 一次事件产生一次中断

//    /* 使能时基模块时钟 */
//    EALLOW;
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
//    EDIS;

//    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  // x=1  PIE组3 EPWM1中断使能
//    IER |= M_INT3;                      // y=3  EPWM1使能GROUP3中断
}

__interrupt void EPWM1_CONFIG(void)
{
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


void InitEPwm2Gpio(void)
{
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;  // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;  // Disable pull-up on GPIO1 (EPWM1B)

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // Configure GPIO1 as EPWM1B

    EDIS;
}

void EPwm2_Init(Uint16 tbprd)
{
//    EALLOW;
//    /* 失能时基模块时钟 */
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
//    /* 使能ePWM外设时钟 */
//    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
//    EDIS;

    /* GPIO初始化 */
    InitEPwm2Gpio();

    /* 使能EPWM1中断 */
    EALLOW;
    PieVectTable.EPWM2_INT  = &EPWM2_CONFIG;
    EDIS;

    /* 配置TB相关寄存器 */
    EPwm2Regs.TBCTL.bit.SWFSYNC     = 0;                // 0脉冲不同步；1同步
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_DISABLE;       // 相位负载使能，初始相位偏移 EPwm2Regs.TBPRD
//    EPwm2Regs.TBCTL.bit.PHSDIR      = 1;              // 只在上下计数起作用；0:选择向下计数触发，1:选择向上计数触发
    EPwm2Regs.TBCTR                 = 0x0000;           // 清除计数器的数值
    EPwm2Regs.TBPRD                 = tbprd;            // 设置计数值
    EPwm2Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // 计数模式：0向上计数；1向下计数；2双向计数；3冻结
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // 不分频
    EPwm2Regs.TBCTL.bit.CLKDIV      = TB_DIV1;          // 不分频

    /* 比较模块配置（CC寄存器） 0 0 0 0 */
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;        // 影子模式 影子寄存器是一种双缓冲机制（在修改的下一个周期执行，防止计数太突兀导致异常）
    EPwm2Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;        // 当用户需要改变PWM参数时，先将新值写入对应影子寄存器
                                                        // 通过影子寄存器，DSP能够再不影响当前操作的情况下预装载新的参数或数据
    EPwm2Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // CTR=0时加载
    EPwm2Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // CTR=0时加载

    /* 初始化动作限定模块（AQ寄存器） */
    /* 当ePwmA计数器计数到 0 时输出低电平， 当ePwmA计数器向上计数到 CMAP 时输出高电平*/
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;                // 将PWMA1置零
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;                  // 在事件A上清除PWM1A，计数向上
    /* 当ePwmB计数器计数到 0 时输出低电平， 当ePwmB计数器向上计数到 CMBP 时输出高电平*/
    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;                // 将PWMB1置零
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;                  // 在事件B上清除PWM1B，计数向上

    /* 比较值设置*/
    EPwm2Regs.CMPA.bit.CMPA = (EPwm2Regs.TBPRD)*(1-0);  // 占空比设置为0    //设置比较值A
    EPwm2Regs.CMPB.bit.CMPB = (EPwm2Regs.TBPRD)*(1-0);  // 占空比设置为1    //设置比较值B
    /* 死区控制模块（DB寄存器） */
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;         // 高有效互补，使用DB_ACTV_HIC时，比较值B设置被忽略；B直接取A输出的反相
    EPwm2Regs.DBCTL.bit.IN_MODE  = DBA_ALL;
    EPwm2Regs.DBRED.all          = 10;                  // 上升沿死区时间(1/主频*RED)   100ns
    EPwm2Regs.DBFED.all          = 10;                  // 下降沿死区时间

//    EPwm2Regs.ETSEL.bit.INTSEL   = ET_CTR_PRD;          // ET_CTR_PRD:计数器计到最大值（三角波的顶峰）时触发中断 ET_CTR_PRDZERD:计数器计到最小值（三角波的低谷）时触发中断
//    EPwm2Regs.ETSEL.bit.INTEN    = 1;                   // 使能中断
//    EPwm2Regs.ETPS.bit.INTPRD    = ET_1ST;              // 一次事件产生一次中断

//    /* 使能时基模块时钟 */
//    EALLOW;
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
//    EDIS;

//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;  // x=2  PIE组3 EPWM1中断使能
//    IER |= M_INT3;                      // y=3  EPWM1使能GROUP3中断
}

__interrupt void EPWM2_CONFIG(void)
{
    EPwm2Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


