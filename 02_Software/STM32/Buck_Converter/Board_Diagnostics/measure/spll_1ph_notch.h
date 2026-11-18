//#############################################################################
//
//  FILE      spll_1ph_notch.h
//
//  TITLE     Notch Filter based Software Phase Lock Loop (SPLL) 
//            for Single Phase Grid Module
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

#ifndef SPLL_1PH_NOTCH_H
#define SPLL_1PH_NOTCH_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup SPLL_1PH_NOTCH
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

//! \brief Defines the SPLL_1PH_NOTCH_COEFF structure
//!
typedef struct{
	float32_t b2;
	float32_t b1;
	float32_t b0;
	float32_t a2;
	float32_t a1;
} SPLL_1PH_NOTCH_COEFF;

//! \brief Defines the SPLL_1PH_NOTCH_LPF_COEFF structure
//!
typedef struct{
    float32_t b1;
    float32_t b0;
    float32_t a1;
} SPLL_1PH_NOTCH_LPF_COEFF;

//! \brief Defines the SPLL_1PH_NOTCH
//!        structure
//!
//! \details The SPLL_1PH_NOTCH can be used to extract the phase of
//!          the ac grid from the sensed single phase grid voltage
//!
typedef struct{
    float32_t   upd[3];       //!< Phase detect buffer
    float32_t   y_notch1[3];  //!< Notch filter1 data storage
    float32_t   y_notch2[3];  //!< Notch filter2 data storage
    float32_t   ylf[2];       //!< Loop filter data storage
    float32_t   fo;           //!< Output frequency of PLL(Hz)
    float32_t   fn;           //!< Nominal frequency (Hz)
    float32_t   theta;        //!< Angle output (0-2*pi)
    float32_t   cosine;       //!< Cosine value of the PLL angle
    float32_t   sine;         //!< Sine value of the PLL angle
    float32_t   delta_t;      //!< Inverse of the ISR rate at which module is called
    SPLL_1PH_NOTCH_COEFF notch_coeff; //!< Notch filter coeffcient structure
    SPLL_1PH_NOTCH_LPF_COEFF lpf_coeff;     //!< Loop filter coeffcient structure
} SPLL_1PH_NOTCH;

//! \brief Resets internal data to zero,
//! \param *spll_obj The SPLL_1PH_NOTCH structure pointer
//! \return None
//!
static inline void SPLL_1PH_NOTCH_reset(SPLL_1PH_NOTCH *spll_obj)
{
    spll_obj->upd[0]=(float32_t)(0.0);
    spll_obj->upd[1]=(float32_t)(0.0);
    
    spll_obj->y_notch1[0]=(float32_t)(0.0);
    spll_obj->y_notch1[1]=(float32_t)(0.0);
    spll_obj->y_notch1[2]=(float32_t)(0.0);
    
    spll_obj->y_notch2[0]=(float32_t)(0.0);
    spll_obj->y_notch2[1]=(float32_t)(0.0);
    spll_obj->y_notch2[2]=(float32_t)(0.0);
    
    spll_obj->ylf[0]=(float32_t)(0.0);
    spll_obj->ylf[1]=(float32_t)(0.0);
    
    spll_obj->fo=(float32_t)(0.0);
    
    spll_obj->theta=(float32_t)(0.0);

    spll_obj->sine=(float32_t)(0.0);
    spll_obj->cosine=(float32_t)(0.0);
}

//! \brief Calculates the coefficients for SPLL_1PH_NOTCH filter
//! \param *spll_obj The SPLL_1PH_NOTCH structure pointer
//! \param c1 c1 Notch paramater
//! \param c2 c2 Notch Parameter
//! \return None
//!
static inline void SPLL_1PH_NOTCH_coeff_calc(SPLL_1PH_NOTCH *spll_obj,
                                             float32_t c1, float32_t c2)
{
    float32_t notch_freq;
    float32_t temp1,temp2;
	float32_t wn2;
	float32_t Ts, Fs;

	notch_freq=2*3.14159265f*spll_obj->fn;
	Ts = spll_obj->delta_t;
	Fs=1/Ts;

    //
	// pre warp the notch frequency
    //
	wn2=2*Fs*tanf(notch_freq* ((float32_t)3.141592653589)*Ts);

	temp1= 4*Fs*Fs + 4* wn2 * c2 * Fs + wn2*wn2;
	temp2= 1/ ( 4*Fs*Fs + 4* wn2 * c1 * Fs + wn2*wn2);

	spll_obj->notch_coeff.b0 = temp1* temp2;
	spll_obj->notch_coeff.b1 = (-8*Fs*Fs + 2* wn2* wn2)* temp2;
	spll_obj->notch_coeff.b2 = (4*Fs*Fs-4*wn2*c2*Fs+wn2*wn2)*temp2;
	spll_obj->notch_coeff.a1 = (-8*Fs*Fs + 2* wn2* wn2)*temp2;
	spll_obj->notch_coeff.a2 = (4*Fs*Fs-4*wn2*c1*Fs+wn2*wn2)*temp2;
}


