/*
 * File: SOGI_PLLslx.c
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

#include "SOGI_PLLslx.h"
#include "SOGI_PLLslx_private.h"

/* Real-time model */
static RT_MODEL_SOGI_PLLslx_T SOGI_PLLslx_M_;
RT_MODEL_SOGI_PLLslx_T *const SOGI_PLLslx_M = &SOGI_PLLslx_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (SOGI_PLLslx_M->Timing.TaskCounters.TID[1])++;
  if ((SOGI_PLLslx_M->Timing.TaskCounters.TID[1]) > 499) {/* Sample time: [5.0E-5s, 0.0s] */
    SOGI_PLLslx_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void SOGI_PLLslx_step(void)
{
  rate_scheduler();
}

/* Model initialize function */
void SOGI_PLLslx_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void SOGI_PLLslx_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
