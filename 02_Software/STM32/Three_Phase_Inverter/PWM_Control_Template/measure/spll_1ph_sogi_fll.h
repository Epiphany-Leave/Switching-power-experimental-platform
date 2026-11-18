//#############################################################################
//
// FILE:      spll_1ph_sogi_fll.h
//
// TITLE:     Orthogonal Signal Generator Software Phase Lock Loop (SPLL) for 
//            Single Phase Grid with Frequency Locked Loop (FLL) Module
//
//#############################################################################
// $TI Release: Software Phase Lock Loop Library v1.03.00.00 $
// $Release Date: Tue Mar 23 14:55:34 CDT 2021 $
// $Copyright:
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
//
// ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef SPLL_1PH_SOGI_FLL_H
#define SPLL_1PH_SOGI_FLL_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup SPLL_1PH_SOGI_FLL
//! @{
//
//*****************************************************************************

//
// Included Files
//
#include <stdint.h>
#ifndef __TMS320C28XX_CLA__
#include <math.h>
#else
#include <CLAmath.h>
#endif

//#############################################################################
//
// Macro Definitions
//
//#############################################################################
#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float         float32_t;
typedef double        float64_t;
#else // TI COFF
typedef float         float32_t;
typedef long double   float64_t;
#endif // __TI_EABI__
#endif // C2000_IEEE754_TYPES

//
// Typedefs
//

//! \brief Defines the SPLL_1PH_SOGI_FLL_OSG_COEFF structure
//!
typedef volatile struct{
    float32_t osg_b0;
    float32_t osg_b2;
    float32_t osg_a1;
    float32_t osg_a2;
    float32_t osg_qb0;
    float32_t osg_qb1;
    float32_t osg_qb2;
} SPLL_1PH_SOGI_FLL_OSG_COEFF;

//! \brief Defines the SPLL_1PH_SOGI_FLL_LPF_COEFF structure
//!
typedef struct{
    float32_t b1;
    float32_t b0;
} SPLL_1PH_SOGI_FLL_LPF_COEFF;

//! \brief Defines the Orthogonal Signal Generator SPLL_1PH_SOGI_FLL structure
//!
//!
//! \details The SPLL_1PH_SOGI_FLL can be used to generate the
//!          orthogonal signal from the sensed single phase grid voltage
//!          and use that information to provide phase of the grid voltage
//!          This module also runs a frequency locked loop for adjusting the
//!          the center frequency automatically
//!
typedef struct{
    float32_t   u[3];       //!< AC input data buffer
    float32_t   osg_u[3];   //!< Orthogonal signal generator data buffer
    float32_t   osg_qu[3];  //!< Orthogonal signal generator quadrature data buffer
    float32_t   u_Q[2];     //!< Q-axis component
    float32_t   u_D[2];     //!< D-axis component
    float32_t   ylf[2];     //!< Loop filter data storage
    float32_t   fo;         //!< Output frequency of PLL(Hz)
    float32_t   fn;         //!< Nominal frequency (Hz)
    float32_t   wc;         //!< Center (Nominal) frequency in radians
    float32_t   theta;      //!< Angle output (0-2*pi)
    float32_t   cosine;     //!< Cosine value of the PLL angle
    float32_t   sine;       //!< Sine value of the PLL angle
    float32_t   delta_t;    //!< Inverse of the ISR rate at which module is called
    float32_t   ef2;        //!< FLL parameter
    float32_t   x3[2];      //!< FLL data storage
    float32_t   w_dash;     //!< Output frequency of PLL(radians)
    float32_t   gamma;      //!< Gamma parameter for FLL
    float32_t   k;          //!< K parameter for FLL
    SPLL_1PH_SOGI_FLL_OSG_COEFF osg_coeff; //!< Orthogonal signal generator coefficient
    SPLL_1PH_SOGI_FLL_LPF_COEFF lpf_coeff; //!< Loop filter coeffcient structure
} SPLL_1PH_SOGI_FLL;

