/*
 * File: SOGI_PLLslx.h
 *
 * Code generated for Simulink model 'SOGI_PLLslx'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Jul 15 20:18:44 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SOGI_PLLslx_h_
#define RTW_HEADER_SOGI_PLLslx_h_
#ifndef SOGI_PLLslx_COMMON_INCLUDES_
#define SOGI_PLLslx_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SOGI_PLLslx_COMMON_INCLUDES_ */

#include "SOGI_PLLslx_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Invariant block signals (default storage) */
typedef struct {
  const uint8_T Compare;               /* '<S57>/Compare' */
  const uint8_T Compare_b;             /* '<S58>/Compare' */
} ConstB_SOGI_PLLslx_T;

/* Real-time Model Data Structure */
struct tag_RTM_SOGI_PLLslx_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

extern const ConstB_SOGI_PLLslx_T SOGI_PLLslx_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void SOGI_PLLslx_initialize(void);
extern void SOGI_PLLslx_step(void);
extern void SOGI_PLLslx_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SOGI_PLLslx_T *const SOGI_PLLslx_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant1' : Unused code path elimination
 * Block '<Root>/Constant2' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S1>/Gain1' : Unused code path elimination
 * Block '<S33>/Integral Gain' : Unused code path elimination
 * Block '<S36>/Integrator' : Unused code path elimination
 * Block '<S41>/Proportional Gain' : Unused code path elimination
 * Block '<S45>/Sum' : Unused code path elimination
 * Block '<S1>/Sum' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Sum2' : Unused code path elimination
 * Block '<S2>/Add' : Unused code path elimination
 * Block '<S2>/Constant1' : Unused code path elimination
 * Block '<S2>/Constant2' : Unused code path elimination
 * Block '<S2>/Mod' : Unused code path elimination
 * Block '<S59>/Fcn' : Unused code path elimination
 * Block '<S59>/Fcn1' : Unused code path elimination
 * Block '<S60>/Fcn' : Unused code path elimination
 * Block '<S60>/Fcn1' : Unused code path elimination
 * Block '<S55>/Switch' : Unused code path elimination
 * Block '<S53>/Constant' : Unused code path elimination
 * Block '<S53>/Constant1' : Unused code path elimination
 * Block '<S53>/Discrete-Time Integrator2' : Unused code path elimination
 * Block '<S89>/Integral Gain' : Unused code path elimination
 * Block '<S92>/Integrator' : Unused code path elimination
 * Block '<S97>/Proportional Gain' : Unused code path elimination
 * Block '<S101>/Sum' : Unused code path elimination
 * Block '<S53>/Scope' : Unused code path elimination
 * Block '<S53>/Scope1' : Unused code path elimination
 * Block '<S53>/Sum' : Unused code path elimination
 * Block '<S53>/Sum1' : Unused code path elimination
 * Block '<S2>/Product' : Unused code path elimination
 * Block '<S54>/Discrete-Time Integrator' : Unused code path elimination
 * Block '<S54>/Discrete-Time Integrator1' : Unused code path elimination
 * Block '<S54>/Gain' : Unused code path elimination
 * Block '<S54>/Product1' : Unused code path elimination
 * Block '<S54>/Product2' : Unused code path elimination
 * Block '<S54>/Sum' : Unused code path elimination
 * Block '<S54>/Sum1' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S2>/Sin' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SOGI_PLLslx'
 * '<S1>'   : 'SOGI_PLLslx/PID'
 * '<S2>'   : 'SOGI_PLLslx/SOGI_PLL'
 * '<S3>'   : 'SOGI_PLLslx/powergui'
 * '<S4>'   : 'SOGI_PLLslx/PID/PID Controller'
 * '<S5>'   : 'SOGI_PLLslx/PID/PID Controller/Anti-windup'
 * '<S6>'   : 'SOGI_PLLslx/PID/PID Controller/D Gain'
 * '<S7>'   : 'SOGI_PLLslx/PID/PID Controller/Filter'
 * '<S8>'   : 'SOGI_PLLslx/PID/PID Controller/Filter ICs'
 * '<S9>'   : 'SOGI_PLLslx/PID/PID Controller/I Gain'
 * '<S10>'  : 'SOGI_PLLslx/PID/PID Controller/Ideal P Gain'
 * '<S11>'  : 'SOGI_PLLslx/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S12>'  : 'SOGI_PLLslx/PID/PID Controller/Integrator'
 * '<S13>'  : 'SOGI_PLLslx/PID/PID Controller/Integrator ICs'
 * '<S14>'  : 'SOGI_PLLslx/PID/PID Controller/N Copy'
 * '<S15>'  : 'SOGI_PLLslx/PID/PID Controller/N Gain'
 * '<S16>'  : 'SOGI_PLLslx/PID/PID Controller/P Copy'
 * '<S17>'  : 'SOGI_PLLslx/PID/PID Controller/Parallel P Gain'
 * '<S18>'  : 'SOGI_PLLslx/PID/PID Controller/Reset Signal'
 * '<S19>'  : 'SOGI_PLLslx/PID/PID Controller/Saturation'
 * '<S20>'  : 'SOGI_PLLslx/PID/PID Controller/Saturation Fdbk'
 * '<S21>'  : 'SOGI_PLLslx/PID/PID Controller/Sum'
 * '<S22>'  : 'SOGI_PLLslx/PID/PID Controller/Sum Fdbk'
 * '<S23>'  : 'SOGI_PLLslx/PID/PID Controller/Tracking Mode'
 * '<S24>'  : 'SOGI_PLLslx/PID/PID Controller/Tracking Mode Sum'
 * '<S25>'  : 'SOGI_PLLslx/PID/PID Controller/Tsamp - Integral'
 * '<S26>'  : 'SOGI_PLLslx/PID/PID Controller/Tsamp - Ngain'
 * '<S27>'  : 'SOGI_PLLslx/PID/PID Controller/postSat Signal'
 * '<S28>'  : 'SOGI_PLLslx/PID/PID Controller/preSat Signal'
 * '<S29>'  : 'SOGI_PLLslx/PID/PID Controller/Anti-windup/Passthrough'
 * '<S30>'  : 'SOGI_PLLslx/PID/PID Controller/D Gain/Disabled'
 * '<S31>'  : 'SOGI_PLLslx/PID/PID Controller/Filter/Disabled'
 * '<S32>'  : 'SOGI_PLLslx/PID/PID Controller/Filter ICs/Disabled'
 * '<S33>'  : 'SOGI_PLLslx/PID/PID Controller/I Gain/Internal Parameters'
 * '<S34>'  : 'SOGI_PLLslx/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S35>'  : 'SOGI_PLLslx/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'SOGI_PLLslx/PID/PID Controller/Integrator/Discrete'
 * '<S37>'  : 'SOGI_PLLslx/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S38>'  : 'SOGI_PLLslx/PID/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S39>'  : 'SOGI_PLLslx/PID/PID Controller/N Gain/Disabled'
 * '<S40>'  : 'SOGI_PLLslx/PID/PID Controller/P Copy/Disabled'
 * '<S41>'  : 'SOGI_PLLslx/PID/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'SOGI_PLLslx/PID/PID Controller/Reset Signal/Disabled'
 * '<S43>'  : 'SOGI_PLLslx/PID/PID Controller/Saturation/Passthrough'
 * '<S44>'  : 'SOGI_PLLslx/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S45>'  : 'SOGI_PLLslx/PID/PID Controller/Sum/Sum_PI'
 * '<S46>'  : 'SOGI_PLLslx/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S47>'  : 'SOGI_PLLslx/PID/PID Controller/Tracking Mode/Disabled'
 * '<S48>'  : 'SOGI_PLLslx/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'SOGI_PLLslx/PID/PID Controller/Tsamp - Integral/Passthrough'
 * '<S50>'  : 'SOGI_PLLslx/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'SOGI_PLLslx/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S52>'  : 'SOGI_PLLslx/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S53>'  : 'SOGI_PLLslx/SOGI_PLL/PLL'
 * '<S54>'  : 'SOGI_PLLslx/SOGI_PLL/SOGI'
 * '<S55>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/Alpha-Beta-Zero to dq0'
 * '<S56>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller'
 * '<S57>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/Alpha-Beta-Zero to dq0/Compare To Constant'
 * '<S58>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/Alpha-Beta-Zero to dq0/Compare To Constant1'
 * '<S59>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/Alpha-Beta-Zero to dq0/Subsystem - pi//2 delay'
 * '<S60>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/Alpha-Beta-Zero to dq0/Subsystem1'
 * '<S61>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Anti-windup'
 * '<S62>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/D Gain'
 * '<S63>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Filter'
 * '<S64>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Filter ICs'
 * '<S65>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/I Gain'
 * '<S66>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Ideal P Gain'
 * '<S67>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Ideal P Gain Fdbk'
 * '<S68>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Integrator'
 * '<S69>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Integrator ICs'
 * '<S70>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/N Copy'
 * '<S71>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/N Gain'
 * '<S72>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/P Copy'
 * '<S73>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Parallel P Gain'
 * '<S74>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Reset Signal'
 * '<S75>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Saturation'
 * '<S76>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Saturation Fdbk'
 * '<S77>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Sum'
 * '<S78>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Sum Fdbk'
 * '<S79>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tracking Mode'
 * '<S80>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tracking Mode Sum'
 * '<S81>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tsamp - Integral'
 * '<S82>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tsamp - Ngain'
 * '<S83>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/postSat Signal'
 * '<S84>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/preSat Signal'
 * '<S85>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Anti-windup/Passthrough'
 * '<S86>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/D Gain/Disabled'
 * '<S87>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Filter/Disabled'
 * '<S88>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Filter ICs/Disabled'
 * '<S89>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/I Gain/Internal Parameters'
 * '<S90>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Ideal P Gain/Passthrough'
 * '<S91>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S92>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Integrator/Discrete'
 * '<S93>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Integrator ICs/Internal IC'
 * '<S94>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S95>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/N Gain/Disabled'
 * '<S96>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/P Copy/Disabled'
 * '<S97>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S98>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Reset Signal/Disabled'
 * '<S99>'  : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Saturation/Passthrough'
 * '<S100>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Saturation Fdbk/Disabled'
 * '<S101>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Sum/Sum_PI'
 * '<S102>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Sum Fdbk/Disabled'
 * '<S103>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tracking Mode/Disabled'
 * '<S104>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S105>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tsamp - Integral/Passthrough'
 * '<S106>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S107>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/postSat Signal/Forward_Path'
 * '<S108>' : 'SOGI_PLLslx/SOGI_PLL/PLL/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_SOGI_PLLslx_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
