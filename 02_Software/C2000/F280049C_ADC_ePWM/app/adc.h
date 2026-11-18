/*
 * adc.h
 *
 *  Created on: 2025年11月27日
 *      Author: 45276
 */

#ifndef APP_ADC_H_
#define APP_ADC_H_

#include "f28x_project.h" // 所有头文件都必须包含

__interrupt void adcA1ISR();
void ADCA_Init(void);

#endif /* APP_ADC_H_ */
