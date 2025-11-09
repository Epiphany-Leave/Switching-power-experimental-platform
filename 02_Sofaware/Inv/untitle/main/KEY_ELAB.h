/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rt_KEY.h
 *
 * Code generated for Simulink model 'rt_KEY'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Jul 27 20:27:04 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_KEY_h_
#define RTW_HEADER_rt_KEY_h_
#ifndef rt_KEY_COMMON_INCLUDES_
#define rt_KEY_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* rt_KEY_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T KEY_IN1;                    /* '<Root>/KEY_IN1' */
  real32_T KEY_IN2;                    /* '<Root>/KEY_IN2' */
  real32_T KEY_IN3;                    /* '<Root>/KEY_IN3' */
} ExtU_rt_KEY;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T KEY_OUT_1;                  /* '<Root>/KEY_OUT_1' */
  real32_T KEY_OUT_2;                  /* '<Root>/KEY_OUT_2' */
  real32_T KEY_OUT_3;                  /* '<Root>/KEY_OUT_3' */
} ExtY_rt_KEY;

/* External inputs (root inport signals with default storage) */
extern ExtU_rt_KEY rtU_rt_KEY;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_rt_KEY rtY_rt_KEY;

/* Model entry point functions */
extern void rt_KEY_initialize(void);
extern void rt_KEY_step(void);

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
 * hilite_system('rt_ELAB_subsystem/rt_KEY')    - opens subsystem rt_ELAB_subsystem/rt_KEY
 * hilite_system('rt_ELAB_subsystem/rt_KEY/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'rt_ELAB_subsystem'
 * '<S1>'   : 'rt_ELAB_subsystem/rt_KEY'
 */
#endif                                 /* RTW_HEADER_rt_KEY_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
