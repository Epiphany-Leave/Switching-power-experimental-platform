#include "f28x_project.h"
#include "Timer.h"
extern Timer_Base_t TB;
__interrupt void cpuTimer0ISR(void);
__interrupt void cpuTimer1ISR(void);
void TB_Init(Timer_Base_t *TB){
    TB->Flag_50us  =0;
    TB->Flag_100us =0;
    TB->Flag_1ms   =0;
    TB->Flag_10ms  =0;
    TB->Flag_100ms =0;
    TB->Flag_1s    =0;
    TB->Cnt_50us   =0;
    TB->Cnt_100us  =0;
    TB->Cnt_1ms    =0;
    TB->Cnt_10ms   =0;
    TB->Cnt_100ms  =0;
    TB->Cnt_1s     =0;
    TB->CNT        =0;
}

void CPUTimer0_Init(int Freq, int Period){
    EALLOW;
    PieVectTable.TIMER0_INT = &cpuTimer0ISR; //自定义的中断服务函数
    EDIS;
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, Freq, Period);

    //启动CPU定时器，并且定时器减至0时请求中断
    CpuTimer0Regs.TCR.all = 0x4000;

    //  使能CPU中断线
    //中断向量表寄存器
    IER |= M_INT1;      // Y 选中
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      //X 选中


}
void CPUTimer1_Init(int Freq, int Period){
    EALLOW;

        PieVectTable.TIMER1_INT = &cpuTimer0ISR; //自定义的中断服务函数

        EDIS;

        InitCpuTimers();

        ConfigCpuTimer(&CpuTimer1, Freq, Period);

        //启动CPU定时器，并且定时器减至0时请求中断
        CpuTimer1Regs.TCR.all = 0x4000;

        //  使能CPU中断线
        //中断向量表寄存器
        IER |= M_INT1;      // Y 选中
        PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      //X 选中

}
__interrupt void cpuTimer0ISR(void)
{
    TB.Flag_100us=1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


