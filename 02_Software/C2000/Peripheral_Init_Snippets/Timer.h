#ifndef __TIMER_H__
#define __TIMER_H__
typedef struct{
    Uint32 Flag_50us    :1;
    Uint32 Flag_100us   :1;
    Uint32 Flag_1ms     :1;
    Uint32 Flag_10ms    :1;
    Uint32 Flag_100ms   :1;
    Uint32 Flag_1s      :1;
    Uint32 Cnt_50us     :4;
    Uint32 Cnt_100us    :4;
    Uint32 Cnt_1ms      :4;
    Uint32 Cnt_10ms     :4;
    Uint32 Cnt_100ms    :4;
    Uint32 Cnt_1s       :4;
    Uint32 CNT          :2;


}Timer_Base_t;

void TB_Init(Timer_Base_t *TB);
void CPUTimer0_Init(int Freq, int Period);
void CPUTimer1_Init(int Freq, int Period);

#endif
