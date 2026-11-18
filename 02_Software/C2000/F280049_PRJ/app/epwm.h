/*
 * epwm.h
 *
 *  Created on: 2025年11月13日
 *      Author: 45276
 */

#ifndef APP_EPWM_H_
#define APP_EPWM_H_

#include "f28x_project.h" // 所有头文件都必须包含

void EPwm_Init(Uint16 tbprd);

void InitEPwm1Gpio(void);
void EPwm1_Init(Uint16 tbprd);
__interrupt void EPWM1_CONFIG(void);
void InitEPwm2Gpio(void);
void EPwm2_Init(Uint16 tbprd);
__interrupt void EPWM2_CONFIG(void);

#endif /* APP_EPWM_H_ */
