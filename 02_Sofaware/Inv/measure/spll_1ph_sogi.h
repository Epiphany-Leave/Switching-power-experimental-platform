//#############################################################################
//
//  FILE:   spll_1ph_sogi.h
//
//  TITLE:  Orthogonal Signal Generator Software Phase Lock Loop (SPLL) 
//          for Single Phase Grid Module
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

#ifndef SPLL_1PH_SOGI_H
#define SPLL_1PH_SOGI_H


//*****************************************************************************
//
//! \addtogroup SPLL_1PH_SOGI
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
#define SOLL_SOGI_Q _IQ23
#define SPLL_SOGI_Qmpy_IQ23mpy	_IQ23mpy
#define SPLL_SOGI_SINE	_IQ23sin
#define SPLL_SOGI_COS	_IQ23cos
//! \brief  Defines the SPLL_1PH_SOGI_PID structure
//!
//typedef struct{
//	float Err;
//	float Kp;
//	float Ki;
//	float v_q_ref;
//	float OutputMax;      
//    float OutputMin;    
//    float Output; 
//} SPLL_1PH_SOGI_PID;

//! \brief  Defines the SPLL_1PH_SOGI_OSG_COEFF structure
//!
typedef struct{
    float osg_k;
    float osg_x;
    float osg_y;
    float osg_b0;
    float osg_b2;
    float osg_a1;
    float osg_a2;
    float osg_qb0;
    float osg_qb1;
    float osg_qb2;
} SPLL_1PH_SOGI_OSG_COEFF;

//! \brief  Defines the SPLL_1PH_SOGI_LPF_COEFF structure
//!
typedef struct{
    float b1;
    float b0;
} SPLL_1PH_SOGI_LPF_COEFF;

//! \brief Defines the Orthogonal Signal Generator SPLL_1PH_SOGI
//!        structure
//!
//! \details The SPLL_1PH_SOGI can be used to generate the
//!          orthogonal signal from the sensed single phase grid voltage
//!          and use that information to provide phase of the grid voltage
//!
typedef struct{
    float   u[3];       //!< AC input data buffer
    float   osg_u[3];   //!< Orthogonal signal generator data buffer
    float   osg_qu[3];  //!< Orthogonal signal generator quadrature data buffer
    float   u_Q[2];     //!< Q-axis component
    float   u_D[2];     //!< D-axis component
    float   ylf[2];     //!< Loop filter data storage
    float   fo;         //!< Output frequency of PLL(Hz)
    float   fn;         //!< Nominal frequency (Hz)
    float   theta;      //!< Angle output (0-2*pi)
    float   cosine;     //!< Cosine value of the PLL angle
    float   sine;       //!< Sine value of the PLL angle
    float   delta_t;    //!< Inverse of the ISR rate at which module is called
    SPLL_1PH_SOGI_OSG_COEFF osg_coeff; //!< Orthogonal signal generator coefficient
    SPLL_1PH_SOGI_LPF_COEFF lpf_coeff; //!< Loop filter coeffcient structure
//	SPLL_1PH_SOGI_PID	pid_coeff;
} SPLL_1PH_SOGI;

//! \brief Resets internal storage data of the module
//! \param *spll_obj The SPLL_1PH_SOGI structure pointer
//! \return None
//!
 void SPLL_1PH_SOGI_reset(SPLL_1PH_SOGI *spll_obj);

//! \brief Calculates the SPLL_1PH_SOGI coefficient
//! \param *spll_obj The SPLL_1PH_SOGI structure
//! \return None
//!
 void SPLL_1PH_SOGI_coeff_calc(SPLL_1PH_SOGI *spll_obj);

//! \brief Run the SPLL_1PH_SOGI module
//! \param *spll_obj The SPLL_1PH_SOGI structure pointer
//! \param acValue AC grid voltage in per unit (pu)
//! \return None
//!
 void SPLL_1PH_SOGI_run(SPLL_1PH_SOGI *spll_obj,
                                     float acValue);
void SPLL_1PH_SOGI_config(SPLL_1PH_SOGI *spll_obj,float acFreq,float isrFrequency,float lpf_b0,float lpf_b1);
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

