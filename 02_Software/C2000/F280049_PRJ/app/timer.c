/*
 * timer.c
 *
 *  Created on: 2025年11月12日
 *      Author: 45276
 */

#include "timer.h"

void Timer0Init(int cpu_mhz, int period_us)
{
    // 1) 计算并写入 PRD/TPR/TPRH，ConfigCpuTimer 会做一次初始配置
    ConfigCpuTimer(&CpuTimer0, cpu_mhz, period_us);
    CpuTimer0Regs.TCR.all = 0x4000;

//    EALLOW;
//
//    // 2) 停表后清标志、配置位（顺序很重要）
//    CpuTimer0Regs.TCR.bit.TSS  = 1;   // 先停表，确保后续操作稳定
//    CpuTimer0Regs.TCR.bit.TIF  = 1;   // 写1清中断标志
//    CpuTimer0Regs.TCR.bit.TIE  = 1;   // 允许中断
//    CpuTimer0Regs.TCR.bit.FREE = 1;   // Debug 下自由运行
//    CpuTimer0Regs.TCR.bit.SOFT = 1;
//
//    CpuTimer0Regs.TCR.bit.TRB  = 1;   // ★★★ 关键：最终配置完成后强制重装载
//    CpuTimer0Regs.TCR.bit.TSS  = 0;   // 启动计时器
//
//    EDIS;
}



