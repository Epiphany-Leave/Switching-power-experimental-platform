/*
 * hrpwm.h
 *
 *  Created on: 2025年11月19日
 *      Author: 45276
 */

#ifndef APP_HRPWM_H_
#define APP_HRPWM_H_

#include "f28x_project.h" // 所有头文件都必须包含

#define AUTOCONVERT 1
void HRPWM1_Init(Uint16 tbprd);
void HRPWM1_CPM_Set(Uint32 val);    // Q15格式写入  0~100% 0~1 0~0xffff（32768）


#endif /* APP_HRPWM_H_ */
