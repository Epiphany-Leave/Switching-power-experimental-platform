/*
 * tz.c
 *
 *  Created on: 2025?ê12??29??
 *      Author: 45276
 */

#include "tz.h"

/* F280049C有七个CMPSS */

/* 需要区分低输出比较器和高输出比较器   一般直接用高输出比较器*/
/*
 * IO分类：
 * 0:A2/B6
 * 1:C0
 * 2:PGA1_IN
 * 3:A3
 * 4:A11/B7
*/
/* TZ_Cmpss_1_Init
 * param:Val-阈值 Io-端口 Mode-高侧/低侧
 */
void TZ_Cmpss_1_Init(uint16_t Val, Uint16 Io, Uint16 Mode)
{
    EALLOW;
    /* 比较器IO复用 */
    if(Mode)
    {
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP1HPMXSEL = Io;
    }
    else
    {
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP1LPMXSEL = Io;
    }
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;

    if(Mode == 0)
    {
        Cmpss1Regs.COMPCTL.bit.ASYNCLEN     = 0;    // 低比较器不馈入数字锁存滤波输出到OR门 也就是存在数字滤波
        Cmpss1Regs.COMPCTL.bit.CTRIPOUTLSEL = 2;    // 0：异步  1：同步  2：数字滤波  3：数字滤波+锁存  同步1~2CLK  数字滤波2CLK  锁存+1CLK 
        Cmpss1Regs.COMPCTL.bit.CTRIPLSEL    = 2;    // 比较器输出非同步非滤波信号
        Cmpss1Regs.COMPCTL.bit.COMPLINV     = 0;    // 低比较器输出不反向
        Cmpss1Regs.COMPCTL.bit.COMPLSOURCE  = 0;    // 低比较器负端口链接DAC
    }
    else
    {
        Cmpss1Regs.COMPCTL.bit.ASYNCHEN     = 0;    // 高比较器不馈入数字锁存滤波输出到OR门 也就是存在数字滤波
        Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL = 2;    // 0：异步  1：同步  2：数字滤波  3：数字滤波+锁存  同步1-2CLK  数字滤波2CLK  锁存+1CLK 
        Cmpss1Regs.COMPCTL.bit.CTRIPHSEL    = 2;    // 比较器输出非同步非滤波信号
        Cmpss1Regs.COMPCTL.bit.COMPHINV     = 0;    // 高比较器输出不反向
        Cmpss1Regs.COMPCTL.bit.COMPHSOURCE  = 0;    // 高比较器负端口链接DAC
    }
    Cmpss1Regs.COMPHYSCTL.bit.COMPHYS = 0;          // 设置滞环宽度 具体需要详细看数据手册 而不是编程手册 有迟滞这一项 单位LSB（1->12 2->24 3->36 4->48）

    Cmpss1Regs.COMPDACCTL.bit.FREESOFT  = 2;        // 仿真挂起仍然运行
    Cmpss1Regs.COMPDACCTL.bit.SWLOADSEL = 0;        // 使用系统时钟同步DAC
    Cmpss1Regs.COMPDACCTL.bit.SELREF    = 0;        // 0:VDDA作为DAC的参考电压  1:VDAC作为DAC的参考电压
    Cmpss1Regs.COMPDACCTL.bit.DACSOURCE = 0;        // 0:DAC更新数据来自影子寄存器  1:DAC更新数据来自斜坡发生器
    
    Cmpss1Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss1Regs.DACLVALS.bit.DACVAL = Val;

    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;        // LINK TRPIN4
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCAEVT1:用于触发ADC采样或同步信号(Sync)  DCAEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm1Regs.TZSEL.bit.DCAEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm1Regs.TZDCSEL.bit.DCAEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm1Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm1Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;        // LINK TRPIN4
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCAEVT1:用于触发ADC采样或同步信号(Sync)  DCAEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm2Regs.TZSEL.bit.DCAEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm2Regs.TZDCSEL.bit.DCAEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm2Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm2Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;        // LINK TRPIN4
    EPwm3Regs.DCACTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCAEVT1:用于触发ADC采样或同步信号(Sync)  DCAEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm3Regs.TZSEL.bit.DCAEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm3Regs.TZDCSEL.bit.DCAEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm3Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm3Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;        // LINK TRPIN4
    EPwm4Regs.DCACTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCAEVT1:用于触发ADC采样或同步信号(Sync)  DCAEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm4Regs.TZSEL.bit.DCAEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm4Regs.TZDCSEL.bit.DCAEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm4Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm4Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0 = 0;     // TRIPx其中x为LINK TRPIN4，即x = 3+1 = 4
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0   = 1;     // 启用EpwmXbarRegs
    EDIS;
//    EPwm1Regs.TZCBCFLG.bit.CBC1 = 1;
}

