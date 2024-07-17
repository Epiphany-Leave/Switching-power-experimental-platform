//#############################################################################
//
//  FILE:   spll_3ph_ddsrf.h
//
//  TITLE:  DDSRF PLL for Three Phase Grid Tied Systems
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

#ifndef SPLL_3PH_DDSRF_H
#define SPLL_3PH_DDSRF_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup SPLL_3PH_DDSRF
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

//! \brief          Defines the coefficients for a loop filter
//!
//! \details        Loop filter coefficients
//!
typedef struct{
    float32_t b1;
    float32_t b0;
} SPLL_3PH_DDSRF_LPF_COEFF;

//! \brief          Defines the SPLL_3PH_DDSRF structure
//!
//! \details        This software module implements a software phase lock loop
//!                 based on decoupled double synchronous reference frame for
//!                 grid connection to three phase grid
//! \return None
//!
typedef struct{
    float32_t d_p_decoupl;  //!< Positive Rotating reference Frame D-axis value
    float32_t d_n_decoupl;  //!< Negative Rotating reference Frame D-axis value
    float32_t q_p_decoupl;  //!< Positive Rotating reference Frame Q-axis value
    float32_t q_n_decoupl;  //!< Negative Rotating reference Frame Q-axis value

    float32_t cos_2theta;   //!< Cos of twice the grid frequency angle
    float32_t sin_2theta;   //!< Sin of twice the grid frequency angle

    float32_t y[2];         //!< Used to store history for filtering the decoupled D and Q axis components    
    float32_t x[2];         //!< Used to store history for filtering the decoupled D and Q axis components
    float32_t w[2];         //!< Used to store history for filtering the decoupled D and Q axis components
    float32_t z[2];         //!< Used to store history for filtering the decoupled D and Q axis components
    float32_t k1;           //!< Lpf coefficient
    float32_t k2;           //!< Lpf coefficient    
    float32_t d_p_decoupl_lpf;  //!< Decoupled positive sequence D-axis component filtered
    float32_t d_n_decoupl_lpf;  //!< Decoupled negative sequence D-axis component filtered
    float32_t q_p_decoupl_lpf;  //!< Decoupled positive sequence Q-axis component filtered
    float32_t q_n_decoupl_lpf;  //!< Decoupled negative sequence Q-axis component filtered

    float32_t v_q[2];       
    float32_t theta[2];     //!< Grid phase angle
    float32_t ylf[2];       //!< Internal Data Buffer for Loop Filter output
    float32_t fo;           //!< Instantaneous Grid Frequency in Hz
    float32_t fn;           //!< Nominal Grid Frequency in Hz
    float32_t delta_t;      //!< 1/Frequency of calling the PLL routine
    SPLL_3PH_DDSRF_LPF_COEFF lpf_coeff;
} SPLL_3PH_DDSRF;

//! \brief              Initialize SPLL_3PH_DDSRF module
//! \param grid_freq    The grid frequency
//! \param delta_t      1/Frequency of calling the PLL routine
//! \param k1           parameter
//! \param k2           parameter
//! \param *spll_obj    The SPLL_3PH_DDSRF structure
//! \return None
//!
static inline void SPLL_3PH_DDSRF_init(float32_t grid_freq, float32_t delta_t,
                                       float32_t k1, float32_t k2,
                                       SPLL_3PH_DDSRF *spll_obj)
{
    spll_obj->d_p_decoupl = (float32_t)(0.0);
    spll_obj->d_n_decoupl = (float32_t)(0.0);

    spll_obj->q_p_decoupl = (float32_t)(0.0);
    spll_obj->q_n_decoupl = (float32_t)(0.0);

    spll_obj->d_p_decoupl_lpf = (float32_t)(0.0);
    spll_obj->d_n_decoupl_lpf = (float32_t)(0.0);

    spll_obj->q_p_decoupl_lpf = (float32_t)(0.0);
    spll_obj->q_n_decoupl_lpf = (float32_t)(0.0);

    spll_obj->y[0] = (float32_t)(0.0);
    spll_obj->y[1] = (float32_t)(0.0);

    spll_obj->x[0] = (float32_t)(0.0);
    spll_obj->x[1] = (float32_t)(0.0);

    spll_obj->w[0] = (float32_t)(0.0);
    spll_obj->w[1] = (float32_t)(0.0);

    spll_obj->z[0] = (float32_t)(0.0);
    spll_obj->z[1] = (float32_t)(0.0);

    spll_obj->k1 = k1;
    spll_obj->k2 = k2;

    spll_obj->v_q[0] = (float32_t)(0.0);
    spll_obj->v_q[1] = (float32_t)(0.0);

    spll_obj->ylf[0] = (float32_t)(0.0);
    spll_obj->ylf[1] = (float32_t)(0.0);

    spll_obj->fo = (float32_t)(0.0);
    spll_obj->fn = (float32_t)(grid_freq);

    spll_obj->theta[0] = (float32_t)(0.0);
    spll_obj->theta[1] = (float32_t)(0.0);

    spll_obj->delta_t = delta_t;
}

