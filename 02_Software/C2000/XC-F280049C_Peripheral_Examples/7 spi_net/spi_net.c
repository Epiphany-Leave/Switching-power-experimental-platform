//#############################################################################
//
// FILE:   main.c
//
// TITLE:  Universal LED Project
//
// Universal LED Project Example
//
// This example demonstrates how to blink an LED using the **Universal Project**.
// In order to migrate the project within syscfg, click the swtich button under 
// the device view and select your corresponding device to migrate, saving the
// project will auto-migrate your project settings.
//!
//!  \note This example project has support for migration across our C2000 
//!  device families. If you are wanting to build this project from launchpad
//!  or controlCARD, please specify in the .syscfg file the board you're using.
//!  At any time you can select another device to migrate this example.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

#include "device.h"
#include "spi2.h"
#include "ult.h"
#include "socket.h"
#include "w5500.h"
#include "24c16.h"
#include "md5.h"
#include "string.h"

extern uint8 txsize[];
extern uint8 rxsize[];

uint8 buffer[2048];
#define   LedReg    (*((volatile  Uint16 *)0x41FF))
uint16    *ExRamStart = (uint16 *)0x100000;

// Prototype statements for functions found within this file.
// interrupt void ISRTimer2(void);
void delay_loop(void);
void spi_xmit(uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);
void gpio_config(void);


#define SPIB_controller_BASE        SPIB_BASE
#define SPIB_controller_BITRATE     1500000
#define SPIB_controller_DATAWIDTH   8


uint32_t i;


// Main
//
void main(void)
{
    uint8 server_ip[4]={192,168,3,27};
    uint16 server_port=8764;
    uint16 local_port=6000;
    uint16 len=0;


    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    EALLOW;

    // GPIO32 -> INTn Pinmux
    GPIO_setPinConfig(GPIO_24_GPIO24);
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_IN);
    GPIO_setControllerCore(24, GPIO_CORE_CPU1);

    // GPIO33 -> RSTn Pinmux
    GPIO_setPinConfig(GPIO_22_GPIO22);
    GPIO_setPadConfig(22, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(22, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(22, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(22, GPIO_CORE_CPU1);


    //
    // SPIB -> SPIB_controller Pinmux
    //


    GPIO_setPinConfig(GPIO_58_SPIB_CLK);
    GPIO_setPadConfig(58, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);

    GPIO_setPadConfig(59, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(59, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(59, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(59, GPIO_CORE_CPU1);

    GPIO_setPinConfig(GPIO_56_SPIB_SIMO);
    GPIO_setPadConfig(56, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(56, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_57_SPIB_SOMI);
    GPIO_setPadConfig(57, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(57, GPIO_QUAL_ASYNC);

    SPI_disableModule(SPIB_controller_BASE);
    SPI_setConfig(SPIB_controller_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL1PHA0,
                  SPI_MODE_CONTROLLER, SPIB_controller_BITRATE, SPIB_controller_DATAWIDTH);
    //SPI_setPTESignalPolarity(SPIB_controller_BASE, SPI_PTE_ACTIVE_LOW);
    SPI_disableFIFO(SPIB_controller_BASE);
    SPI_disableLoopback(SPIB_controller_BASE);
    SPI_setEmulationMode(SPIB_controller_BASE, SPI_EMULATION_FREE_RUN);
    SPI_enableModule(SPIB_controller_BASE);



    gpio_config();

    spi_init();        // init SPI

    EDIS;

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    Reset_W5500();

    set_default();
    set_network();


    //
    // Loop Forever
    //
    for(;;)
    {
        i++;
        switch(getSn_SR(0))
        {
        case SOCK_UDP:
            if(getSn_IR(0) & Sn_IR_RECV)
            {
                setSn_IR(0, Sn_IR_RECV);
            }

            if((len=getSn_RX_RSR(0)) > 0)
            {
                memset(buffer, 0, len+1);
                len -= 8;
                recvfrom(0,buffer, len, server_ip,&server_port);
                //printf("%s\r\n",buffer);
                sendto(0,buffer,len, server_ip, server_port);
            }
            break;

        case SOCK_CLOSED:
            socket(0,Sn_MR_UDP,local_port,Sn_MR_MC);
            break;
        }

        if(i >= 1000)
        {
            i = 0;
            GPIO_togglePin(myBoardLED0_GPIO);
        }
    }
}



void delay_loop()
{
    long      i;
    for (i = 0; i < 1000000; i++) {}
}


void error(void)
{
    asm("     ESTOP0");                     // Test failed!! Stop!
    for (;;);
}

void spi_init()
{
    //SpiaRegs.SPICCR.bit.SPISWRESET = 0;//
    //SpiaRegs.SPICCR.all = 0x0047;     //The SPI software resets the polarity bit
                                    //to 1 (sending data along the falling edge),
                                    //moving in and out of the 8 bit word length each time,
                                    //and prohibiting the SPI internal loopback (LOOKBACK) function;
    //SpiaRegs.SPICTL.all = 0x0006;     // Enable master mode, normal phase, // enable talk, and SPI int disabled.
    //SpiaRegs.SPISTS.all = 0x0000;     //溢出中断，禁止SPI中断；
    //SpiaRegs.SPIBRR = 0x001F;         //SPI波特率=37.5M/24=1.5MHZ；
    //SpiaRegs.SPIPRI.bit.FREE = 1;     //Set so breakpoints don't disturb xmission
    //SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

void spi_xmit(uint16 a)
{
    //SpiaRegs.SPITXBUF=a;
    SPI_writeDataNonBlocking(SPIB_BASE, a);
}



void gpio_config(void)
{
    //EALLOW;
     //GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1;
     //GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
     //GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
     //GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;
     //EDIS;
}
void Reset_W5500(void)
{
    GPIO_writePin(22, 0);
    delay_loop();
    GPIO_writePin(22, 1);
    delay_loop();
}

/*void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
        *DestAddr++ = *SourceAddr++;
    }
    return;

}*/

//
// End of File
//

