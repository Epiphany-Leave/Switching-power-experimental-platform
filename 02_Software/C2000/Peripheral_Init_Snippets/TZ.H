/*
 * TZ.H
 *
 *  Created on: 2025年7月14日
 *      Author: c
 */

#ifndef APP_APP_H_TZ_H_
#define APP_APP_H_TZ_H_

#include "f28x_project.h"
#define L_mode 0
#define H_mode 1

/* DAC值  AIO  mode为0为L mode为高为H*/
/*
 * IO 分类：
 *  0:  A2/B6/C9
 *  1:  A11/B10/C0
 *  2:  A6
 *  3:  A15
 *  4:  A1/B7/DACB_OUT
 *  5:  B5
 * */
void TZ_Cmpss_1_Init(uint16_t Val,Uint16 Io,Uint16 Mode);
/*
 * IO 分类：
 *  0:  A4/B8
 *  1:  A12
 *  2:  A9
 *  3:  A10/B1/C10
 *  4:  B0/C11
 *  5:  A5
 * */
void TZ_Cmpss_2_Init(uint16_t Val,Uint16 Io,Uint16 Mode);
/*
 * IO 分类：
 *  0:  B2/C6
 *  1:  B12/C2
 *  2:  A0/B15/C15/DACA_OUT
 *  3:  B3/VDAC
 *  4:  A14/B14/C4
 *  5:  A3
 * */
void TZ_Cmpss_3_Init(uint16_t Val,Uint16 Io,Uint16 Mode);
/*
 * IO 分类：
 *  0:  B4/C8
 *  1:  A7/C3
 *  2:  C1
 *  3:  C14
 *  4:  A8
 *  5:  B11
 * */
void TZ_Cmpss_4_Init(uint16_t Val,Uint16 Io,Uint16 Mode);


#endif /* APP_APP_H_TZ_H_ */