//
//! \brief              Reset SPLL_3PH_DDSRF module
//! \param *spll_obj    The SPLL_3PH_DDSRF structure
//! \return None
//!
static inline void SPLL_3PH_DDSRF_reset(SPLL_3PH_DDSRF *spll_obj)
{
    spll_obj->d_p_decoupl = (float32_t)(0.0);
    spll_obj->d_n_decoupl = (float32_t)(0.0);

    spll_obj->q_p_decoupl = (float32_t)(0.0);
    spll_obj->q_n_decoupl = (float32_t)(0.0);

    spll_obj->d_p_decoupl_lpf = (float32_t)(0.0);
    spll_obj->d_n_decoupl_lpf = (float32_t)(0.0);

    spll_obj->q_p_decoupl_lpf = (float32_t)(0.0);
    spll_obj->q_n_decoupl_lpf = (float32_t)(0.0);

    spll_obj->y[0] = (float32_t)(0.0);
    spll_obj->y[1] = (float32_t)(0.0);

    spll_obj->x[0] = (float32_t)(0.0);
    spll_obj->x[1] = (float32_t)(0.0);

    spll_obj->w[0] = (float32_t)(0.0);
    spll_obj->w[1] = (float32_t)(0.0);

    spll_obj->z[0] = (float32_t)(0.0);
    spll_obj->z[1] = (float32_t)(0.0);

    spll_obj->v_q[0] = (float32_t)(0.0);
    spll_obj->v_q[1] = (float32_t)(0.0);

    spll_obj->ylf[0] = (float32_t)(0.0);
    spll_obj->ylf[1] = (float32_t)(0.0);

    spll_obj->fo = (float32_t)(0.0);

    spll_obj->theta[0] = (float32_t)(0.0);
    spll_obj->theta[1] = (float32_t)(0.0);
}

//
//! \brief              Run spll_3PH_srf module
//! \param *spll_obj    The spll_3PH_ddsrf structure
//! \param d_p          D Positive seq component of the grid voltage
//! \param d_n          D Negative seq component of the grid voltage
//! \param q_p          Q Positive seq component of the grid voltage
//! \param q_n          Q Negative seq component of the grid voltage
//! \return None
//!
static inline void SPLL_3PH_DDSRF_run(SPLL_3PH_DDSRF *spll_obj,
                                      float32_t d_p, float32_t d_n,
                                      float32_t q_p, float32_t q_n)
{
    //
    // before calling this routine run the ABC_DQ0_Pos & Neg run routines
    // pass updated values for d_p,d_n,q_p,q_n
    // and update the cos_2theta and sin_2theta values with the prev angle
    //

    //
    // Decoupling Network
    //
    spll_obj->d_p_decoupl = d_p
                           - (spll_obj->d_n_decoupl_lpf * spll_obj->cos_2theta)
                           - (spll_obj->q_n_decoupl * spll_obj->sin_2theta);
    spll_obj->q_p_decoupl = q_p
                           + (spll_obj->d_n_decoupl_lpf * spll_obj->sin_2theta)
                           - (spll_obj->q_n_decoupl * spll_obj->cos_2theta);

    spll_obj->d_n_decoupl = d_n
                           - (spll_obj->d_p_decoupl_lpf * spll_obj->cos_2theta)
                           + (spll_obj->q_p_decoupl * spll_obj->sin_2theta);
    spll_obj->q_n_decoupl = q_n
                           - (spll_obj->d_p_decoupl_lpf * spll_obj->sin_2theta)
                           - (spll_obj->q_p_decoupl * spll_obj->cos_2theta);

    //
    // Low pass filter
    //

    spll_obj->y[1] = (spll_obj->d_p_decoupl * spll_obj->k1)
                   - (spll_obj->y[0] * spll_obj->k2);
    spll_obj->d_p_decoupl_lpf = spll_obj->y[1] + spll_obj->y[0];
    spll_obj->y[0] = spll_obj->y[1];

    spll_obj->x[1] = (spll_obj->q_p_decoupl * spll_obj->k1)
                  - (spll_obj->x[0] * spll_obj->k2);
    spll_obj->q_p_decoupl_lpf = spll_obj->x[1] + spll_obj->x[0];
    spll_obj->x[0] = spll_obj->x[1];

    spll_obj->w[1] = (spll_obj->d_n_decoupl * spll_obj->k1)
                  - (spll_obj->w[0] * spll_obj->k2);
    spll_obj->d_n_decoupl_lpf = spll_obj->w[1] + spll_obj->w[0];
    spll_obj->w[0] = spll_obj->w[1];

    spll_obj->z[1] = (spll_obj->q_n_decoupl * spll_obj->k1)
                  - (spll_obj->z[0] * spll_obj->k2);
    spll_obj->q_n_decoupl_lpf = spll_obj->z[1] + spll_obj->z[0];
    spll_obj->z[0] = spll_obj->z[1];

    spll_obj->v_q[0] = spll_obj->q_p_decoupl;

    //
    // Loop Filter
    //
    spll_obj->ylf[0] = spll_obj->ylf[1]
                    + (spll_obj->lpf_coeff.b0 * spll_obj->v_q[0])
                    + (spll_obj->lpf_coeff.b1 * spll_obj->v_q[1]);
    spll_obj->ylf[1] = spll_obj->ylf[0];
    spll_obj->v_q[1] = spll_obj->v_q[0];

    //
    // VCO
    //
    spll_obj->fo = spll_obj->fn + spll_obj->ylf[0];

    spll_obj->theta[0] = spll_obj->theta[1] +
             ((spll_obj->fo * spll_obj->delta_t)
             * (float32_t)(2.0f * 3.1415926f));

    if(spll_obj->theta[0] > (float32_t)(2.0f * 3.1415926f))
    {
        spll_obj->theta[0] = spll_obj->theta[0] -
                  (float32_t)(2.0f * 3.1415926f);
    }


    spll_obj->theta[1] = spll_obj->theta[0];

    spll_obj->cos_2theta = cosf(spll_obj->theta[1] * 2.0f);
    spll_obj->sin_2theta = sinf(spll_obj->theta[1] * 2.0f);
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

#endif // end of  _SPLL_3PH_DDSRF_H_ definition

//
// End of File
//
