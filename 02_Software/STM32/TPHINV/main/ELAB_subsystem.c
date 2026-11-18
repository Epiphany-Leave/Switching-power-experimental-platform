#include  "ELAB_subsystem.h"
#include  "my_board.h"
/*
 * File: TPHINV_ELAB.c
 *
 * Code generated for Simulink model 'TPHINV_ELAB'.
 *
 * Model version                  : 1.44
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jun 25 16:49:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "TPHINV_ELAB.h"

/* Block signals and states (default storage) */
DW_TPHINV_ELAB rtDW_TPHINV_ELAB;

/* External inputs (root inport signals with default storage) */
ExtU_TPHINV_ELAB rtU_TPHINV_ELAB;

/* External outputs (root outports fed by signals with default storage) */
ExtY_TPHINV_ELAB rtY_TPHINV_ELAB;

/* Model step function */
void TPHINV_ELAB_step(void)
{
  real32_T DiscreteFilter_tmp;
  real32_T rtb_Product3;
  real32_T rtb_Saturation;
  real32_T rtb_Sum3;

  /* Abs: '<S1>/Abs' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC3'
   */
  rtb_Sum3 = fabsf(rtU_TPHINV_ELAB.MY_BOARD_ADC3);

  /* DiscreteFilter: '<S1>/Discrete Filter' incorporates:
   *  Product: '<S1>/Product3'
   */
  DiscreteFilter_tmp = (rtb_Sum3 * rtb_Sum3 - -1999.0F *
                        rtDW_TPHINV_ELAB.DiscreteFilter_states) / 2001.0F;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteFilter: '<S1>/Discrete Filter'
   *  Sqrt: '<S1>/Sqrt'
   */
  rtb_Sum3 = sqrtf(DiscreteFilter_tmp + rtDW_TPHINV_ELAB.DiscreteFilter_states)
    - 15.0F;

  /* Gain: '<S37>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S29>/Filter'
   *  Gain: '<S28>/Derivative Gain'
   *  Sum: '<S29>/SumD'
   */
  rtb_Product3 = (0.0F * rtb_Sum3 - rtDW_TPHINV_ELAB.Filter_DSTATE) * 100.0F;

  /* Sum: '<S43>/Sum' incorporates:
   *  DiscreteIntegrator: '<S34>/Integrator'
   *  Gain: '<S39>/Proportional Gain'
   */
  rtb_Saturation = (2.0E-5F * rtb_Sum3 + rtDW_TPHINV_ELAB.Integrator_DSTATE) +
    rtb_Product3;

  /* Saturate: '<S41>/Saturation' */
  if (rtb_Saturation > 0.45F) {
    rtb_Saturation = 0.45F;
  } else if (rtb_Saturation < -0.45F) {
    rtb_Saturation = -0.45F;
  }

  /* End of Saturate: '<S41>/Saturation' */

  /* Outport: '<Root>/PWM_A' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Product: '<S1>/Product'
   *  Sin: '<S1>/Sine Wave'
   *  Sum: '<S1>/Sum'
   */
  rtY_TPHINV_ELAB.PWM_A = sin((real_T)rtDW_TPHINV_ELAB.counter * 2.0 *
    3.1415926535897931 / 400.0) * rtb_Saturation + 0.5;

  /* Outport: '<Root>/PWM_B' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Product: '<S1>/Product1'
   *  Sin: '<S1>/Sine Wave1'
   *  Sum: '<S1>/Sum1'
   */
  rtY_TPHINV_ELAB.PWM_B = sin(((real_T)rtDW_TPHINV_ELAB.counter_f +
    133.33333333333334) * 2.0 * 3.1415926535897931 / 400.0) * rtb_Saturation +
    0.5;

  /* Outport: '<Root>/PWM_C' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Product: '<S1>/Product2'
   *  Sin: '<S1>/Sine Wave2'
   *  Sum: '<S1>/Sum2'
   */
  rtY_TPHINV_ELAB.PWM_C = sin(((real_T)rtDW_TPHINV_ELAB.counter_m +
    266.66666666666669) * 2.0 * 3.1415926535897931 / 400.0) * rtb_Saturation +
    0.5;

  /* Outport: '<Root>/signal1' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC3'
   */
  rtY_TPHINV_ELAB.signal1 = rtU_TPHINV_ELAB.MY_BOARD_ADC3;

  /* Outport: '<Root>/signal2' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC5'
   */
  rtY_TPHINV_ELAB.signal2 = rtU_TPHINV_ELAB.MY_BOARD_ADC5;

  /* Outport: '<Root>/signal3' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC6'
   */
  rtY_TPHINV_ELAB.signal3 = rtU_TPHINV_ELAB.MY_BOARD_ADC6;

  /* Outport: '<Root>/signal4' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC7'
   */
  rtY_TPHINV_ELAB.signal4 = rtU_TPHINV_ELAB.MY_BOARD_ADC7;

  /* Update for DiscreteFilter: '<S1>/Discrete Filter' */
  rtDW_TPHINV_ELAB.DiscreteFilter_states = DiscreteFilter_tmp;

  /* Update for DiscreteIntegrator: '<S34>/Integrator' incorporates:
   *  Gain: '<S31>/Integral Gain'
   */
  rtDW_TPHINV_ELAB.Integrator_DSTATE += 0.2F * rtb_Sum3 * 5.0E-5F;

  /* Update for DiscreteIntegrator: '<S29>/Filter' */
  rtDW_TPHINV_ELAB.Filter_DSTATE += 5.0E-5F * rtb_Product3;

  /* Update for Sin: '<S1>/Sine Wave' */
  rtDW_TPHINV_ELAB.counter++;
  if (rtDW_TPHINV_ELAB.counter == 400) {
    rtDW_TPHINV_ELAB.counter = 0;
  }

  /* End of Update for Sin: '<S1>/Sine Wave' */

  /* Update for Sin: '<S1>/Sine Wave1' */
  rtDW_TPHINV_ELAB.counter_f++;
  if (rtDW_TPHINV_ELAB.counter_f == 400) {
    rtDW_TPHINV_ELAB.counter_f = 0;
  }

  /* End of Update for Sin: '<S1>/Sine Wave1' */

  /* Update for Sin: '<S1>/Sine Wave2' */
  rtDW_TPHINV_ELAB.counter_m++;
  if (rtDW_TPHINV_ELAB.counter_m == 400) {
    rtDW_TPHINV_ELAB.counter_m = 0;
  }

  /* End of Update for Sin: '<S1>/Sine Wave2' */
}

/* Model initialize function */
void TPHINV_ELAB_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
