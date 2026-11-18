/*
 * HRPWM.C
 *
 *  Created on: 2024年11月21日
 *      Author: c
 */

#include "hrpwm.h"
#include "math.h"

#define AUTOCONVERT  1
/*   CMPAHR寄存器赋值为  （（占空比x满载波值）的小数部分 x MEP+0.5） << 8     也就是是对小数部分进行精确控制  */
/*    MEP  10n/180p  = 55 */
/*   当使用 DBREDHR和DBFEDHR时， DBRED或DBFED  必须大于等于7    */
/*   TBPRDHR寄存器的值  frac（PWMperiod）*MEP+0.5   */

/*
 *
 * 详细过程 ： 开启epwm时钟
 *          使能HRpwm时钟
 *          禁用TBCLKSYNC
 *          配置epwm  只能向上计数或者上下计数模式
 *          必须配置影子寄存器
 *          CMPCLT[LOADAMODE]  向上计数  =1  （加载CTR=PRD）  上下计数  =2 （加载CTR=0或者CTR=PED）
 *          配置HRCNFG注册表： 1  HRCHFG[HRLOAD]=2 (加载CTR=0或者CTR=PED) 2  HRCHFG[AUTOCONV]=1（启动自动转换） HRCNFG[EDGMODE]=3  （双边MEP控制）
 *          对于高分辨率周期的TBPHS:TBOHSHR同步  设置HRPCTL[TBPSHRLOADE] = 1 and TBCTL[PHSEN] = 1
 *          启用高分辨率控制 HRPCTL[HRPE] = 1
 *          启用 TBCLKSYNC
 *          TBCTL[SWFSYNC] = 1
 *          SFO函数得到MEP比例因子
 *          写入 TBPRDHR(M) registers
 *
 * */
