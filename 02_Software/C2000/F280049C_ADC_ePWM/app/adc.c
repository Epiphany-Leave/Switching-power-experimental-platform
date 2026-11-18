/*
 * adc.c
 *
 *  Created on: 2025年11月27日
 *      Author: 45276
 */

#include "adc.h"

__interrupt void adcA1ISR();

void ADCA_Init(void)
{
    EALLOW;
    PieVectTable.ADCA1_INT = &adcA1ISR;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    EDIS;

    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);   // 设置内部电压3.3V
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);   // 设置内部电压3.3V

    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE       = 6;        // 4分频  100/4
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS    = 1;        // 设置中断脉冲延迟  1:转化完成后再触发
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ       = 1;        // 接通ADC电源
    
    AdccRegs.ADCCTL2.bit.PRESCALE       = 6;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS    = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ       = 1;
    EDIS;
    DELAY_US(1000); // 然后延迟1ms，保障上电稳定

    /* EPWM1触发ADC采样配置 */
    EALLOW;
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;                // TRGO：1：TPCTR=0；2：TPCTR=TBPRD；3：TBCTR=0/TBPRD
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;
    EDIS;

    // 同步采样：不同通道，相同采样周期&触发源
    EALLOW;
    /* ADCA */
    AdcaRegs.ADCSOC0CTL.bit.CHSEL   = 0;    // A0 采样通道
    AdcaRegs.ADCSOC0CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;    // 采样触发源

    AdcaRegs.ADCSOC1CTL.bit.CHSEL   = 1;
    AdcaRegs.ADCSOC1CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;

    AdcaRegs.ADCSOC2CTL.bit.CHSEL   = 2;
    AdcaRegs.ADCSOC2CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 5;

    AdcaRegs.ADCSOC3CTL.bit.CHSEL   = 3;
    AdcaRegs.ADCSOC3CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5;

    /* ADCC */
    AdccRegs.ADCSOC0CTL.bit.CHSEL   = 0;    // C0
    AdccRegs.ADCSOC0CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;

    AdccRegs.ADCSOC1CTL.bit.CHSEL   = 1;
    AdccRegs.ADCSOC1CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 5;

    AdccRegs.ADCSOC2CTL.bit.CHSEL   = 2;
    AdccRegs.ADCSOC2CTL.bit.ACQPS   = 11;   // 采样周期--((11+1) * (1/100MHz) = 120ns)
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 5;

    AdccRegs.ADCSOC3CTL.bit.CHSEL   = 3;
    AdccRegs.ADCSOC3CTL.bit.ACQPS   = 11;
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = 5;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 3;  // EOC3触发中断（SOC3->最后一个转化结束的通道）
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1;  // 中断使能
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  // 清除中断标志位

    IER |= M_INT1;                      // Y选中
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;  // X选中
    EDIS;
}


