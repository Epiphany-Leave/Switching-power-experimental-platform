void TZ_Init(Uint16 Val){
    EALLOW;

    AnalogSubsysRegs.CMPHPMXSEL.bit.CMP3HPMXSEL = 2;    // 选择GPIO10----I_PFC引脚作为高侧比较器1的同向输入端

    Cmpss3Regs.COMPCTL.bit.COMPDACE = 1;                // 使能DAC和比较器
    Cmpss3Regs.COMPCTL.bit.COMPHSOURCE =0;              // 比较器负链接DAC
    Cmpss3Regs.COMPCTL.bit.COMPHINV = 0;                // 比较器输出不反向
    Cmpss3Regs.COMPCTL.bit.ASYNCHEN = 0;                // 不馈入数字锁存滤波输出到OR门
    Cmpss3Regs.COMPCTL.bit.CTRIPOUTHSEL = 0;            // 比较器异步输出驱动CTRIPOUTH
    Cmpss3Regs.COMPCTL.bit.CTRIPLSEL = 0;               // 比较器异步输出驱动CTRIPH

    Cmpss3Regs.COMPDACCTL.bit.DACSOURCE = 0;            // DAC更新数据来自于其影子寄存器
    Cmpss3Regs.COMPDACCTL.bit.SELREF = 0;               // VDDA作为DAC的参考电压
    Cmpss3Regs.COMPDACCTL.bit.SWLOADSEL = 0;            // 使用系统时钟同步DAC

    Cmpss3Regs.DACHVALS.bit.DACVAL = Val;               // V-等于DACVAL*(VDDA-VSSA)/1023
    Cmpss3Regs.COMPHYSCTL.bit.COMPHYS = 4;              // 设置滞环宽度

    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;            // LINK TRIPIN4
    EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = 3;            // TRIPIN4触发

    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;          // DCAEVT1信号
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;            // EPWMCLK同步

    EPwm1Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;          // DCAEVT2信号
    EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 0;            // EPWMCLK同步

    EPwm1Regs.TZDCSEL.bit.DCAEVT2   =   2;              // 跳闸触发事件 DCAH = high,
    EPwm1Regs.TZSEL.bit.DCAEVT2     =   1;              // 使能DCAEVT2信号源
    EPwm1Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;    // 跳闸触发后PWM拉低


    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 3;            // LINK TRIPIN4
    EPwm2Regs.DCTRIPSEL.bit.DCALCOMPSEL = 3;            // TRIPIN4触发

    EPwm2Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;          // DCAEVT1信号
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = 0;            // EPWMCLK同步

    EPwm2Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;          // DCAEVT2信号
    EPwm2Regs.DCACTL.bit.EVT2FRCSYNCSEL = 0;            // EPWMCLK同步

    EPwm2Regs.TZDCSEL.bit.DCAEVT2   =   2;              // 跳闸触发事件 DCAH = high,
    EPwm2Regs.TZSEL.bit.DCAEVT2     =   1;              // 使能DCAEVT2信号源
    EPwm2Regs.TZCTL.bit.TZA         =   TZ_FORCE_LO;    // 跳闸触发后PWM拉低


    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0 = 0;         //
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0 = 1;           // TRIP4使能
    EDIS;

}
