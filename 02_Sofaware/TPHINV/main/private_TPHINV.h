#include "ELAB_subsystem.h"
#include "KEY_ELAB.h"
#include "TPHINV_ELAB.h"
#include "TPHINV_KEY.h"
#define MY_PWM_FREQUENCY  20000
#define ctrl_FREQUENTCY_DIV  1
#define ELAB_step   TPHINV_ELAB_step
#define ELAB_initialize   TPHINV_ELAB_initialize
#define KEY_step   TPHINV_KEY_step
#define KEY_initialize   TPHINV_KEY_initialize
#define rtU_ELAB   rtU_TPHINV_ELAB
#define rtY_ELAB   rtY_TPHINV_ELAB
#define rtU_KEY   rtU_TPHINV_KEY
#define rtY_KEY   rtY_TPHINV_KEY
#define PWMA_ENA  1 
#define PWMB_ENA  1 
#define PWMC_ENA  1 
#define PWMD_ENA  0 
#define PWMA_MODE  1 
#define PWMB_MODE  1 
#define PWMC_MODE  1 
#define PWMD_MODE  0 
#define delay_time  100
