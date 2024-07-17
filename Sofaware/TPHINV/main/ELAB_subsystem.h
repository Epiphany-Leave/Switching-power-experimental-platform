/*
 * File: TPHINV_ELAB.h
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

#ifndef RTW_HEADER_TPHINV_ELAB_h_
#define RTW_HEADER_TPHINV_ELAB_h_
#include <math.h>
#ifndef TPHINV_ELAB_COMMON_INCLUDES_
#define TPHINV_ELAB_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* TPHINV_ELAB_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteFilter_states;      /* '<S1>/Discrete Filter' */
  real32_T Integrator_DSTATE;          /* '<S34>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S29>/Filter' */
  int32_T counter;                     /* '<S1>/Sine Wave' */
  int32_T counter_f;                   /* '<S1>/Sine Wave1' */
  int32_T counter_m;                   /* '<S1>/Sine Wave2' */
} DW_TPHINV_ELAB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T MY_BOARD_ADC1;              /* '<Root>/MY_BOARD_ADC1' */
  real32_T MY_BOARD_ADC2;              /* '<Root>/MY_BOARD_ADC2' */
  real32_T MY_BOARD_ADC3;              /* '<Root>/MY_BOARD_ADC3' */
  real32_T MY_BOARD_ADC4;              /* '<Root>/MY_BOARD_ADC4' */
  real32_T MY_BOARD_ADC5;              /* '<Root>/MY_BOARD_ADC5' */
  real32_T MY_BOARD_ADC6;              /* '<Root>/MY_BOARD_ADC6' */
  real32_T MY_BOARD_ADC7;              /* '<Root>/MY_BOARD_ADC7' */
  real32_T MY_BOARD_ADC8;              /* '<Root>/MY_BOARD_ADC8' */
  real32_T MY_BOARD_ADC9;              /* '<Root>/MY_BOARD_ADC9' */
  real32_T MY_BOARD_ADC10;             /* '<Root>/MY_BOARD_ADC10' */
  real32_T KEY_INPUT_1;                /* '<Root>/KEY_INPUT_1' */
  real32_T KEY_INPUT_2;                /* '<Root>/KEY_INPUT_2' */
  real32_T KEY_INPUT_3;                /* '<Root>/KEY_INPUT_3' */
} ExtU_TPHINV_ELAB;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T PWM_A;                        /* '<Root>/PWM_A' */
  real_T PWM_B;                        /* '<Root>/PWM_B' */
  real_T PWM_C;                        /* '<Root>/PWM_C' */
  real32_T PWM_D;                      /* '<Root>/PWM_D' */
  real32_T signal1;                    /* '<Root>/signal1' */
  real32_T signal2;                    /* '<Root>/signal2' */
  real32_T signal3;                    /* '<Root>/signal3' */
  real32_T signal4;                    /* '<Root>/signal4' */
  real32_T signal1b;                   /* '<Root>/signal1b' */
  real32_T signal2b;                   /* '<Root>/signal2b' */
  real32_T signal3b;                   /* '<Root>/signal3b' */
} ExtY_TPHINV_ELAB;

/* Block signals and states (default storage) */
extern DW_TPHINV_ELAB rtDW_TPHINV_ELAB;

/* External inputs (root inport signals with default storage) */
extern ExtU_TPHINV_ELAB rtU_TPHINV_ELAB;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_TPHINV_ELAB rtY_TPHINV_ELAB;

/* Model entry point functions */
extern void TPHINV_ELAB_initialize(void);
extern void TPHINV_ELAB_step(void);

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
 * hilite_system('TPHINV_ELAB_subsystem/TPHINV_ELAB')    - opens subsystem TPHINV_ELAB_subsystem/TPHINV_ELAB
 * hilite_system('TPHINV_ELAB_subsystem/TPHINV_ELAB/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TPHINV_ELAB_subsystem'
 * '<S1>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB'
 * '<S2>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller'
 * '<S3>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Anti-windup'
 * '<S4>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/D Gain'
 * '<S5>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Filter'
 * '<S6>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Filter ICs'
 * '<S7>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/I Gain'
 * '<S8>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Ideal P Gain'
 * '<S9>'   : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Integrator'
 * '<S11>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Integrator ICs'
 * '<S12>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/N Copy'
 * '<S13>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/N Gain'
 * '<S14>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/P Copy'
 * '<S15>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Parallel P Gain'
 * '<S16>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Reset Signal'
 * '<S17>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Saturation'
 * '<S18>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Saturation Fdbk'
 * '<S19>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Sum'
 * '<S20>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Sum Fdbk'
 * '<S21>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tracking Mode'
 * '<S22>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tsamp - Integral'
 * '<S24>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/postSat Signal'
 * '<S26>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/preSat Signal'
 * '<S27>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S28>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S29>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S30>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S31>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S32>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S33>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S34>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Integrator/Discrete'
 * '<S35>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S36>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/N Copy/Disabled'
 * '<S37>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S38>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/P Copy/Disabled'
 * '<S39>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S40>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Reset Signal/Disabled'
 * '<S41>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Saturation/Enabled'
 * '<S42>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S43>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Sum/Sum_PID'
 * '<S44>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S45>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S46>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S47>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S48>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S49>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S50>'  : 'TPHINV_ELAB_subsystem/TPHINV_ELAB/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_TPHINV_ELAB_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
