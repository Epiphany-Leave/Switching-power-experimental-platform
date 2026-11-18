/*
 * TZ.C
 *
 *  Created on: 2025年7月14日
 *      Author: c
 */


#include "TZ.h"
/*需要区分低输出比较器和高输出比较器  一般直接用高侧   */
/*
 * IO 分类：
 *  0:  A2/B6/C9
 *  1:  A11/B10/C0
 *  2:  A6
 *  3:  A15
 *  4:  A1/B7/DACB_OUT
 *  5:  B5
 * */
void TZ_Cmpss_1_Init(uint16_t Val,Uint16 Io,Uint16 Mode){
    EALLOW;
    /**/
    if(Mode){
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP1HPMXSEL = Io;            //高侧adc输入
    }else{
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP1LPMXSEL = Io;            //低侧adc输入
    }

    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;                            //使能内部DAC

    if(Mode){
        Cmpss1Regs.COMPCTL.bit.ASYNCLEN = 0;                            //低比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss1Regs.COMPCTL.bit.CTRIPOUTLSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss1Regs.COMPCTL.bit.CTRIPLSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss1Regs.COMPCTL.bit.COMPLINV = 0;                            //低比较器输出不反向
        Cmpss1Regs.COMPCTL.bit.COMPLSOURCE =0;                          //低比较器负端口链接DAC
    }else{

        Cmpss1Regs.COMPCTL.bit.ASYNCHEN = 0;                            //高比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss1Regs.COMPCTL.bit.CTRIPHSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss1Regs.COMPCTL.bit.COMPHINV = 0;                            //低比较器输出不反向
        Cmpss1Regs.COMPCTL.bit.COMPHSOURCE =0;                          //低比较器负端口链接DAC
    }
    Cmpss1Regs.COMPHYSCTL.bit.COMPHYS = 0;                              //设置滞环宽度  具体需要详细看数据手册  而不是编程手册  有迟滞这一项 单位是LSB

    Cmpss1Regs.COMPDACCTL.bit.FREESOFT = 2;                             //仿真挂起仍然执行
    Cmpss1Regs.COMPDACCTL.bit.SWLOADSEL = 0;                            //使用系统时钟同步DAC
    Cmpss1Regs.COMPDACCTL.bit.SELREF = 0;                               //VDDA作为DAC的参考电压
    Cmpss1Regs.COMPDACCTL.bit.DACSOURCE = 0;                            //DAC更新数据来自于其影子寄存器 而不是斜坡发生器

    Cmpss1Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss1Regs.DACLVALS.bit.DACVAL = Val;

    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm1Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm1Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm1Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE           =0;                              //清除标志位

    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm2Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm2Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm2Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm3Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm3Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm3Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm3Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm4Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm4Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm4Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm4Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm5Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm5Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm5Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm5Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm5Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm5Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm5Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm5Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm6Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm6Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm6Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm6Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm6Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm6Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm6Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm6Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位


    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0=0;
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0=1;                             //启用EPwmXbarRegs
    EDIS;
    //EPwm1Regs.TZCBCFLG.bit.CBC1  读这一位
}

/*需要区分低输出比较器和高输出比较器  一般直接用高侧   */
/*
 * IO 分类：
 *  0:  A4/B8
 *  1:  A12
 *  2:  A9
 *  3:  A10/B1/C10
 *  4:  B0/C11
 *  5:  A5
 * */
