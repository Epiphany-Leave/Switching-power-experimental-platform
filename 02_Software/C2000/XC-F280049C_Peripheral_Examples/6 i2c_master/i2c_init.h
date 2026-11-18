#ifndef _I2C_INIT_H_
#define _I2C_INIT_H_
//#############################################################################
//
// FILE:   i2c_init.h
//
// TITLE:  I2C INITIALIZE HEADER
//
//  Group:            C2000
//  Target Family:    F2837xD
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2013-2021 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//
// Function Prototypes
//


//
// Error Messages
//
#define I2C_ERROR               0xFFFF
#define I2C_ARB_LOST_ERROR      0x0001
#define I2C_NACK_ERROR          0x0002
#define I2C_BUS_BUSY_ERROR      0x1000
#define I2C_STP_NOT_READY_ERROR 0x5555
#define I2C_NO_FLAGS            0xAAAA
#define I2C_SUCCESS             0x0000


extern void InitI2CGpio();
extern void I2CA_Init(void);
extern Uint16 I2C_xrdy();
extern Uint16 I2C_rrdy();
extern Uint16 I2CA_WriteData(Uint16 slaveaddr, Uint16 addr, Uint16 len, unsigned char *str);
extern Uint16 Writetoeepromstr(Uint16 addr, Uint16 len, unsigned char *str);
extern Uint16 I2CA_ReadData(Uint16 slaveaddr, Uint16 addr, Uint16 len, unsigned char *str);
extern void ReadfromeepromStr(Uint16 addr, Uint16 len, unsigned char *str);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _I2C_INIT_H_ definition

//
// End of file
//
