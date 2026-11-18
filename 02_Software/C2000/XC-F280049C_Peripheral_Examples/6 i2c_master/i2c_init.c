#include "F28x_Project.h"
#include "i2c_init.h"
#include "i2c_opt.h"

void InitI2CGpio()
{
// For this example, only init the pins for the SCI-A port.
// These functions are found in the F2837xS_Gpio.c file.
//   GPIO_SetupPinMux(32, GPIO_MUX_CPU1, 1);
//   GPIO_SetupPinMux(33, GPIO_MUX_CPU1, 1);
	EALLOW;
	/* Enable internal pull-up for the selected I2C pins */
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;

	/* Set qualification for the selected I2C pins */
	GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;
	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;

	/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   //SDAA
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   //SCLA

	EDIS;
}

void I2CA_Init(void)
{
	// Initialize I2C
	//InitI2CGpio();

    GPIO_SetupPinMux(32, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(32, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(33, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(33, GPIO_OUTPUT, GPIO_PULLUP);

	I2caRegs.I2CMDR.bit.IRS = 0;          //The I2C module is in reset/disabled.
//   I2caRegs.I2CSAR.all = 0x0050;      // Slave address - EEPROM control code

	I2caRegs.I2CPSC.all = 19;         // I2C Module Clock = SYSCLK/I2CPSC+1   Prescaler - need 7-12 Mhz on module clk
	I2caRegs.I2CCLKL = 5;           // NOTE: must be non zero  High-time duration:10MHz/(5+5+5+5)*0.5
	I2caRegs.I2CCLKH = 5;           // NOTE: must be non zero  Low-time duration:10MHz/(5+5+5+5)*0.5
	I2caRegs.I2CIER.all = 0x00;      // Enable SCD & ARDY __interrupts

	I2caRegs.I2CIER.all = 0x24;
	I2caRegs.I2CFFTX.all = 0x0000;
	I2caRegs.I2CMDR.bit.IRS = 1;
//   I2caRegs.I2CMDR.all = 0x0020;  // Take I2C out of reset
	// Stop I2C when suspended

	// I2caRegs.I2CFFTX.all = 0x6000; // Enable FIFO mode and TXFIFO
	//I2caRegs.I2CFFRX.all = 0x2040; // Enable RXFIFO, clear RXFFINT,

	return;
}

Uint16 I2C_xrdy()
{
	Uint16 t;
	t = I2caRegs.I2CSTR.bit.XRDY;         //数据发送中断标志位；0未做好准备
	return t;
}

Uint16 I2C_rrdy()
{
	Uint16 t;
	t = I2caRegs.I2CSTR.bit.RRDY;         //数据接受中断标志位
	return t;
}

Uint16 I2CA_WriteData(Uint16 slaveaddr, Uint16 addr, Uint16 len,
		unsigned char *str)
{
	Uint16 i;

	if (I2caRegs.I2CMDR.bit.STP == 1)
	{
		return I2C_STP_NOT_READY_ERROR;
	}

	// Setup slave address
	I2caRegs.I2CSAR.all = slaveaddr;

	// Check if bus busy
	if (I2caRegs.I2CSTR.bit.BB == 1)
	{
		return I2C_BUS_BUSY_ERROR;
	}

	// Setup number of bytes to send
	// MsgBuffer + Address
	I2caRegs.I2CCNT = len + 2;

	// Setup data to send
	I2caRegs.I2CDXR.all = addr >> 8;
	I2caRegs.I2CMDR.all = 0x6E20;
	while (!I2C_xrdy())
		;
	I2caRegs.I2CDXR.all = addr & 0xff;

	for (i = 0; i < len; i++)

	{
		while (!I2C_xrdy())
			;
		I2caRegs.I2CDXR.all = *(str + i);
		if (I2caRegs.I2CSTR.bit.NACK == 1)
			return I2C_BUS_BUSY_ERROR;
	}

	// Send start as master transmitter

	return I2C_SUCCESS;
}
//////////////////////////////////////
Uint16 Writetoeepromstr(Uint16 addr, Uint16 len, unsigned char *str)
{
	Uint16 i = 0, j = 0;
	j = len / 8;
	if (j == 0)
	{
		for (i = 0; i < 1; i++)
		{
			I2CA_WriteData(0x50, addr + i, len, str + i);
			DELAY_US(10000);   //必须等待5MS，EEPROM规定连续写间隔
		}
	}
	else
	{
		for (i = 0; i < j; i++)
		{
			I2CA_WriteData(0x50, addr + i * 8, 8, str + i * 8);
			DELAY_US(10000);   //必须等待5MS，EEPROM规定连续写间隔
		}
	}
	return 1;
}

Uint16 I2CA_ReadData(Uint16 slaveaddr, Uint16 addr, Uint16 len,
		unsigned char *str)
{
	Uint16 i;
	if (I2caRegs.I2CMDR.bit.STP == 1)
	{
		return I2C_STP_NOT_READY_ERROR;
	}

	I2caRegs.I2CSAR.all = slaveaddr;

	if (I2caRegs.I2CSTR.bit.BB == 1)
	{
		return I2C_BUS_BUSY_ERROR;
	}
	I2caRegs.I2CCNT = 2;
	I2caRegs.I2CDXR.all = addr >> 8;
	I2caRegs.I2CMDR.all = 0x6620;         // Send data to setup RTC address
	while (!I2C_xrdy())
		;
	I2caRegs.I2CDXR.all = addr & 0xff;
	if (I2caRegs.I2CSTR.bit.NACK == 1)
		return I2C_BUS_BUSY_ERROR;
	while (!I2C_xrdy())
		;

	I2caRegs.I2CSAR.all = slaveaddr;
	I2caRegs.I2CCNT = len;
	I2caRegs.I2CMDR.all = 0x6C20;
	if (I2caRegs.I2CSTR.bit.NACK == 1)
		return I2C_BUS_BUSY_ERROR;
	for (i = 0; i < len; i++)
	{
		while (!I2C_rrdy())
			;
		*(str + i) = I2caRegs.I2CDRR.all;
		if (I2caRegs.I2CSTR.bit.NACK == 1)
			return I2C_BUS_BUSY_ERROR;
	}
	DELAY_US(200);
	return I2C_SUCCESS;
}

void ReadfromeepromStr(Uint16 addr, Uint16 len, unsigned char *str)
{
	Uint16 i = 0, j = 0;
	j = len / 8;
	if (j == 0)
	{
		for (i = 0; i < 1; i++)
			I2CA_ReadData(0x50, addr + i, len, str + i);
	}
	else
	{
		for (i = 0; i <= j; i++)
		{
			I2CA_ReadData(0x50, addr + i * 8, 8, str + i * 8);
			DELAY_US(20);
		}
	}

}
