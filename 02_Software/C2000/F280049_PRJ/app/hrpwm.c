/*
 * hrpwm.c
 *
 *  Created on: 2025年11月19日
 *      Author: 45276
 */
#include "hrpwm.h"

Uint32 MEP_ScaleFactor = 100;
void InitEPwm1Gpio();
void HRPWM1_Init(Uint16 tbprd)
{
    EALLOW;
    /* 失能时基模块时钟 */
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /* 使能ePWM外设时钟 */
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    EDIS;

    /* GPIO初始化 */
    InitEPwm1Gpio();

    /* 配置TB相关寄存器 */
    EPwm1Regs.TBCTL.bit.SWFSYNC     = 0;                // 0脉冲不同步；1同步 软件强制脉冲同步
//    EPwm1Regs.TBPHS.bit.TBPHS       = 1;              // 0无移相操作；1移相操作
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;       // 相位负载使能，初始相位偏移 EPwm1Regs.TBPRD
    EPwm1Regs.TBCTR                 = 0x0000;           // 清除计数器的数值
    EPwm1Regs.TBPRD                 = tbprd;            // 设置计数值
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // 计数模式：0向上计数；1向下计数；2双向计数；3冻结
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // 不分频
    EPwm1Regs.TBCTL.bit.CLKDIV      = TB_DIV1;          // 不分频
    EPwm1Regs.TBCTL.bit.FREE_SOFT   = 01;

    /* 比较模块配置（CC寄存器） 0 0 0 0 */
    EPwm1Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;        // 影子模式 影子寄存器是一种双缓冲机制
    EPwm1Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;        // 当用户需要改变PWM参数时，先写入对应影子寄存器
                                                        // 通过影子寄存器，DSP能够再不影响当前操作的情况下预装载新的参数或数据
    EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // CTR=0时加载
    EPwm1Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // CTR=0时加载

    /* 初始化动作限定模块（AQ寄存器） */
    /* 当ePwmA计数器计数到 0 时输出低电平， 当ePwmA计数器向上计数到 CMPA 时输出高电平*/
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;                // 将PWMA1置零
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;                  // 在事件A上清除PWM1A，计数向上
    /* 当ePwmB计数器计数到 0 时输出低电平， 当ePwmB计数器向上计数到 CMPB 时输出高电平*/
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;                // 将PWMB1置零
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;                  // 在事件B上清除PWM1B，计数向上

    /* 比较值设置*/
    EPwm1Regs.CMPA.bit.CMPA = (EPwm1Regs.TBPRD)*(1-0);  // 占空比设置为0    //设置比较值A
    EPwm1Regs.CMPA.bit.CMPA = (EPwm1Regs.TBPRD)*(1-0);  // 占空比设置为1    //设置比较值B

    /* 死区控制模块（DB寄存器） */
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL   = DB_ACTV_HIC;         //
    // EPwm1Regs.DBCTL.bit.IN_MODE  = DBA_RED_DBB_FED;
    EPwm1Regs.DBCTL.bit.IN_MODE  = DBA_ALL;             // 单极性倍频时需要设置为DBA_ALL
    EPwm1Regs.DBRED.all          = 10;                  // 上升沿死区时间(1/主频*RED)   500ns
    EPwm1Regs.DBFED.all          = 10;                  // 下降沿死区时间

    EPwm1Regs.ETSEL.bit.INTSEL   = ET_CTR_PRD;          // ET_CTR_PRDZERD   ET_CTR_PRD
    EPwm1Regs.ETSEL.bit.INTEN    = 1;                   // 使能中断
    EPwm1Regs.ETPS.bit.INTPRD    = ET_1ST;              // 一次事件产生一次中断

    EALLOW;
    /* CNFC寄存器 */
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.HRLOAD         = HR_CTR_ZERO;      // 与CC寄存器的LOADxMODE保持一致
    EPwm1Regs.HRCNFG.bit.HRLOADB        = HR_CTR_ZERO;
    EPwm1Regs.HRCNFG.bit.CTLMODE        = HR_CMP;           // 与TB寄存器MODE保持一致
    EPwm1Regs.HRCNFG.bit.CTLMODEB       = HR_CMP;           // 控制模式 0：时段控制 1：行为控制
    EPwm1Regs.HRCNFG.bit.EDGMODE        = HR_BEP;           // 边缘模式 1：上升沿   2：下降沿   3：上下
    EPwm1Regs.HRCNFG.bit.EDGMODEB       = HR_BEP;
#if (AUTOCONVERT)
    EPwm1Regs.HRCNFG.bit.AUTOCONV       = 1;                //启用校准
#endif
    /* CTL寄存器 */
    EPwm1Regs.HRPCTL.bit.HRPE           = 0;                // 0：失能  1：使能（此时UP/DOWN不能使用）

    /* CNFC2寄存器高精度死区 */
    EPwm1Regs.HRCNFG2.bit.CTLMODEDBFED  = 0;                // 与CC寄存器的LOADxMODE保持一致
    EPwm1Regs.HRCNFG2.bit.CTLMODEDBRED  = 0;                // 与CC寄存器的LOADxMODE保持一致
    EPwm1Regs.HRCNFG2.bit.EDGMODEDB     = 3;                // 与TB寄存器CTRMODE保持一致
    EPwm1Regs.DBFEDHR.all               = 10;               // 跟DB寄存器保持一致
    EPwm1Regs.DBREDHR.all               = 10;
    EDIS;

    /* 使能时基模块时钟 */
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

//void HRPWM1_CPM_Set(Uint32 val)
//{
//    Uint32 temp,temp1;
//    Uint16 CMPA_reg_val;
//    Uint16 CMPAHR_reg_val;
//    Uint16 CMPB_reg_val;
//    Uint16 CMPBHR_reg_val;
//
//    // Q15格式    最大为0x7FDF 0~327668 0~100
//    CMPA_reg_val = ((long)val * ((EPwm1Regs.TBPRD+1))) >> 15;
//    CMPB_reg_val = ((long)val * ((EPwm1Regs.TBPRD+1))) >> 15;
//    temp         = ((long)val * ((EPwm1Regs.TBPRD+1)));
//    temp1        = ((long)val * ((EPwm1Regs.TBPRD+1)));
//    temp         = temp - ((long)CMPA_reg_val << 15);
//    temp1        = temp1 - ((long)CMPA_reg_val << 15);
//#if (AUTOCONVERT)
//    CMPAHR_reg_val = temp << 1;    // convert to Q16
//    CMPBHR_reg_val = temp << 1;    // convert to Q16
//#else
//    CMPA_reg_val = ((temp * MEP_ScaleFactor) + (0x0080<<7)) >> 15;
//    CMPA_reg_val = CMPAHR_reg_val<<8;
//    CMPB_reg_val = ((temp1 * MEP_ScaleFactor) + (0x0080<<7)) >> 15;
//    CMPB_reg_val = CMPBHR_reg_val<<8;
//#endif
//    EPwm1Regs.CMPA.all = ((long)CMPA_reg_val) << 16 | CMPAHR_reg_val;
//    EPwm1Regs.CMPB.all = ((long)CMPB_reg_val) << 16 | CMPBHR_reg_val;
//}

/* * val 输入范围：Q15格式 (0 ~ 32768对应 0~100% 占空比)
 * 对应公式中的 (Vm + 1) / 2
 */
void HRPWM1_CPM_Set(Uint32 val)
{
    Uint32 raw_val_A; // S1 的计算中间值
    Uint32 raw_val_B; // S3 的计算中间值

    Uint16 CMPA_reg_val, CMPAHR_reg_val;
    Uint16 CMPB_reg_val, CMPBHR_reg_val;
    Uint32 Period = EPwm1Regs.TBPRD; // 读取当前的周期值

    /* 逻辑推导：
       公式1: S1_Duty = val
       公式2: S3_Duty = 1 - val

       你的AQ配置是: CAU=SET(置高), CAD=CLEAR(拉低)。
       这意味着当计数器大于 CMP 时输出高？不对。
       通常 Up-Down 模式下:
       0 -> PRD (Up): 遇到 CMPA (Set) -> 变高
       PRD -> 0 (Down): 遇到 CMPA (Clear) -> 变低
       这样的波形是高电平居中 (Centered High)。
       占空比 D = (2 * (PRD - CMPA)) / (2 * PRD) = 1 - (CMPA / PRD)

       因此：
       CMPA = PRD * (1 - val)
       CMPB = PRD * (1 - (1-val)) = PRD * val
    */

    // --- 计算 S1 (CMPA) ---
    // 目标：CMPA = Period * (1 - val)
    // val 是 Q15, 所以计算 Period * (32768 - val)
    raw_val_A = ((Uint32)Period + 1) * (32768 - val);

    // --- 计算 S3 (CMPB) ---
    // 目标：CMPB = Period * val
    raw_val_B = ((Uint32)Period + 1) * val;

    // --- 处理 CMPA 的高精度部分 ---
    CMPA_reg_val = raw_val_A >> 15; // 取整数部分
    // 获取小数部分余数，准备转 Q8 或 Q16
    Uint32 remainder_A = raw_val_A - ((Uint32)CMPA_reg_val << 15);

    // --- 处理 CMPB 的高精度部分 ---
    CMPB_reg_val = raw_val_B >> 15; // 取整数部分
    Uint32 remainder_B = raw_val_B - ((Uint32)CMPB_reg_val << 15);

#if (AUTOCONVERT)
    // 如果开启自动转换，硬件会自动处理比例，只需左移对齐到 Q16 (对于 Type 4 PWM)
    // 这里的移位取决于 MEP_ScaleFactor 的处理方式，通常 AutoConvert 不需要乘 ScaleFactor
    // 但 F280049 通常建议使用 float 库或 SFO。这里沿用你代码的位移逻辑。
    // Q15 remainder 左移 1 位变成 Q16 格式送给 HR 寄存器
    CMPAHR_reg_val = remainder_A << 1;
    CMPBHR_reg_val = remainder_B << 1;
#else
    // 手动计算 MEP 步长
    // remainder 是 Q15 格式的 "0.xxxxx"
    // 需要乘以 MEP_ScaleFactor 转换为 MEP 计数值，并左移8位到 CMPAHR 高字节
    // (remainder * MEP_ScaleFactor) >> 15 得到 MEP 数量
    // 加上舍入 (0x0080<<7)

    Uint32 mep_calc_A = (remainder_A * MEP_ScaleFactor) + 0x4000; // 0x4000 is rounding for Q15
    CMPAHR_reg_val = (mep_calc_A >> 15) << 8; // 结果移入高8位

    Uint32 mep_calc_B = (remainder_B * MEP_ScaleFactor) + 0x4000;
    CMPBHR_reg_val = (mep_calc_B >> 15) << 8;
#endif

    // --- 写入寄存器 ---
    // F280049C 的 CMPA/CMPB 是 32 位寄存器 (高16位整数，低16位小数)
    EPwm1Regs.CMPA.all = ((Uint32)CMPA_reg_val << 16) | CMPAHR_reg_val;
    EPwm1Regs.CMPB.all = ((Uint32)CMPB_reg_val << 16) | CMPBHR_reg_val;
}


