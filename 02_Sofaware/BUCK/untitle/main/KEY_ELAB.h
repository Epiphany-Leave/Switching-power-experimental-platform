/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_KEY.h
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

#ifndef RTW_HEADER_buck_KEY_h_
#define RTW_HEADER_buck_KEY_h_
#ifndef buck_KEY_COMMON_INCLUDES_
#define buck_KEY_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* buck_KEY_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S1>/Unit Delay' */
} DW_buck_KEY;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T KEY_IN1;                      /* '<Root>/KEY_IN1' */
  real_T KEY_IN2;                      /* '<Root>/KEY_IN2' */
  real_T KEY_IN3;                      /* '<Root>/KEY_IN3' */
} ExtU_buck_KEY;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T KEY_OUT_1;                    /* '<Root>/KEY_OUT_1' */
  real_T KEY_OUT_2;                    /* '<Root>/KEY_OUT_2' */
  real_T KEY_OUT_3;                    /* '<Root>/KEY_OUT_3' */
} ExtY_buck_KEY;

/* Block signals and states (default storage) */
extern DW_buck_KEY rtDW_buck_KEY;

/* External inputs (root inport signals with default storage) */
extern ExtU_buck_KEY rtU_buck_KEY;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_buck_KEY rtY_buck_KEY;

/* Model entry point functions */
extern void buck_KEY_initialize(void);
extern void buck_KEY_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('buck_ELAB_subsystem/buck_KEY')    - opens subsystem buck_ELAB_subsystem/buck_KEY
 * hilite_system('buck_ELAB_subsystem/buck_KEY/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'buck_ELAB_subsystem'
 * '<S1>'   : 'buck_ELAB_subsystem/buck_KEY'
 */
#endif                                 /* RTW_HEADER_buck_KEY_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
