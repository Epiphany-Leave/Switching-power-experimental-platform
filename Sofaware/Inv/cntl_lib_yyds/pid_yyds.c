
#include "pid_yyds.h"

 void PI_Init(PI *pid,float Kp,float Ki,float max,float min)
 {
     pid->P=Kp;
     pid->I=Ki;
     pid->OutputMax=max;
     pid->OutputMin=min;
 }

 void PI_clc(PI *pid)
 {
     pid->P=0;
     pid->I=0;
     pid->OutputMax=0;
     pid->OutputMin=0;
     pid->LastError=0;
     pid->Output=0;
 }
 float IncPIDCal(PI *pid, float NowValue, float AimValue)     
{
	float iError;                       
	float cal;                          
	iError =AimValue -NowValue;            
	cal = (pid->P * (iError-pid->LastError) )             
			+(pid->I * iError) ;     
	pid->LastError = iError;
    pid->Output+=cal;
    pid->Output = pid->Output > pid->OutputMax?pid->OutputMax:pid->Output;  
    pid->Output = pid->Output <pid->OutputMin?pid->OutputMin:pid->Output; 
	return pid->Output;                  

}

// PI控制器计算函数
float PI_Compute(PI *pid, float NowValue, float AimValue) 
{
    float error = AimValue - NowValue;

    // 计算比例部分
    float proportional = pid->P * error;

    // 计算梯形积分部分
    pid->I += ((1/20000) / 2.0f) * (error + pid->LastError) * pid->I;

    // 更新前一次的误差
    pid->LastError = error;

    // 计算输出
    float output = proportional + pid->I;

    return output;
}
