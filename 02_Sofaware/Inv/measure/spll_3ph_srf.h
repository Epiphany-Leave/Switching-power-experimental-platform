//#############################################################################
//
//  FILE:   splll_3ph_srf.h
//
//  TITLE:  Software Phase Lock Loop for Three Phase Grid Tied Systems
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

#ifndef SPLL_3PH_SRF_H
#define SPLL_3PH_SRF_H

//*****************************************************************************
//
//! \addtogroup SPLL_3PH_SRF
//! @{
//
//*****************************************************************************

//
// Included Files
//

#include <math.h>

//#############################################################################
//
// Macro Definitions
//
//#############################################################################


//
// Typedefs
//

//! \brief          Defines the coefficients for a loop filter
//!
//! \details        Loop filter coefficients
//!
typedef struct{
    float b1;
    float b0;
} SPLL_3PH_SRF_LPF_COEFF;

//! \brief          Defines the SPLL_3PH_SRF structure
//!
//! \details        This software module implements a software phase lock loop
//!                 based on synchronous reference frame for
//!                 grid connection to three phase grid
//!
typedef struct{
    float v_q[2];     //!< Rotating reference frame Q-axis value
    float ylf[2];     //!< Data buffer for loop filter output
    float fo;         //!< Output frequency of PLL
    float fn;         //!< Nominal frequency
    float theta[2];   //!< Grid phase angle
    float delta_t;    //!< Inverse of the ISR rate at which module is called
    SPLL_3PH_SRF_LPF_COEFF lpf_coeff;  //!< Loop filter coefficients
} SPLL_3PH_SRF;

//! \brief              Initialize SPLL_3PH_SRF module
//! \param grid_freq    The grid frequency
//! \param delta_t      1/Frequency of calling the PLL routine
//! \param *spll_obj     The SPLL_3PH_SRF structure
//! \return None
//!
 void SPLL_3PH_SRF_init(float grid_freq, float delta_t,
                                     SPLL_3PH_SRF *spll_obj)
{
    spll_obj->v_q[0] = (float)(0.0);
    spll_obj->v_q[1] = (float)(0.0);

    spll_obj->ylf[0] = (float)(0.0);
    spll_obj->ylf[1] = (float)(0.0);

    spll_obj->fo = (float)(0.0);
    spll_obj->fn = (float)(grid_freq);

    spll_obj->theta[0] = (float)(0.0);
    spll_obj->theta[1] = (float)(0.0);

    spll_obj->delta_t = (float)delta_t;
}

//! \brief              Reset SPLL_3PH_SRF module
//! \param *spll_obj     The SPLL_3PH_SRF structure
//! \return None
//!
 void SPLL_3PH_SRF_reset(SPLL_3PH_SRF *spll_obj)
{
    spll_obj->v_q[0] = (float)(0.0);
    spll_obj->v_q[1] = (float)(0.0);

    spll_obj->ylf[0] = (float)(0.0);
    spll_obj->ylf[1] = (float)(0.0);

    spll_obj->fo = (float)(0.0);

    spll_obj->theta[0] = (float)(0.0);
    spll_obj->theta[1] = (float)(0.0);

}

//! \brief              Run SPLL_3PH_SRF module
//! \param v_q          Q component of the grid voltage
//! \param *spll_obj     The SPLL_3PH_SRF structure
//!
 void SPLL_3PH_SRF_run(float v_q, SPLL_3PH_SRF *spll_obj)
{
    //
    // Update the spll_obj->v_q[0] with the grid value
    //
    spll_obj->v_q[0] = v_q;

    //
    // Loop Filter
    //
    spll_obj->ylf[0] =  spll_obj->ylf[1]
                     + (spll_obj->lpf_coeff.b0 * spll_obj->v_q[0])
                     + (spll_obj->lpf_coeff.b1 * spll_obj->v_q[1]);
    spll_obj->ylf[1] = spll_obj->ylf[0];
    spll_obj->v_q[1] = spll_obj->v_q[0];

    spll_obj->ylf[0] = (spll_obj->ylf[0] > (float)(200.0)) ?
                                (float)(200.0) : spll_obj->ylf[0];

    //
    // VCO
    //
    spll_obj->fo = spll_obj->fn + spll_obj->ylf[0];

    spll_obj->theta[0] = spll_obj->theta[1] +
                         ((spll_obj->fo * spll_obj->delta_t) *
                          (float)(2.0 * 3.1415926));
    if(spll_obj->theta[0] > (float)(2.0 * 3.1415926))
    {
        spll_obj->theta[0] = spll_obj->theta[0] - (float)(2.0 * 3.1415926);
    }

    spll_obj->theta[1] = spll_obj->theta[0];
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif