/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_ELAB.h
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

#ifndef RTW_HEADER_buck_ELAB_h_
#define RTW_HEADER_buck_ELAB_h_
#ifndef buck_ELAB_COMMON_INCLUDES_
#define buck_ELAB_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* buck_ELAB_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S34>/Integrator' */
  real_T Filter_DSTATE;                /* '<S29>/Filter' */
} DW_buck_ELAB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T MY_BOARD_ADC1;                /* '<Root>/MY_BOARD_ADC1' */
  real_T MY_BOARD_ADC2;                /* '<Root>/MY_BOARD_ADC2' */
  real_T MY_BOARD_ADC3;                /* '<Root>/MY_BOARD_ADC3' */
  real_T MY_BOARD_ADC4;                /* '<Root>/MY_BOARD_ADC4' */
  real_T MY_BOARD_ADC5;                /* '<Root>/MY_BOARD_ADC5' */
  real_T MY_BOARD_ADC6;                /* '<Root>/MY_BOARD_ADC6' */
  real_T MY_BOARD_ADC7;                /* '<Root>/MY_BOARD_ADC7' */
  real_T MY_BOARD_ADC8;                /* '<Root>/MY_BOARD_ADC8' */
  real_T MY_BOARD_ADC9;                /* '<Root>/MY_BOARD_ADC9' */
  real_T MY_BOARD_ADC10;               /* '<Root>/MY_BOARD_ADC10' */
  real_T KEY_INPUT_1;                  /* '<Root>/KEY_INPUT_1' */
  real_T KEY_INPUT_2;                  /* '<Root>/KEY_INPUT_2' */
  real_T KEY_INPUT_3;                  /* '<Root>/KEY_INPUT_3' */
} ExtU_buck_ELAB;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T PWM_A;                        /* '<Root>/PWM_A' */
  real_T PWM_B;                        /* '<Root>/PWM_B' */
  real_T PWM_C;                        /* '<Root>/PWM_C' */
  real_T PWM_D;                        /* '<Root>/PWM_D' */
  real_T signal1;                      /* '<Root>/signal1' */
  real_T signal2;                      /* '<Root>/signal2' */
  real_T signal3;                      /* '<Root>/signal3' */
  real_T signal4;                      /* '<Root>/signal4' */
  real_T signal1b;                     /* '<Root>/signal1b' */
  real_T signal2b;                     /* '<Root>/signal2b' */
  real_T signal3b;                     /* '<Root>/signal3b' */
} ExtY_buck_ELAB;

/* Block signals and states (default storage) */
extern DW_buck_ELAB rtDW_buck_ELAB;

/* External inputs (root inport signals with default storage) */
extern ExtU_buck_ELAB rtU_buck_ELAB;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_buck_ELAB rtY_buck_ELAB;

/* Model entry point functions */
extern void buck_ELAB_initialize(void);
extern void buck_ELAB_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S31>/Integral Gain' : Eliminated nontunable gain of 1
 */

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
 * hilite_system('buck_ELAB_subsystem/buck_ELAB')    - opens subsystem buck_ELAB_subsystem/buck_ELAB
 * hilite_system('buck_ELAB_subsystem/buck_ELAB/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'buck_ELAB_subsystem'
 * '<S1>'   : 'buck_ELAB_subsystem/buck_ELAB'
 * '<S2>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller'
 * '<S3>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Anti-windup'
 * '<S4>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/D Gain'
 * '<S5>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Filter'
 * '<S6>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Filter ICs'
 * '<S7>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/I Gain'
 * '<S8>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Ideal P Gain'
 * '<S9>'   : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Integrator'
 * '<S11>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Integrator ICs'
 * '<S12>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/N Copy'
 * '<S13>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/N Gain'
 * '<S14>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/P Copy'
 * '<S15>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Parallel P Gain'
 * '<S16>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Reset Signal'
 * '<S17>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Saturation'
 * '<S18>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Saturation Fdbk'
 * '<S19>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Sum'
 * '<S20>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Sum Fdbk'
 * '<S21>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tracking Mode'
 * '<S22>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tsamp - Integral'
 * '<S24>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/postSat Signal'
 * '<S26>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/preSat Signal'
 * '<S27>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S28>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S29>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S30>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S31>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S32>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S33>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S34>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Integrator/Discrete'
 * '<S35>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S36>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/N Copy/Disabled'
 * '<S37>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S38>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/P Copy/Disabled'
 * '<S39>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S40>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Reset Signal/Disabled'
 * '<S41>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Saturation/Enabled'
 * '<S42>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S43>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Sum/Sum_PID'
 * '<S44>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S45>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S46>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S47>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S48>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S49>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S50>'  : 'buck_ELAB_subsystem/buck_ELAB/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_buck_ELAB_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
