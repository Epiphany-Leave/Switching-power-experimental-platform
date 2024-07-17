#include  "KEY_ELAB.h"
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_KEY.c
 *
 * Code generated for Simulink model 'buck_KEY'.
 *
 * Model version                  : 1.23
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu May 25 02:46:03 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "buck_KEY.h"

/* Block signals and states (default storage) */
DW_buck_KEY rtDW_buck_KEY;

/* External inputs (root inport signals with default storage) */
ExtU_buck_KEY rtU_buck_KEY;

/* External outputs (root outports fed by signals with default storage) */
ExtY_buck_KEY rtY_buck_KEY;

/* Model step function */
void buck_KEY_step(void)
{
  real_T rtb_Sum1;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Constant: '<S1>/Constant'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_Sum1 = rtDW_buck_KEY.UnitDelay_DSTATE + 1.0;

  /* Outport: '<Root>/KEY_OUT_1' */
  rtY_buck_KEY.KEY_OUT_1 = rtb_Sum1;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW_buck_KEY.UnitDelay_DSTATE = rtb_Sum1;
}

/* Model initialize function */
void buck_KEY_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