void TZ_Cmpss_2_Init(uint16_t Val,Uint16 Io,Uint16 Mode){
    EALLOW;
    /**/
    if(Mode){
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP2HPMXSEL = Io;            //高侧adc输入
    }else{
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP2LPMXSEL = Io;            //低侧adc输入
    }

    Cmpss2Regs.COMPCTL.bit.COMPDACE = 1;                            //使能内部DAC

    if(Mode){
        Cmpss2Regs.COMPCTL.bit.ASYNCLEN = 0;                            //低比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss2Regs.COMPCTL.bit.CTRIPOUTLSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss2Regs.COMPCTL.bit.CTRIPLSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss2Regs.COMPCTL.bit.COMPLINV = 0;                            //低比较器输出不反向
        Cmpss2Regs.COMPCTL.bit.COMPLSOURCE =0;                          //低比较器负端口链接DAC
    }else{

        Cmpss2Regs.COMPCTL.bit.ASYNCHEN = 0;                            //高比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss2Regs.COMPCTL.bit.CTRIPOUTHSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss2Regs.COMPCTL.bit.CTRIPHSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss2Regs.COMPCTL.bit.COMPHINV = 0;                            //低比较器输出不反向
        Cmpss2Regs.COMPCTL.bit.COMPHSOURCE =0;                          //低比较器负端口链接DAC
    }
    Cmpss2Regs.COMPHYSCTL.bit.COMPHYS = 0;                              //设置滞环宽度  具体需要详细看数据手册  而不是编程手册  有迟滞这一项 单位是LSB

    Cmpss2Regs.COMPDACCTL.bit.FREESOFT = 2;                             //仿真挂起仍然执行
    Cmpss2Regs.COMPDACCTL.bit.SWLOADSEL = 0;                            //使用系统时钟同步DAC
    Cmpss2Regs.COMPDACCTL.bit.SELREF = 0;                               //VDDA作为DAC的参考电压
    Cmpss2Regs.COMPDACCTL.bit.DACSOURCE = 0;                            //DAC更新数据来自于其影子寄存器 而不是斜坡发生器

    Cmpss2Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss2Regs.DACLVALS.bit.DACVAL = Val;

    EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm1Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm1Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm1Regs.TZSEL.bit.DCBEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm1Regs.TZDCSEL.bit.DCBEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm1Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE        =   0;                          //清除标志位

    EPwm2Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm2Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm2Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm2Regs.TZSEL.bit.DCBEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm2Regs.TZSEL.bit.CBC1        =   1;
    EPwm2Regs.TZDCSEL.bit.DCBEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm2Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位


    EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm3Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm3Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm3Regs.TZSEL.bit.DCBEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm3Regs.TZSEL.bit.CBC1        =   1;
    EPwm3Regs.TZDCSEL.bit.DCBEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm3Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm4Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm4Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm4Regs.DCBCTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm4Regs.TZSEL.bit.DCBEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm4Regs.TZSEL.bit.CBC1        =   1;
    EPwm4Regs.TZDCSEL.bit.DCBEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm4Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        =  0;                              //清除标志位


    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX2=0;
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX2=1;                             //启用EPwmXbarRegs
    EDIS;
    //EPwm1Regs.TZCBCFLG.bit.CBC1  读这一位

}
/*
 * IO 分类：
 *  0:  B2/C6
 *  1:  B12/C2
 *  2: A0/B15/C15/DACA_OUT
 *  3:  B3/VDAC
 *  4:  A14/B14/C4
 *  5:  A3
 * */
void TZ_Cmpss_3_Init(uint16_t Val,Uint16 Io,Uint16 Mode){
    EALLOW;
    /**/
    if(Mode){
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP3HPMXSEL = Io;            //高侧adc输入
    }else{
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP3LPMXSEL = Io;            //低侧adc输入
    }

    Cmpss3Regs.COMPCTL.bit.COMPDACE = 1;                            //使能内部DAC

    if(Mode){
        Cmpss3Regs.COMPCTL.bit.ASYNCLEN = 0;                            //低比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss3Regs.COMPCTL.bit.CTRIPOUTLSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss3Regs.COMPCTL.bit.CTRIPLSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss3Regs.COMPCTL.bit.COMPLINV = 0;                            //低比较器输出不反向
        Cmpss3Regs.COMPCTL.bit.COMPLSOURCE =0;                          //低比较器负端口链接DAC
    }else{

        Cmpss3Regs.COMPCTL.bit.ASYNCHEN = 0;                            //高比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss3Regs.COMPCTL.bit.CTRIPOUTHSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss3Regs.COMPCTL.bit.CTRIPHSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss3Regs.COMPCTL.bit.COMPHINV = 0;                            //低比较器输出不反向
        Cmpss3Regs.COMPCTL.bit.COMPHSOURCE =0;                          //低比较器负端口链接DAC
    }
    Cmpss3Regs.COMPHYSCTL.bit.COMPHYS = 0;                              //设置滞环宽度  具体需要详细看数据手册  而不是编程手册  有迟滞这一项 单位是LSB

    Cmpss3Regs.COMPDACCTL.bit.FREESOFT = 2;                             //仿真挂起仍然执行
    Cmpss3Regs.COMPDACCTL.bit.SWLOADSEL = 0;                            //使用系统时钟同步DAC
    Cmpss3Regs.COMPDACCTL.bit.SELREF = 0;                               //VDDA作为DAC的参考电压
    Cmpss3Regs.COMPDACCTL.bit.DACSOURCE = 0;                            //DAC更新数据来自于其影子寄存器 而不是斜坡发生器

    Cmpss3Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss3Regs.DACLVALS.bit.DACVAL = Val;


    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm1Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm1Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm1Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE           =0;                              //清除标志位

    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm2Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm2Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm2Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm3Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm3Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm3Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm3Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 4;                            //LINK TRIPIN5
    EPwm4Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm4Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm4Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm4Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位


    EPwmXbarRegs.TRIP5MUX0TO15CFG.bit.MUX4=0;
    EPwmXbarRegs.TRIP5MUXENABLE.bit.MUX4=1;                             //启用EPwmXbarRegs

    EDIS;
    //EPwm1Regs.TZCBCFLG.bit.CBC1  读这一位


}
/*
 * IO 分类：
 *  0:  B4/C8
 *  1:  A7/C3
 *  2:  C1
 *  3:  C14
 *  4:  A8
 *  5:  B11
 * */
