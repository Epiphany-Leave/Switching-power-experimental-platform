#include "DAC.H"
volatile struct DAC_REGS* DAC_PTR[3] = {0x0,&DacaRegs,&DacbRegs};
void DAC_Init(Uint16 dac_num){

    EALLOW;
    /*选择参考电压源 1为内部参考 0 为外部参考*/
    DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = 1;
    /*增益 0 时增益为1 1时增益为2*/
    DAC_PTR[dac_num]->DACCTL.bit.MODE = 1;

    /*0 加载到下一个时钟 1 加载到下一个epwm时钟 绑定epwm通过SYNCSEL 寄存器位7-4*/
    DAC_PTR[dac_num]->DACCTL.bit.LOADMODE=0;
    /*1 DAC输出使能 0 DAC 输出关闭*/
    DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
    /*输出电压计算  Vdac = (DACVALA * DACREF) / 4096。*/
    DAC_PTR[dac_num]->DACVALS.all = 0;

    DELAY_US(10); // Delay for buffered DAC to power up
    EDIS;
}


void SET_DACV(Uint16 dac_num,Uint16 VAL){

    DAC_PTR[dac_num]->DACVALS.all = VAL;

}
