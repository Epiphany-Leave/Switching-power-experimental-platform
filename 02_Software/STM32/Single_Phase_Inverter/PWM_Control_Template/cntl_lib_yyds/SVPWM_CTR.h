#ifndef _SVPWM_CTR_H
#define _SVPWM_CTR_H

#include <stdint.h>
#include <math.h>
#include "my_board.h"

typedef struct
{
float a;
float b;
float c;
float alpha;
float beta;
} abc_to_alpha_beta_struct; 
typedef struct
{
float alpha;
float beta;
float theta;      
float cosine;  
float sine;     
float d;
float q;
} alpha_beta_to_dq_struct; 

typedef struct
{
float d;
float q;
float theta;      
float cosine;  
float  sine;     
float alpha;
float beta;
}dq_to_alpha_beta_struct; 


typedef struct
{
float ed;
float wl;
float id;
float iq;
float id_s;
float uq;
float ud;
} feedforward_and_decoupling_control_struct;


typedef struct
{
float ualpha;
float ubeta;
char N;
} sector_struct;

typedef struct
{
float Ts;
float ubeta;
float ualpha;
float udc;
float A;
float B;
float C;
float Ts_d_udc;
} alpha_beta_to_A_B_C_struct;


typedef struct
{
char N;
float A;
float B;
float C;
float Ts;
float Ta;
float Tb;
float Tc;
}FOC_struct; 

 void abc_to_alpha_beta(abc_to_alpha_beta_struct *a); //    /in:a;b;c;/out:alpha;beta;
 void alpha_beta_to_dq(alpha_beta_to_dq_struct *a);   //   /in:alpha;beta;omega;/out:d;q;
 void dq_to_alpha_beta(dq_to_alpha_beta_struct *a);//     /in:d;q;/out:alpha;beta;
 void feedforward_and_decoupling_control(feedforward_and_decoupling_control_struct *a,PI *pid1,PI *pid2);//    /in:ed;id*;id;iq;/out:ud;uq;
 void sector(sector_struct *a);//    /in:ualpha;ubeta;/out:N;
 void alpha_beta_to_A_B_C(alpha_beta_to_A_B_C_struct *a);//    /in:Ts;udc;ubeta;ualpha;/out:A;B;C;
 void FOC(FOC_struct *a);//    /in:N;TI;T2;Ts;/out:Ta;Tb;Tc;

#endif