uint32_t  MEP_ScaleFactor = 55; // Start with typical Scale Factor
void  InitEPwm1Gpio();
void  InitEPwm2Gpio();
void  InitEPwm3Gpio();
void  InitEPwm4Gpio();
void  InitEPwm5Gpio();
void  InitEPwm6Gpio();
__interrupt void  HRPWM1_CONFIG();
__interrupt void  EPWM2_CONFIG();
__interrupt void  EPWM3_CONFIG();
void HRPMW1_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    EDIS;

    EALLOW;
    PieVectTable.EPWM1_INT = &HRPWM1_CONFIG;
    EDIS;
    /*GPIO初始化*/
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;   // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    EDIS;
    /*配置TB相关寄存器*/
    EALLOW;
    EPwm1Regs.TBCTL.bit.SWFSYNC = 0;                // 0 为脉冲不同步  1 为同步  软件强制脉冲同步
    // EPwm1Regs.TBPHS.bit.TBPHS=0;
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN  =1;         //当为0的时候产生一个同步脉冲
    EPwm1Regs.TBCTL.bit.PHSEN   =  TB_DISABLE;      //  相位负载使能 初始相位偏移  EPwm1Regs.TBPHS
    EPwm1Regs.TBCTR     =   0X0000;                 //清除计数器的值
    EPwm1Regs.TBPRD     =   tbprd;                  //设置周期值
    EPwm1Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UPDOWN;    //上计数模式
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;    //不分频
    EPwm1Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;        //不分频
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 01;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/

    EPwm1Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;  //使用影子寄存器   影子寄存器实际上是一种双缓冲机制 新的数据被写入活动寄存器之前，它首先在影子寄存器中进行缓存。
    EPwm1Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;  //当用户想要改变PWM（脉冲宽度调制）的参数时，不是直接写入正在使用的寄存器，而是先将新值写入对应的影子寄存器。
                                                    //通过使用影子寄存器，DSP系统能够在不影响当前操作的情况下预装载新的参数或数据。
    EPwm1Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_ZERO;//CTR=0时加载
    EPwm1Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_ZERO;//CTR=0时加载

    /*比较值设置*/
    EPwm1Regs.CMPA.bit.CMPA = (EPwm1Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值A
//    EPwm1Regs.CMPB.bit.CMPB = (EPwm1Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B

    /*初始化动作限定模块 （配置AQ寄存器）*/

    EPwm1Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;
//    EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;

    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // 将PWM1A置零
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // 在事件A上清除PWM1A，计数上升

    /*死区控制模块 DB寄存器*/
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    // 500ns --  500/5ns=100
    EPwm1Regs.DBRED.bit.DBRED = 50;
    EPwm1Regs.DBFED.bit.DBFED = 50;
    EPwm1Regs.DBFEDHR.bit.DBFEDHR = 0;
    EPwm1Regs.DBREDHR.bit.DBREDHR = 0;//HRDB

    EDIS;

    EALLOW;
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO;  //CTR=0时加载
    EPwm1Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO; //CTR=0时加载
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm1Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_BEP;
    EPwm1Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
#if(AUTOCONVERT)
    EPwm1Regs.HRCNFG.bit.AUTOCONV = 1;      // Enable auto-conversion
                                               // logic
#endif
    EPwm1Regs.HRPCTL.bit.HRPE = 0; // Turn off high-resolution period
                                       // control.
    EPwm1Regs.HRCNFG2.bit.CTLMODEDBFED=0;
    EPwm1Regs.HRCNFG2.bit.CTLMODEDBRED=0;
    EPwm1Regs.HRCNFG2.bit.EDGMODEDB=3;

    //EPwm1Regs.HRPCTL.bit.TBPHSHRLOADE = 1;
    //EPwm1Regs.HRPCTL.bit.HRPE = 1;
    //EPwm1Regs.HRCNFG.bit.EDGMODE = HR_FEP;      // Control Falling Edge Position
    //EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;      // CMPAHR controls the MEP
    //EPwm1Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO;  // Shadow load on CTR=Zero
    EDIS;

     // value for 100MHz
     // Note: Use SFO functions to update MEP_ScaleFactor dynamically


//    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //ET_CTR_PRDZERO  ET_CTR_PRD
//    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // 使能中断
//    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // 一次事件产生一次中断
//
//    IER |= M_INT3;                          // Y 选中
//    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;      //X 选中
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;      //X 选中
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
void HRPMW2_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
    EDIS;

//    EALLOW;
//    PieVectTable.EPWM2_INT = &HRPWM2_CONFIG;
//    EDIS;
    /*GPIO初始化*/
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;   // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    EDIS;
    /*配置TB相关寄存器*/
    EALLOW;
    EPwm2Regs.TBCTL.bit.SWFSYNC = 1;                // 0 为脉冲不同步  1 为同步
    EPwm2Regs.EPWMSYNCINSEL.bit.SEL=0x1;      //和epwm1同步
    EPwm2Regs.TBCTL.bit.PHSEN   =  TB_ENABLE;      //  相位负载使能 初始相位偏移  EPwm1Regs.TBPRD
    EPwm2Regs.TBCTR     =   0X0000;                 //清除计数器的值
    EPwm2Regs.TBPRD     =   tbprd;                //设置周期值
    EPwm2Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UPDOWN;    //上计数模式
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;    //不分频
    EPwm2Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;        //不分频
    EPwm2Regs.TBCTL.bit.FREE_SOFT = 01;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;  //使用影子寄存器   影子寄存器实际上是一种双缓冲机制 新的数据被写入活动寄存器之前，它首先在影子寄存器中进行缓存。
    EPwm2Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;  //当用户想要改变PWM（脉冲宽度调制）的参数时，不是直接写入正在使用的寄存器，而是先将新值写入对应的影子寄存器。
    EPwm2Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_ZERO;//CTR=0时加载
    EPwm2Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_ZERO;//CTR=0时加载
    /*比较值设置*/
    EPwm2Regs.CMPA.bit.CMPA = (EPwm2Regs.TBPRD)* (1);       //占空比设定0;                             // 设置比较值A
//   EPwm2Regs.CMPB.bit.CMPB = (EPwm2Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B
   /*初始化动作限定模块 （配置AQ寄存器）*/
   /*当 ePWMA计数器计数到 0 时输出高电平，当 ePWMA 计数器向上计数到 CMPA 时输出低电平，*/
    EPwm2Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;
    EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;

    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;

    /*死区控制模块 DB寄存器*/
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    // 200ns --  200/5ns=40    整数/5 = DBRED (小数*55+0.5)*256
    EPwm2Regs.DBRED.bit.DBRED = 50;
    EPwm2Regs.DBFED.bit.DBFED = 50;
    EPwm2Regs.DBFEDHR.bit.DBFEDHR = 0;
    EPwm2Regs.DBREDHR.bit.DBREDHR = 0;//HRDB
    EDIS;
//    EPwm2Regs.DBFEDHR.all = 0;
//    EPwm2Regs.DBREDHR.all = 0;//HRDB
    EALLOW;
//    /*高精度脉冲模块 HR寄存器*/
    EPwm2Regs.HRCNFG.all = 0x0;
    EPwm2Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO;
    EPwm2Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO;
    EPwm2Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm2Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
    EPwm2Regs.HRCNFG.bit.EDGMODE = HR_BEP;
    EPwm2Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
#if(AUTOCONVERT)
    EPwm2Regs.HRCNFG.bit.AUTOCONV = 1;
#endif
    EPwm2Regs.HRPCTL.bit.HRPE = 0;                            // control.
    EPwm2Regs.HRCNFG2.bit.CTLMODEDBFED=0;
    EPwm2Regs.HRCNFG2.bit.CTLMODEDBRED=0;
    EPwm2Regs.HRCNFG2.bit.EDGMODEDB=3;
    EDIS;
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
void HRPWM3_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;
    EDIS;

//    EALLOW;
//    PieVectTable.EPWM2_INT = &HRPWM2_CONFIG;
//    EDIS;
    /*GPIO初始化*/
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;   // Disable pull-up on GPIO5 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
    EDIS;
    /*配置TB相关寄存器*/
    EALLOW;
    EPwm3Regs.TBCTL.bit.SWFSYNC = 0;                // 0 为脉冲不同步  1 为同步
    EPwm3Regs.EPWMSYNCINSEL.bit.SEL=0x1;      //和epwm1同步
    EPwm3Regs.TBCTL.bit.PHSEN   =  TB_ENABLE;      //  相位负载使能 初始相位偏移  EPwm1Regs.TBPRD
    EPwm3Regs.TBCTR     =   0X0000;                 //清除计数器的值
    EPwm3Regs.TBPRD     =   tbprd;                //设置周期值
    EPwm3Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UP;    //上下计数模式
    EPwm3Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;    //不分频
    EPwm3Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;        //不分频
    EPwm3Regs.TBCTL.bit.FREE_SOFT = 1;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/
    EPwm3Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;  //使用影子寄存器   影子寄存器实际上是一种双缓冲机制 新的数据被写入活动寄存器之前，它首先在影子寄存器中进行缓存。
    EPwm3Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;  //当用户想要改变PWM（脉冲宽度调制）的参数时，不是直接写入正在使用的寄存器，而是先将新值写入对应的影子寄存器。
    EPwm3Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_ZERO;//CTR=0时加载
    EPwm3Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_ZERO;//CTR=0时加载
    /*比较值设置*/
   EPwm3Regs.CMPA.bit.CMPA = (EPwm3Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值A
   EPwm3Regs.CMPB.bit.CMPB = (EPwm3Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B
   /*初始化动作限定模块 （配置AQ寄存器）*/

   EPwm3Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
   EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;

   EPwm3Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
   EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;

    /*死区控制模块 DB寄存器*/
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm3Regs.DBCTL.bit.IN_MODE = DBB_ALL;
    // 200ns  == 200/5
    EPwm3Regs.DBRED.bit.DBRED = 40;
    EPwm3Regs.DBFED.bit.DBFED = 40;
    EPwm3Regs.DBFEDHR.bit.DBFEDHR = 0;
    EPwm3Regs.DBREDHR.bit.DBREDHR = 0;//HRDB
    EDIS;
//    EPwm3Regs.DBFEDHR.all = 0;
//    EPwm3Regs.DBREDHR.all = 0;//HRDB
    EALLOW;
    /*高精度脉冲模块 HR寄存器*/
    EPwm3Regs.HRCNFG.all = 0x0;
    EPwm3Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO;
    EPwm3Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO;
    EPwm3Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm3Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
    EPwm3Regs.HRCNFG.bit.EDGMODE = HR_BEP;
    EPwm3Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
#if(AUTOCONVERT)
    EPwm3Regs.HRCNFG.bit.AUTOCONV = 1;
#endif
    EPwm3Regs.HRPCTL.bit.HRPE = 0;                            // control.
    EPwm3Regs.HRCNFG2.bit.CTLMODEDBFED=0;
    EPwm3Regs.HRCNFG2.bit.CTLMODEDBRED=0;
    EPwm3Regs.HRCNFG2.bit.EDGMODEDB=3;
    EDIS;
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}


void HRPMW4_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
    EDIS;
    /*GPIO初始化*/
    InitEPwm4Gpio();
    /*配置TB相关寄存器*/
    EPwm4Regs.TBCTL.bit.SWFSYNC = 0;
    EPwm4Regs.EPWMSYNCINSEL.bit.SEL=0x1;
    EPwm4Regs.TBCTL.bit.PHSEN   =  TB_DISABLE;
    EPwm4Regs.TBCTR     =   0X0000;
    EPwm4Regs.TBPRD     =   tbprd;
    EPwm4Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UPDOWN;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;
    EPwm4Regs.TBCTL.bit.FREE_SOFT = 11;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/
    EPwm4Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_PRD;
    EPwm4Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_PRD;
    /*比较值设置*/
   EPwm4Regs.CMPA.bit.CMPA = (EPwm4Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值A
   EPwm4Regs.CMPB.bit.CMPB = (EPwm4Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B
   /*初始化动作限定模块 （配置AQ寄存器）*/
   EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
   EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
   EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;
   EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    /*死区控制模块 DB寄存器*/
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm4Regs.DBRED.all = 80;           //800n   8.3n  24*8.33=200n
    EPwm4Regs.DBFED.all = 80;
//    EPwm4Regs.DBFEDHR.all = 0;
//    EPwm4Regs.DBREDHR.all = 0;//HRDB
    EALLOW;
//    /*高精度脉冲模块 HR寄存器*/
//    EPwm4Regs.HRCNFG.all = 0x0;
//    EPwm4Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO_PRD;
//    EPwm4Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO_PRD;
//    EPwm4Regs.HRCNFG.bit.CTLMODE = HR_CMP;
//    EPwm4Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
//    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
//    EPwm4Regs.HRCNFG.bit.EDGMODE = HR_BEP;
//    EPwm4Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
//#if(AUTOCONVERT)
//    EPwm4Regs.HRCNFG.bit.AUTOCONV = 1;
//#endif
//    EPwm4Regs.HRPCTL.bit.HRPE = 0;                            // control.
//    EPwm4Regs.HRCNFG2.bit.CTLMODEDBFED=2;
//    EPwm4Regs.HRCNFG2.bit.CTLMODEDBRED=2;
//    EPwm4Regs.HRCNFG2.bit.EDGMODEDB=3;
    EDIS;
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void HRPMW5_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;
    EDIS;
    /*GPIO初始化*/
    InitEPwm5Gpio();
    /*配置TB相关寄存器*/
    EPwm5Regs.TBCTL.bit.SWFSYNC = 0;
    EPwm5Regs.EPWMSYNCINSEL.bit.SEL=0x1;
    EPwm5Regs.TBCTL.bit.PHSEN   =  TB_DISABLE;
    EPwm5Regs.TBCTR     =   0X0000;
    EPwm5Regs.TBPRD     =   tbprd;
    EPwm5Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UPDOWN;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;
    EPwm5Regs.TBCTL.bit.FREE_SOFT = 11;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/
    EPwm5Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_PRD;
    EPwm5Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_PRD;
    /*比较值设置*/
   EPwm5Regs.CMPA.bit.CMPA = (EPwm5Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值A
   EPwm5Regs.CMPB.bit.CMPB = (EPwm5Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B
   /*初始化动作限定模块 （配置AQ寄存器）*/
   EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
   EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;
   EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    /*死区控制模块 DB寄存器*/
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm5Regs.DBRED.all = 80;           //800n   8.3n  24*8.33=200n
    EPwm5Regs.DBFED.all = 80;
//    EPwm5Regs.DBFEDHR.all = 0;
//    EPwm5Regs.DBREDHR.all = 0;//HRDB
    EALLOW;
//    /*高精度脉冲模块 HR寄存器*/
//    EPwm5Regs.HRCNFG.all = 0x0;
//    EPwm5Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO_PRD;
//    EPwm5Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO_PRD;
//    EPwm5Regs.HRCNFG.bit.CTLMODE = HR_CMP;
//    EPwm5Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
//    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
//    EPwm5Regs.HRCNFG.bit.EDGMODE = HR_BEP;
//    EPwm5Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
//#if(AUTOCONVERT)
//    EPwm5Regs.HRCNFG.bit.AUTOCONV = 1;
//#endif
//    EPwm5Regs.HRPCTL.bit.HRPE = 0;                            // control.
//    EPwm5Regs.HRCNFG2.bit.CTLMODEDBFED=2;
//    EPwm5Regs.HRCNFG2.bit.CTLMODEDBRED=2;
//    EPwm5Regs.HRCNFG2.bit.EDGMODEDB=3;
    EDIS;
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
void HRPMW6_INIT(Uint16 tbprd){
    EALLOW;
    /*失能时基模块时钟*/
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    /*使能ePWM外设时钟*/
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
    EDIS;
    /*GPIO初始化*/
    InitEPwm6Gpio();
    /*配置TB相关寄存器*/
    EPwm6Regs.TBCTL.bit.SWFSYNC = 0;
    EPwm6Regs.EPWMSYNCINSEL.bit.SEL=0x1;
    EPwm6Regs.TBCTL.bit.PHSEN   =  TB_DISABLE;
    EPwm6Regs.TBCTR     =   0X0000;
    EPwm6Regs.TBPRD     =   tbprd;
    EPwm6Regs.TBCTL.bit.CTRMODE =   TB_COUNT_UPDOWN;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV   =   TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV  =   TB_DIV1;
    EPwm6Regs.TBCTL.bit.FREE_SOFT = 11;
    /*比较模块配置（cc相关寄存器）  0 0 0 0*/
    EPwm6Regs.CMPCTL.bit.SHDWAMODE  =   CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE  =   CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE  =   CC_CTR_PRD;
    EPwm6Regs.CMPCTL.bit.LOADBMODE  =   CC_CTR_PRD;
    /*比较值设置*/
   EPwm6Regs.CMPA.bit.CMPA = (EPwm6Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值A
   EPwm6Regs.CMPB.bit.CMPB = (EPwm6Regs.TBPRD)* (0);       //占空比设定0;                             // 设置比较值B
   /*初始化动作限定模块 （配置AQ寄存器）*/
   EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
   EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
   EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;
   EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    /*死区控制模块 DB寄存器*/
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LO;/*POLSEL为极性控制位，默认不翻转，01为PWMA反转，10为PWMB反转，11为PWMA和PWMB同时反转。本实例输出需要做互补，因此可先把PMWA和PWMB设置为一样的状态，再将DBCTR.POLSEL配置为10。*/
    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm6Regs.DBRED.all = 80;           //800n   8.3n  24*8.33=200n
    EPwm6Regs.DBFED.all = 80;
//    EPwm6Regs.DBFEDHR.all = 0;
//    EPwm6Regs.DBREDHR.all = 0;//HRDB
    EALLOW;
//    /*高精度脉冲模块 HR寄存器*/
//    EPwm6Regs.HRCNFG.all = 0x0;
//    EPwm6Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO_PRD;
//    EPwm6Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO_PRD;
//    EPwm6Regs.HRCNFG.bit.CTLMODE = HR_CMP;
//    EPwm6Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
//    //EPwm1Regs.HRCNFG.bit.SELOUTB=0;
//    EPwm6Regs.HRCNFG.bit.EDGMODE = HR_BEP;
//    EPwm6Regs.HRCNFG.bit.EDGMODEB = HR_BEP;
//#if(AUTOCONVERT)
//    EPwm6Regs.HRCNFG.bit.AUTOCONV = 1;
//#endif
//    EPwm6Regs.HRPCTL.bit.HRPE = 0;                            // control.
//    EPwm6Regs.HRCNFG2.bit.CTLMODEDBFED=2;
//    EPwm6Regs.HRCNFG2.bit.CTLMODEDBRED=2;
//    EPwm6Regs.HRCNFG2.bit.EDGMODEDB=3;
    EDIS;
    /*使能时基模块时钟*/
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void HRPWM_INIT(Uint16 tbprd){
    HRPMW1_INIT(tbprd);
    HRPMW2_INIT(tbprd);
    HRPWM3_INIT(tbprd);
    HRPMW4_INIT(tbprd);
    HRPMW5_INIT(tbprd);
    HRPMW6_INIT(tbprd);
}

void HRPWM1_SetCompare(Uint32 val){
    Uint32 temp, temp1;
    Uint16 CMPA_reg_val;
    Uint16 CMPAHR_reg_val;
    Uint16 CMPB_reg_val;
    Uint16 CMPBHR_reg_val;
    //Q15格式   最大为0x7FDF 0-327668 0-100
    CMPA_reg_val = ((long)val * ((EPwm1Regs.TBPRD + 1))) >> 15;
    CMPB_reg_val = ((long)val * ((EPwm1Regs.TBPRD + 1))) >> 15;
    temp = ((long)val * ((EPwm1Regs.TBPRD + 1))) ;
    temp1 = ((long)val * ((EPwm1Regs.TBPRD + 1))) ;
    temp = temp - ((long)CMPA_reg_val << 15);
    temp1 = temp1 - ((long)CMPB_reg_val << 15);
#if(AUTOCONVERT)
    CMPAHR_reg_val = temp << 1; // convert to Q16
    CMPBHR_reg_val = temp << 1; // convert to Q16
#else
    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPAHR_reg_val = CMPAHR_reg_val << 8;
    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPBHR_reg_val = CMPBHR_reg_val << 8;
   #endif
    EPwm1Regs.CMPA.all = ((long)CMPA_reg_val) << 16 |CMPAHR_reg_val;
    EPwm1Regs.CMPB.all = ((long)CMPB_reg_val) << 16 |CMPBHR_reg_val;

}
void HRPWM2_SetCompare(Uint16 val){
    Uint32 temp, temp1;
    Uint16 CMPA_reg_val;
    Uint16 CMPAHR_reg_val;
    Uint16 CMPB_reg_val;
    Uint16 CMPBHR_reg_val;

    //Q15格式   最大为0x7FDF  32735 0.999
    CMPA_reg_val = ((long)val * ((EPwm2Regs.TBPRD + 1))) >> 15;
    CMPB_reg_val = ((long)val * ((EPwm2Regs.TBPRD + 1))) >> 15;
    temp = ((long)val * ((EPwm2Regs.TBPRD + 1))) ;
    temp1 = ((long)val * ((EPwm2Regs.TBPRD + 1))) ;
    temp = temp - ((long)CMPA_reg_val << 15);
    temp1 = temp1 - ((long)CMPB_reg_val << 15);
#if(AUTOCONVERT)
    CMPAHR_reg_val = temp << 1; // convert to Q16
    CMPBHR_reg_val = temp << 1; // convert to Q16
#else
    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPAHR_reg_val = CMPAHR_reg_val << 8;
    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPBHR_reg_val = CMPBHR_reg_val << 8;
   #endif
    EPwm2Regs.CMPA.all = ((long)CMPA_reg_val) << 16 |CMPAHR_reg_val;
    EPwm2Regs.CMPB.all = ((long)CMPB_reg_val) << 16 |CMPBHR_reg_val;
}
void HRPWM3_SetCompare(Uint16 val){
    Uint32 temp, temp1;
    Uint16 CMPA_reg_val;
    Uint16 CMPAHR_reg_val;
    Uint16 CMPB_reg_val;
    Uint16 CMPBHR_reg_val;
    //Q15格式   最大为0x7FDF  32735 0.999
    CMPA_reg_val = ((long)val * ((EPwm3Regs.TBPRD + 1))) >> 15;
    CMPB_reg_val = ((long)val * ((EPwm3Regs.TBPRD + 1))) >> 15;
    temp = ((long)val * ((EPwm3Regs.TBPRD + 1))) ;
    temp1 = ((long)val * ((EPwm3Regs.TBPRD + 1))) ;
    temp = temp - ((long)CMPA_reg_val << 15);
    temp1 = temp1 - ((long)CMPB_reg_val << 15);
#if(AUTOCONVERT)
    CMPAHR_reg_val = temp << 1; // convert to Q16
    CMPBHR_reg_val = temp << 1; // convert to Q16
#else
    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPAHR_reg_val = CMPAHR_reg_val << 8;
    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPBHR_reg_val = CMPBHR_reg_val << 8;
   #endif
    EPwm3Regs.CMPA.all = ((long)CMPA_reg_val) << 16 |CMPAHR_reg_val;
    EPwm3Regs.CMPB.all = ((long)CMPB_reg_val) << 16 |CMPBHR_reg_val;
}

void HRPWM4_SetCompare(Uint16 val){

    Uint32 temp, temp1;
    Uint16 CMPA_reg_val;
    Uint16 CMPAHR_reg_val;
    Uint16 CMPB_reg_val;
    Uint16 CMPBHR_reg_val;
    //Q15格式   最大为0x7FDF  32735 0.999
    CMPA_reg_val = ((long)val * ((EPwm3Regs.TBPRD + 1))) >> 15;
    CMPB_reg_val = ((long)val * ((EPwm3Regs.TBPRD + 1))) >> 15;
    temp = ((long)val * ((EPwm3Regs.TBPRD + 1))) ;
    temp1 = ((long)val * ((EPwm3Regs.TBPRD + 1))) ;
    temp = temp - ((long)CMPA_reg_val << 15);
    temp1 = temp1 - ((long)CMPB_reg_val << 15);
#if(AUTOCONVERT)
    CMPAHR_reg_val = temp << 1; // convert to Q16
    CMPBHR_reg_val = temp << 1; // convert to Q16
#else
    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPAHR_reg_val = CMPAHR_reg_val << 8;
    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                      (0x0080 << 7)) >> 15;
    CMPBHR_reg_val = CMPBHR_reg_val << 8;
   #endif
    EPwm4Regs.CMPA.all = ((long)CMPA_reg_val) << 16 |CMPAHR_reg_val;
    EPwm4Regs.CMPB.all = ((long)CMPB_reg_val) << 16 |CMPBHR_reg_val;

}
__interrupt void HRPWM1_CONFIG(){


    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}
__interrupt void HRPWM2_CONFIG(){


    EPwm2Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}
__interrupt void HRPWM3_CONFIG(){


    EPwm3Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}
void HRPWM1_CMP_Set(Uint16 Val){
    EPwm1Regs.CMPA.bit.CMPA  =   Val;
    EPwm1Regs.CMPB.bit.CMPB  =   Val;
}
void HRPWM2_CMP_Set(Uint16 Val){
    EPwm2Regs.CMPA.bit.CMPA  =   Val;
    EPwm2Regs.CMPB.bit.CMPB  =   Val;
}
void HRPWM3_CMP_Set(Uint16 Val){
    EPwm3Regs.CMPA.bit.CMPA  =   Val;
    EPwm3Regs.CMPB.bit.CMPB  =   Val;
}
void HRPWM4_CMP_Set(Uint16 Val){
    EPwm4Regs.CMPA.bit.CMPA  =   Val;
    EPwm4Regs.CMPB.bit.CMPB  =  Val;
}
void HRPWM5_CMP_Set(Uint16 Val){
    EPwm5Regs.CMPA.bit.CMPA  =   Val;
    EPwm5Regs.CMPB.bit.CMPB  =   Val;
}
void HRPWM6_CMP_Set(Uint16 Val){
    EPwm6Regs.CMPA.bit.CMPA  =  Val;
    EPwm6Regs.CMPB.bit.CMPB  =  Val;
}
