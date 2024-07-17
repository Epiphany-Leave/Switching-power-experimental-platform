#include "ELAB_subsystem.h"
#include "KEY_ELAB.h"
#include "buck_ELAB.h"
#include "buck_KEY.h"
#define MY_PWM_FREQUENCY  20000
#define ctrl_FREQUENTCY_DIV  1
#define ELAB_step   buck_ELAB_step
#define ELAB_initialize   buck_ELAB_initialize
#define KEY_step   buck_ELAB_step
#define KEY_initialize   buck_ELAB_initialize
#define rtU_ELAB   rtU_buck_ELAB
#define rtY_ELAB   rtY_buck_ELAB
#define rtU_KEY   rtU_buck_KEY
#define rtY_KEY   rtY_buck_KEY
#define PWMA_ENA  1 
#define PWMB_ENA  0 
#define PWMC_ENA  0 
#define PWMD_ENA  0 
#define PWMA_MODE  1 
#define PWMB_MODE  0 
#define PWMC_MODE  0 
#define PWMD_MODE  0 