//! \brief Resets internal data to zero,
//! \param *spll_obj  The SPLL_1PH_SOGI_FLL structure pointer
//! \return None
//!
static inline void SPLL_1PH_SOGI_FLL_reset(SPLL_1PH_SOGI_FLL *spll_obj)
{
    spll_obj->u[0]=(float32_t)(0.0);
    spll_obj->u[1]=(float32_t)(0.0);
    spll_obj->u[2]=(float32_t)(0.0);
    
    spll_obj->osg_u[0]=(float32_t)(0.0);
    spll_obj->osg_u[1]=(float32_t)(0.0);
    spll_obj->osg_u[2]=(float32_t)(0.0);
    
    spll_obj->osg_qu[0]=(float32_t)(0.0);
    spll_obj->osg_qu[1]=(float32_t)(0.0);
    spll_obj->osg_qu[2]=(float32_t)(0.0);
    
    spll_obj->u_Q[0]=(float32_t)(0.0);
    spll_obj->u_Q[1]=(float32_t)(0.0);
    
    spll_obj->u_D[0]=(float32_t)(0.0);
    spll_obj->u_D[1]=(float32_t)(0.0);
    
    spll_obj->ylf[0]=(float32_t)(0.0);
    spll_obj->ylf[1]=(float32_t)(0.0);
    
    spll_obj->fo=(float32_t)(0.0);
    
    spll_obj->theta=(float32_t)(0.0);
    
    spll_obj->sine=(float32_t)(0.0);
    spll_obj->cosine=(float32_t)(0.0);

    spll_obj->x3[0]=0;
    spll_obj->x3[1]=0;

    spll_obj->ef2=0;
}

//! \brief Calculates the SPLL_1PH_SOGI_FLL coefficients
//! \param *spll_obj The SPLL_1PH_SOGI_FLL structure pointer
//! \return None
//!
static inline void SPLL_1PH_SOGI_FLL_coeff_calc(SPLL_1PH_SOGI_FLL *spll_obj)
{
    float32_t osgx,osgy,temp;

    osgx = (float32_t)(2.0f*spll_obj->k*spll_obj->w_dash*spll_obj->delta_t);
    osgy = (float32_t)(spll_obj->w_dash*spll_obj->delta_t*spll_obj->w_dash*spll_obj->delta_t);
    temp = (float32_t)1.0f/(osgx+osgy+4.0f);

    spll_obj->osg_coeff.osg_b0=((float32_t)osgx*temp);
    spll_obj->osg_coeff.osg_b2=((float32_t)(-1.0f)*spll_obj->osg_coeff.osg_b0);
    spll_obj->osg_coeff.osg_a1=((float32_t)(2.0f*(4.0f-osgy))*temp);
    spll_obj->osg_coeff.osg_a2=((float32_t)(osgx-osgy-4)*temp);

    spll_obj->osg_coeff.osg_qb0=((float32_t)(spll_obj->k*osgy)*temp);
    spll_obj->osg_coeff.osg_qb1=(spll_obj->osg_coeff.osg_qb0*(float32_t)(2.0));
    spll_obj->osg_coeff.osg_qb2=spll_obj->osg_coeff.osg_qb0;

    spll_obj->x3[0]=0;
    spll_obj->x3[1]=0;
}

//! \brief  Configures the SPLL_1PH_SOGI_FLL coefficients
//! \param  *spll_obj The SPLL_1PH_SOGI_FLL structure pointer
//! \param  acFreq Nominal AC frequency for the SPLL Module
//! \param  isrFrequency Nominal AC frequency for the SPLL Module
//! \param  lpf_b0 B0 coefficient of LPF of SPLL
//! \param  lpf_b1 B1 coefficient of LPF of SPLL
//! \param  k k parameter for FLL
//! \param  gamma gamma parameter for FLL
//! \return None
//!
static inline void SPLL_1PH_SOGI_FLL_config(SPLL_1PH_SOGI_FLL *spll_obj,
                         float32_t acFreq,
                         float32_t isrFrequency,
                         float32_t lpf_b0,
                         float32_t lpf_b1,
                         float32_t k,
                         float32_t gamma)
{
    spll_obj->fn=acFreq;
    spll_obj->w_dash = 2*3.14159265f*acFreq;
    spll_obj->wc = 2*3.14159265f*acFreq;
    spll_obj->delta_t=((1.0f)/isrFrequency);
    spll_obj->k=k;
    spll_obj->gamma=gamma;

    SPLL_1PH_SOGI_FLL_coeff_calc(spll_obj);

    spll_obj->lpf_coeff.b0=lpf_b0;
    spll_obj->lpf_coeff.b1=lpf_b1;
}

