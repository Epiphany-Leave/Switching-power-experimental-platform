#include  "ELAB_subsystem.h"
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_ELAB.c
 *
 * Code generated for Simulink model 'buck_ELAB'.
 *
 * Model version                  : 1.23
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu May 25 02:44:34 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "buck_ELAB.h"

/* Block signals and states (default storage) */
DW_buck_ELAB rtDW_buck_ELAB;

/* External inputs (root inport signals with default storage) */
ExtU_buck_ELAB rtU_buck_ELAB;

/* External outputs (root outports fed by signals with default storage) */
ExtY_buck_ELAB rtY_buck_ELAB;

/* Model step function */
void buck_ELAB_step(void)
{
  real_T rtb_FilterCoefficient;
  real_T rtb_Saturation;

  /* Gain: '<S37>/Filter Coefficient' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S29>/Filter'
   *  Gain: '<S28>/Derivative Gain'
   *  Inport: '<Root>/MY_BOARD_ADC1'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S29>/SumD'
   */
  rtb_FilterCoefficient = ((rtU_buck_ELAB.MY_BOARD_ADC1 - 30.0) * 0.0 -
    rtDW_buck_ELAB.Filter_DSTATE) * 100.0;

  /* Sum: '<S43>/Sum' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S34>/Integrator'
   *  Gain: '<S39>/Proportional Gain'
   *  Inport: '<Root>/MY_BOARD_ADC1'
   *  Sum: '<S1>/Sum'
   */
  rtb_Saturation = ((rtU_buck_ELAB.MY_BOARD_ADC1 - 30.0) * 2.0E-5 +
                    rtDW_buck_ELAB.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<S41>/Saturation' */
  if (rtb_Saturation > 0.95) {
    rtb_Saturation = 0.95;
  } else if (rtb_Saturation < 0.05) {
    rtb_Saturation = 0.05;
  }

  /* End of Saturate: '<S41>/Saturation' */

  /* Outport: '<Root>/PWM_A' */
  rtY_buck_ELAB.PWM_A = rtb_Saturation;

  /* Outport: '<Root>/signal3' */
  rtY_buck_ELAB.signal3 = rtb_Saturation;

  /* Outport: '<Root>/signal1b' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/MY_BOARD_ADC1'
   *  Sum: '<S1>/Sum1'
   *  Switch: '<S1>/Switch'
   */
  rtY_buck_ELAB.signal1b = (rtU_buck_ELAB.MY_BOARD_ADC1 - 25.0 > 0.0);

  /* Outport: '<Root>/signal1' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC1'
   */
  rtY_buck_ELAB.signal1 = rtU_buck_ELAB.MY_BOARD_ADC1;

  /* Outport: '<Root>/signal4' incorporates:
   *  Inport: '<Root>/MY_BOARD_ADC2'
   */
  rtY_buck_ELAB.signal4 = rtU_buck_ELAB.MY_BOARD_ADC2;

  /* Update for DiscreteIntegrator: '<S34>/Integrator' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/MY_BOARD_ADC1'
   *  Sum: '<S1>/Sum'
   */
  rtDW_buck_ELAB.Integrator_DSTATE += (rtU_buck_ELAB.MY_BOARD_ADC1 - 30.0) *
    5.0E-5;

  /* Update for DiscreteIntegrator: '<S29>/Filter' */
  rtDW_buck_ELAB.Filter_DSTATE += 5.0E-5 * rtb_FilterCoefficient;
}

/* Model initialize function */
void buck_ELAB_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S34>/Integrator' */
  rtDW_buck_ELAB.Integrator_DSTATE = 0.9;

  /* ConstCode for Outport: '<Root>/signal2' incorporates:
   *  Constant: '<S1>/Constant'
   */
  rtY_buck_ELAB.signal2 = 30.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