/* 需要区分低输出比较器和高输出比较器   一般直接用高输出比较器*/
/*
 * IO分类：
 * 0:A4/B8/PGA2_OF
 * 1:C1
 * 2:PGA2_IN
 * 3:A5
 * 4:A12/B9
*/
void TZ_Cmpss_2_Init(uint16_t Val, Uint16 Io, Uint16 Mode)
{
    EALLOW;
    // 比较器IO复用
    if(Mode)
    {
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP2HPMXSEL = Io;
    }
    else
    {
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP2LPMXSEL = Io;
    }
    Cmpss2Regs.COMPCTL.bit.COMPDACE = 1;

    if(Mode == 0)
    {
        Cmpss2Regs.COMPCTL.bit.ASYNCLEN     = 0;    // 低比较器不馈入数字锁存滤波输出到OR门 也就是存在数字滤波
        Cmpss2Regs.COMPCTL.bit.CTRIPOUTLSEL = 2;    // 0：异步  1：同步  2：数字滤波  3：数字滤波+锁存  同步1~2CLK  数字滤波2CLK  锁存+1CLK
        Cmpss2Regs.COMPCTL.bit.CTRIPLSEL    = 2;    // 比较器输出非同步非滤波信号
        Cmpss2Regs.COMPCTL.bit.COMPLINV     = 0;    // 低比较器输出不反向
        Cmpss2Regs.COMPCTL.bit.COMPLSOURCE  = 0;    // 低比较器负端口链接DAC
    }
    else
    {
        Cmpss2Regs.COMPCTL.bit.ASYNCHEN     = 0;    // 高比较器不馈入数字锁存滤波输出到OR门 也就是存在数字滤波
        Cmpss2Regs.COMPCTL.bit.CTRIPOUTHSEL = 2;    // 0：异步  1：同步  2：数字滤波  3：数字滤波+锁存  同步1-2CLK  数字滤波2CLK  锁存+1CLK
        Cmpss2Regs.COMPCTL.bit.CTRIPHSEL    = 2;    // 比较器输出非同步非滤波信号
        Cmpss2Regs.COMPCTL.bit.COMPHINV     = 0;    // 高比较器输出不反向
        Cmpss2Regs.COMPCTL.bit.COMPHSOURCE  = 0;    // 高比较器负端口链接DAC
    }
    Cmpss2Regs.COMPHYSCTL.bit.COMPHYS = 0;          // 设置滞环宽度 具体需要详细看数据手册 而不是编程手册 有迟滞这一项 单位LSB（1->12 2->24 3->36 4->48）

    Cmpss2Regs.COMPDACCTL.bit.FREESOFT  = 2;        // 仿真挂起仍然运行
    Cmpss2Regs.COMPDACCTL.bit.SWLOADSEL = 0;        // 使用系统时钟同步DAC
    Cmpss2Regs.COMPDACCTL.bit.SELREF    = 0;        // 0:VDDA作为DAC的参考电压  1:VDAC作为DAC的参考电压
    Cmpss2Regs.COMPDACCTL.bit.DACSOURCE = 0;        // 0:DAC更新数据来自影子寄存器  1:DAC更新数据来自斜坡发生器

    Cmpss2Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss2Regs.DACLVALS.bit.DACVAL = Val;

    EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;        // LINK TRPIN5
    EPwm1Regs.DCBCTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCBEVT1:用于触发ADC采样或同步信号(Sync)  DCBEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm1Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm1Regs.TZSEL.bit.DCBEVT2         = 1;        // CBC事件触发（逐周期）
    // EPwm1Regs.TZSEL.bit.CBC1 = 1;                // 外部引脚
    EPwm1Regs.TZDCSEL.bit.DCBEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm1Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm1Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm2Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;        // LINK TRPIN5
    EPwm2Regs.DCBCTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCBEVT1:用于触发ADC采样或同步信号(Sync)  DCBEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm2Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm2Regs.TZSEL.bit.DCBEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm2Regs.TZDCSEL.bit.DCBEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm2Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm2Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;        // LINK TRPIN5
    EPwm3Regs.DCBCTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCBEVT1:用于触发ADC采样或同步信号(Sync)  DCBEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm3Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm3Regs.TZSEL.bit.DCBEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm3Regs.TZDCSEL.bit.DCBEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm3Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm3Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwm4Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;        // LINK TRPIN5
    EPwm4Regs.DCBCTL.bit.EVT1SRCSEL     = DC_EVT1;  // DCBEVT1:用于触发ADC采样或同步信号(Sync)  DCBEVT2:用于触发TZ保护  CMPSS里有滤波,这里不需要再做
    EPwm4Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;        // 同步方式一致
    EPwm4Regs.TZSEL.bit.DCBEVT2         = 1;        // CBC事件触发（逐周期）
    EPwm4Regs.TZDCSEL.bit.DCBEVT2       = 2;        // 跳闸触发事件 H为高
    EPwm4Regs.TZCTL.bit.TZA             = TZ_FORCE_LO; // 使能后拉低
    EPwm4Regs.TZCTL.bit.TZB             = TZ_FORCE_LO; // 使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        = 0;        // 消除标志位 CBC 清零脉冲选择

    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX2 = 0;     // TRIPx其中x为LINK TRPIN5，即x = 4+1 = 5
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX2   = 1;     // 启用EpwmXbarRegs
    EDIS;
//    EPwm1Regs.TZCBCFLG.bit.CBC1 = 1;
}

