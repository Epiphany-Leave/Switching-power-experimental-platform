/*
 * CAN.h
 *
 *  Created on: 2025年3月5日
 *      Author: 
 */

#ifndef USER_H_CAN_H_
#define USER_H_CAN_H_

#include "f28x_project.h"


#define PF_SET_CMD 0x01//命令帧
#define PF_SET_CMD_ACK 0x02//命令帧回复
#define PF_HEART_BEAT 0x20//心跳帧
#define PF_RECORD_VALUE 0x10//状态上报帧
void Can_Init(uint32_t clockFreq, uint32_t bitRate,uint16_t bitTime);    //Can初始化
void CanRecord(void);

extern long CAN_Data1_L,CAN_Data1_H,CAN_Data2_L,CAN_Data2_H;
extern long CAN_Data0_L,CAN_Data0_H;
extern long CAN_ID0,CAN_ID1,CAN_ID2;


#endif /* USER_H_CAN_H_ */
