
#include <stdint.h>
#include <math.h>
#include "my_board.h"
abc_to_alpha_beta_struct abc_to_alpha_beta_struct_U;
abc_to_alpha_beta_struct abc_to_alpha_beta_struct_I;
alpha_beta_to_dq_struct alpha_beta_to_dq_struct_U;  
alpha_beta_to_dq_struct alpha_beta_to_dq_struct_I;  
dq_to_alpha_beta_struct dq_to_alpha_beta_struct_0;
feedforward_and_decoupling_control_struct feedforward_and_decoupling_control_struct_0;
sector_struct sector_struct_0;
alpha_beta_to_A_B_C_struct alpha_beta_to_A_B_C_struct_0;
FOC_struct FOC_struct_0;


//abc坐标系向αβ坐标系变换
void abc_to_alpha_beta(abc_to_alpha_beta_struct *a)
{
a->alpha=(2*a->a-a->b-a->c)*0.3333f;
a->beta=(a->b-a->c)*0.577f;
}

//αβ坐标系向dq坐标系变换
void alpha_beta_to_dq(alpha_beta_to_dq_struct *a)
{
a->d=a->cosine*a->alpha+a->sine*a->beta;
a->q=a->sine*a->alpha-a->cosine*a->beta;
}



//dq坐标系向αβ坐标系变换
void dq_to_alpha_beta(dq_to_alpha_beta_struct *a)
{
a->alpha=a->cosine*a->d+a->sine*a->q;
a->beta=a->sine*a->d-a->cosine*a->q;
}




//前馈解耦控制
void feedforward_and_decoupling_control(feedforward_and_decoupling_control_struct *a,PI *pid_id,PI *pid_iq)
{
a->ud=-(float)IncPIDCal( pid_id, a->id, a->id_s)+a->wl*a->iq+a->ed;
a->uq=-(float)IncPIDCal( pid_iq, a->iq, 0)-a->wl*a->id;
}



//扇区判断
void sector(sector_struct *a)
{
a->N=0;
if(a->ubeta>=0.0f)
a->N++;
if(0.866f*a->ualpha-0.5f*a->ubeta>=0.0f)
a->N+=2;
if(-0.866f*a->ualpha-0.5f*a->ubeta>=0.0f)
a->N+=4;
if(a->N==7||a->N==0)
a->N=1;
}



//ABC时间的求取
void alpha_beta_to_A_B_C(alpha_beta_to_A_B_C_struct *a)
{
    a->Ts_d_udc=1.0f/a->udc;
    a->A=1.732f*a->ubeta*a->Ts_d_udc;
    a->B=(1.5f*a->ualpha+0.866f*a->ubeta)*a->Ts_d_udc;
    a->C=(1.5f*a->ualpha-0.866f*a->ubeta)*a->Ts_d_udc;
}


//矢量控制
void FOC(FOC_struct *a)
{
switch(a->N)
{
case 1:
{
a->Ta=(a->Ts+a->C+a->B)*0.5f;
a->Tb=(a->Ts-a->C+a->B)*0.5f;
a->Tc=(a->Ts+a->C-a->B)*0.5f ;
break;
}
case 2:
{
a->Ta=(a->Ts-a->A+a->B)*0.5f;
a->Tb=(a->Ts+a->A-a->B)*0.5f;
a->Tc=(a->Ts-a->A-a->B)*0.5f;
break;
}
case 3:
{
a->Ta=(a->Ts+a->A+a->C)*0.5f;
a->Tb=(a->Ts+a->A-a->C)*0.5f;
a->Tc=(a->Ts-a->A-a->C)*0.5f;
break;
}
case 4:
{
a->Ta=(a->Ts+a->A+a->C)*0.5f;
a->Tb=(a->Ts+a->A-a->C)*0.5f;
a->Tc=(a->Ts-a->A-a->C)*0.5f;
break;
}
case 5:
{
a->Ta=(a->Ts-a->A+a->B)*0.5f;
a->Tb=(a->Ts+a->A-a->B)*0.5f;
a->Tc=(a->Ts-a->A-a->B)*0.5f;
break;
}
case 6:
{
a->Ta=(a->Ts+a->C+a->B)*0.5f;
a->Tb=(a->Ts-a->C+a->B)*0.5f;
a->Tc=(a->Ts+a->C-a->B)*0.5f;
break;
}
}
}






