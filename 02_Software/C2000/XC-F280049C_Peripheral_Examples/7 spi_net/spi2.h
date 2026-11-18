#ifndef __SPI2_H
#define __SPI2_H


#include "types.h"
void WIZ_SPI_Init(void);
void WIZ_CS(uint8 val);
uint8 SPI2_SendByte(uint8 byte);
#endif

