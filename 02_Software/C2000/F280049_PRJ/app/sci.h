/*
 * sci.h
 *
 *  Created on: 2025年12月1日
 *      Author: 45276
 */

#ifndef APP_SCI_H_
#define APP_SCI_H_

#include "f28x_project.h" // 所有头文件都必须包含

__interrupt void SCIA_Rx_IRQn();
void SCIA_Init(Uint32 baud, Uint16 RXFrameLength);

int SCIA_SendByte(Uint16 data);
int SCIA_SendString(const char *msg);

void SCIA_Reset(void);

int SCIA_SendFloatToVOFA(float data);
int SCIA_SendFloatToVOFA2(float data1, float data2);
int SCIA_SendFloatToVOFA3(float data1, float data2, float data3);

#endif /* APP_SCI_H_ */