//! \brief  Configures the SPLL_1PH_NOTCH module
//! \param  *spll_obj The SPLL_1PH_NOTCH structure pointer
//! \param  acFreq Nominal AC frequency for the SPLL Module
//! \param  isrFrequency Nominal AC frequency for the SPLL Module
//! \param  lpf_b0 B0 coefficient of LPF of SPLL
//! \param  lpf_b1 B1 coefficient of LPF of SPLL
//! \param  c1 c1 Notch paramater
//! \param  c2 c2 Notch Parameter
//! \return None
//!
static inline void SPLL_1PH_NOTCH_config(SPLL_1PH_NOTCH *spll_obj,
                         float32_t acFreq,
                         float32_t isrFrequency,
                         float32_t lpf_b0,
                         float32_t lpf_b1,
                         float32_t c1,
                         float32_t c2
                         )
{
    spll_obj->fn=acFreq;
    spll_obj->delta_t=((1.0f)/isrFrequency);

    SPLL_1PH_NOTCH_coeff_calc( spll_obj,
                                   c1,
                                   c2);

    spll_obj->lpf_coeff.b0=lpf_b0;
    spll_obj->lpf_coeff.b1=lpf_b1;
}

//! \brief  Runs the SPLL_1PH_NOTCH module
//! \param  *spll_obj The SPLL_1PH_NOTCH structure pointer
//! \param  acValue AC grid voltage in per unit (pu)
//! \return None
//!
static inline void SPLL_1PH_NOTCH_run(SPLL_1PH_NOTCH *spll_obj,
                                      float32_t acValue)
{
    //
    // Phase detect
    //
	spll_obj->upd[0] = acValue*spll_obj->cosine;
	
    //
	// Notch Filter
    //
	spll_obj->y_notch1[0] = - spll_obj->y_notch1[1]*spll_obj->notch_coeff.a1
	                        - spll_obj->y_notch1[2]*spll_obj->notch_coeff.a2
	                        + spll_obj->upd[0]*spll_obj->notch_coeff.b0
	                        + spll_obj->upd[1]*spll_obj->notch_coeff.b1
	                        + spll_obj->upd[2]*spll_obj->notch_coeff.b2;

	spll_obj->y_notch2[0] = - spll_obj->y_notch2[1]*spll_obj->notch_coeff.a1
                            - spll_obj->y_notch2[2]*spll_obj->notch_coeff.a2
                            + spll_obj->y_notch1[0]*spll_obj->notch_coeff.b0
                            + spll_obj->y_notch1[1]*spll_obj->notch_coeff.b1
                            + spll_obj->y_notch1[2]*spll_obj->notch_coeff.b2;

    //
    // Loop Filter
    //
    spll_obj->ylf[0] = spll_obj->ylf[1]
                    + (spll_obj->lpf_coeff.b0*spll_obj->y_notch2[0])
                    + (spll_obj->lpf_coeff.b1*spll_obj->y_notch2[1]);

    //spll_obj->ylf[0] = (spll_obj->ylf[0]>100)?100:spll_obj->ylf[0];
    //spll_obj->ylf[0] = (spll_obj->ylf[0]<-100)?-100:spll_obj->ylf[0];

    //
	// update the Upd array for future sample
    //
	spll_obj->upd[2] = spll_obj->upd[1];
	spll_obj->upd[1] = spll_obj->upd[0];

	spll_obj->y_notch1[2] = spll_obj->y_notch1[1];
	spll_obj->y_notch1[1] = spll_obj->y_notch1[0];

	spll_obj->y_notch2[2] = spll_obj->y_notch2[1];
	spll_obj->y_notch2[1] = spll_obj->y_notch2[0];

	spll_obj->ylf[1] = spll_obj->ylf[0];

    //
    // VCO
    //
    spll_obj->fo = spll_obj->fn+spll_obj->ylf[0];

    spll_obj->theta= spll_obj->theta
          + (spll_obj->fo*spll_obj->delta_t)*(float32_t)(2.0*3.1415926);

    if(spll_obj->theta>(float32_t)(2.0*3.1415926))
    {
        spll_obj->theta =spll_obj->theta-(float32_t)(2.0*3.1415926);
    }

    spll_obj->sine = (float32_t)sinf(spll_obj->theta);
    spll_obj->cosine = (float32_t)cosf(spll_obj->theta);
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

#endif  // end of  _SPLL_1PH_NOTCH_H_ definition


//
// End of File
//

