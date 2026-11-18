

#ifndef _ALG_PID_H
#define _ALG_PID_H


#include "system_typedef.h"


typedef struct PI
{
    float P;             
    float I;             
    float OutputMax;      
    float OutputMin;    
    float LastError;    
    float Output;    
}PI;
void PI_Init(PI *pid,float Kp,float Ki,float max,float min);
float IncPIDCal(PI *pid, float NowValue, float AimValue);
void PI_clc(PI *pid);
#endif


