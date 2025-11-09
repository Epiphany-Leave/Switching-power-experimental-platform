#include "my_board.h"


 inline  void SPLL_1PH_SOGI_reset(SPLL_1PH_SOGI *spll_obj)
{
    spll_obj->u[0]=(float)(0.0);
    spll_obj->u[1]=(float)(0.0);
    spll_obj->u[2]=(float)(0.0);
    
    spll_obj->osg_u[0]=(float)(0.0);
    spll_obj->osg_u[1]=(float)(0.0);
    spll_obj->osg_u[2]=(float)(0.0);
    
    spll_obj->osg_qu[0]=(float)(0.0);
    spll_obj->osg_qu[1]=(float)(0.0);
    spll_obj->osg_qu[2]=(float)(0.0);
    
    spll_obj->u_Q[0]=(float)(0.0);
    spll_obj->u_Q[1]=(float)(0.0);
    
    spll_obj->u_D[0]=(float)(0.0);
    spll_obj->u_D[1]=(float)(0.0);
    
    spll_obj->ylf[0]=(float)(0.0);
    spll_obj->ylf[1]=(float)(0.0);
    
    spll_obj->fo=(float)(0.0);
    
    spll_obj->theta=(float)(0.0);
    
    spll_obj->sine=(float)(0.0);
    spll_obj->cosine=(float)(0.0);
}


 inline  void SPLL_1PH_SOGI_coeff_calc(SPLL_1PH_SOGI *spll_obj)
{
    float osgx,osgy,temp, wn;
    wn= spll_obj->fn *6.2831852f;
    spll_obj->osg_coeff.osg_k=(float)(0.5);
    osgx = (float)(1.0f*wn*spll_obj->delta_t);
    spll_obj->osg_coeff.osg_x=(float)(osgx);
    osgy = (float)(wn*spll_obj->delta_t*wn*spll_obj->delta_t);
    spll_obj->osg_coeff.osg_y=(float)(osgy);
    temp = 1.0f/(osgx+osgy+4.0f);
    spll_obj->osg_coeff.osg_b0=((float)osgx*temp);
    spll_obj->osg_coeff.osg_b2=((float)(-1.0f)*spll_obj->osg_coeff.osg_b0);
    spll_obj->osg_coeff.osg_a1=((float)(2.0f*(4.0f-osgy))*temp);
    spll_obj->osg_coeff.osg_a2=((float)(osgx-osgy-4)*temp);
    spll_obj->osg_coeff.osg_qb0=((float)(0.5f*osgy)*temp);
    spll_obj->osg_coeff.osg_qb1=(spll_obj->osg_coeff.osg_qb0*2.0f);
    spll_obj->osg_coeff.osg_qb2=spll_obj->osg_coeff.osg_qb0;
}

inline  void SPLL_1PH_SOGI_config(SPLL_1PH_SOGI *spll_obj,
                         float acFreq,
                         float isrFrequency,
                         float lpf_b0,
                         float lpf_b1)
{
    spll_obj->fn=acFreq;
    spll_obj->delta_t=((1.0f)/isrFrequency);

    SPLL_1PH_SOGI_coeff_calc(spll_obj);

    spll_obj->lpf_coeff.b0=lpf_b0;
    spll_obj->lpf_coeff.b1=lpf_b1;
}


 inline  void SPLL_1PH_SOGI_run(SPLL_1PH_SOGI *spll_obj,
                                     float acValue)
{
    // Update the spll_obj->u[0] with the grid value
	
	//Orthogonal Signal Generator//
    spll_obj->u[0]=acValue;

    
    spll_obj->osg_u[0]=(spll_obj->osg_coeff.osg_b0*
                       (spll_obj->u[0]-spll_obj->u[2])) +
                       (spll_obj->osg_coeff.osg_a1*spll_obj->osg_u[1]) +
                       (spll_obj->osg_coeff.osg_a2*spll_obj->osg_u[2]);

    spll_obj->osg_u[2]=spll_obj->osg_u[1];
    spll_obj->osg_u[1]=spll_obj->osg_u[0];
	
    spll_obj->osg_qu[0]=(spll_obj->osg_coeff.osg_qb0*spll_obj->u[0]) +
                        (spll_obj->osg_coeff.osg_qb1*spll_obj->u[1]) +
                        (spll_obj->osg_coeff.osg_qb2*spll_obj->u[2]) +
                        (spll_obj->osg_coeff.osg_a1*spll_obj->osg_qu[1]) +
                        (spll_obj->osg_coeff.osg_a2*spll_obj->osg_qu[2]);

    spll_obj->osg_qu[2]=spll_obj->osg_qu[1];
    spll_obj->osg_qu[1]=spll_obj->osg_qu[0];

    spll_obj->u[2]=spll_obj->u[1];
    spll_obj->u[1]=spll_obj->u[0];

    //Park Transform from alpha beta to d-q axis//
    spll_obj->u_Q[0]=(spll_obj->cosine*spll_obj->osg_u[0]) +
                     (spll_obj->sine*spll_obj->osg_qu[0]);
    spll_obj->u_D[0]=(spll_obj->cosine*spll_obj->osg_qu[0]) -
                     (spll_obj->sine*spll_obj->osg_u[0]);

	//LOOP Filter//
    spll_obj->ylf[0]=spll_obj->ylf[1] +
                     (spll_obj->lpf_coeff.b0*spll_obj->u_Q[0]) +
                     (spll_obj->lpf_coeff.b1*spll_obj->u_Q[1]);
    spll_obj->ylf[1]=spll_obj->ylf[0];

    spll_obj->u_Q[1]=spll_obj->u_Q[0];

	//VCO//
    spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

    spll_obj->theta=spll_obj->theta + (spll_obj->fo*spll_obj->delta_t)*
                     6.2831852f;

    if(spll_obj->theta>6.2831852f)
    {
        spll_obj->theta=spll_obj->theta - 6.2831852f;
    }


    spll_obj->sine=arm_sin_f32(spll_obj->theta);
    spll_obj->cosine=arm_cos_f32(spll_obj->theta);
}