void TZ_Cmpss_4_Init(uint16_t Val,Uint16 Io,Uint16 Mode){
    EALLOW;
    /**/
    if(Mode){
        AnalogSubsysRegs.CMPHPMXSEL.bit.CMP4HPMXSEL = Io;            //高侧adc输入
    }else{
        AnalogSubsysRegs.CMPLPMXSEL.bit.CMP4LPMXSEL = Io;            //低侧adc输入
    }

    Cmpss4Regs.COMPCTL.bit.COMPDACE = 1;                            //使能内部DAC

    if(Mode){
        Cmpss4Regs.COMPCTL.bit.ASYNCLEN = 0;                            //低比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss4Regs.COMPCTL.bit.CTRIPOUTLSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss4Regs.COMPCTL.bit.CTRIPLSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss4Regs.COMPCTL.bit.COMPLINV = 0;                            //低比较器输出不反向
        Cmpss4Regs.COMPCTL.bit.COMPLSOURCE =0;                          //低比较器负端口链接DAC
    }else{

        Cmpss4Regs.COMPCTL.bit.ASYNCHEN = 0;                            //高比较器不馈入数字锁存滤波输出到OR门     也就是存在数字滤波
        Cmpss4Regs.COMPCTL.bit.CTRIPOUTHSEL =2;                         // 0是异步 1是同步 2是数字滤波 3是数字滤波加锁存 同步1-2CLK 数字滤波2clk 锁存+1clk
        Cmpss4Regs.COMPCTL.bit.CTRIPHSEL = 2;                           //比较器输出非同步非滤波信号
        Cmpss4Regs.COMPCTL.bit.COMPHINV = 0;                            //低比较器输出不反向
        Cmpss4Regs.COMPCTL.bit.COMPHSOURCE =0;                          //低比较器负端口链接DAC
    }
    Cmpss4Regs.COMPHYSCTL.bit.COMPHYS = 0;                              //设置滞环宽度  具体需要详细看数据手册  而不是编程手册  有迟滞这一项 单位是LSB

    Cmpss4Regs.COMPDACCTL.bit.FREESOFT = 2;                             //仿真挂起仍然执行
    Cmpss4Regs.COMPDACCTL.bit.SWLOADSEL = 0;                            //使用系统时钟同步DAC
    Cmpss4Regs.COMPDACCTL.bit.SELREF = 0;                               //VDDA作为DAC的参考电压
    Cmpss4Regs.COMPDACCTL.bit.DACSOURCE = 0;                            //DAC更新数据来自于其影子寄存器 而不是斜坡发生器

    Cmpss4Regs.DACHVALS.bit.DACVAL = Val;
    Cmpss4Regs.DACLVALS.bit.DACVAL = Val;

    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm1Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm1Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm1Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm1Regs.TZCLR.bit.CBCPULSE           =0;                              //清除标志位

    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm2Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm2Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm2Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm2Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm3Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm3Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm3Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm3Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm3Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位

    EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;                            //LINK TRIPIN4
    EPwm4Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;                            //同步方式一致
    EPwm4Regs.TZSEL.bit.DCAEVT2     =   1;                              //CBC事件触发       逐周期
    EPwm4Regs.TZDCSEL.bit.DCAEVT2   =   2;                              //跳闸触发事件  H为高
    EPwm4Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCTL.bit.TZB         =   TZ_FORCE_LO;                    //使能后拉低
    EPwm4Regs.TZCLR.bit.CBCPULSE        =   0;                              //清除标志位


    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX6=0;
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX6=1;                             //启用EPwmXbarRegs
    EDIS;
    EDIS;
    //EPwm1Regs.TZCBCFLG.bit.CBC1  读这一位

}