//! \brief  Runs SPLL_1PH_SOGI_FLL module
//! \param  *spll_obj The SPLL_1PH_SOGI_FLL structure pointer
//! \param  acValue AC grid voltage in per unit (pu)
//! \return None
//!
static inline void SPLL_1PH_SOGI_FLL_run(SPLL_1PH_SOGI_FLL *spll_obj, 
                                         float32_t acValue)
{
    float32_t osgx,osgy,temp;

    //
    // Update the spll_obj->u[0] with the grid value
    //
    spll_obj->u[0]=acValue;

    //
    // Orthogonal Signal Generator
    //
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

    //
    // Park Transform from alpha beta to d-q axis
    //
    spll_obj->u_Q[0]=(spll_obj->cosine*spll_obj->osg_u[0]) +
                     (spll_obj->sine*spll_obj->osg_qu[0]);
    spll_obj->u_D[0]=(spll_obj->cosine*spll_obj->osg_qu[0]) -
                     (spll_obj->sine*spll_obj->osg_u[0]);

    //
    // Loop Filter
    //
    spll_obj->ylf[0]=spll_obj->ylf[1] +
                     (spll_obj->lpf_coeff.b0*spll_obj->u_Q[0]) +
                     (spll_obj->lpf_coeff.b1*spll_obj->u_Q[1]);
    spll_obj->ylf[1]=spll_obj->ylf[0];

    //spll_obj->ylf[0] = (spll_obj->ylf[0]>0.5)?0.5:spll_obj->ylf[0];
    //spll_obj->ylf[0] = (spll_obj->ylf[0]<-0.5)?-0.5:spll_obj->ylf[0];

    spll_obj->u_Q[1]=spll_obj->u_Q[0];

    //
    // VCO
    //
    spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

    spll_obj->theta=spll_obj->theta + (spll_obj->fo*spll_obj->delta_t)*
                    (float32_t)(2.0*3.1415926f);

    if(spll_obj->theta>(float32_t)(2.0*3.1415926f))
    {
        spll_obj->theta=spll_obj->theta-(float32_t)(2.0*3.1415926f);
    }

    spll_obj->sine=(float32_t)sinf(spll_obj->theta);
    spll_obj->cosine=(float32_t)cosf(spll_obj->theta);

    //
    // FLL
    //
    spll_obj->ef2 = ((spll_obj->u[0] - spll_obj->osg_u[0])*spll_obj->osg_qu[0])
                    * spll_obj->gamma * spll_obj->delta_t*-1.0f;

    spll_obj->x3[0]=spll_obj->x3[1] + spll_obj->ef2;

    //spll_obj->x3[0]= (spll_obj->x3[0]>1.0)?1.0:spll_obj->x3[0];
    //spll_obj->x3[0]= (spll_obj->x3[0]<-1.0)?-1.0:spll_obj->x3[0];

    spll_obj->x3[1]=spll_obj->x3[0];

    spll_obj->w_dash = spll_obj->wc + spll_obj->x3[0];

    spll_obj->fn = spll_obj->w_dash / (2.0*3.1415926f);

    osgx = (float32_t)(2.0f*spll_obj->k*spll_obj->w_dash*spll_obj->delta_t);
    osgy = (float32_t)(spll_obj->w_dash * spll_obj->delta_t * spll_obj->w_dash *
                   spll_obj->delta_t);
    temp = (float32_t)1.0f/(osgx+osgy+4.0f);

    spll_obj->osg_coeff.osg_b0=((float32_t)osgx*temp);
    spll_obj->osg_coeff.osg_b2=((float32_t)(-1.0f)*spll_obj->osg_coeff.osg_b0);
    spll_obj->osg_coeff.osg_a1=((float32_t)(2.0f*(4.0f-osgy))*temp);
    spll_obj->osg_coeff.osg_a2=((float32_t)(osgx-osgy-4)*temp);

    spll_obj->osg_coeff.osg_qb0=((float32_t)(spll_obj->k*osgy)*temp);
    spll_obj->osg_coeff.osg_qb1=(spll_obj->osg_coeff.osg_qb0*(float32_t)(2.0));
    spll_obj->osg_coeff.osg_qb2=spll_obj->osg_coeff.osg_qb0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif // extern "C"

#endif  // end of  _SPLL_1PH_SOGI_H_ definition

//
// End of File
//

