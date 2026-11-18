#include "F28x_Project.h"
#include "i2c_opt.h"
#include "i2c_init.h"

Uint16 EEPROM_BufferRead[128];
Uint16 EEPROM_BufferWrite[128];

Uint16 WriteData(Uint16 *Wdata, Uint16 RomAddress, Uint16 number) //从地址，数据要保存在设备中的地址
{
	Uint16 i;
	if (I2caRegs.I2CSTR.bit.BB == 1) //总线被占用
	{
		return I2C_BUS_BUSY_ERROR;
	}
	while (!I2C_xrdy())
		;         //发送数据到设置的 EEPROM 地址
	I2caRegs.I2CSAR.all = 0x50;          //从地址
	I2caRegs.I2CCNT = number + 1;       //数据计数寄存器
	I2caRegs.I2CDXR.all = RomAddress;  //数据发送寄存器
	I2caRegs.I2CMDR.all = 0x6E20;     //配置模式：从机接收，发送起始信号，主机模式，发送，10位地址
	for (i = 0; i < number; i++)
	{
		while (!I2C_xrdy())
			;
		I2caRegs.I2CDXR.all = *Wdata; //数据发送寄存器
		Wdata++;
		if (I2caRegs.I2CSTR.bit.NACK == 1) //收到无应答信号
			return I2C_BUS_BUSY_ERROR;
	}
	return I2C_SUCCESS;
}

Uint16 ReadData(Uint16 *RamAddr, Uint16 RomAddress, Uint16 number)
{
	Uint16 i, Temp;

	if (I2caRegs.I2CSTR.bit.BB == 1)      //总线被占用
	{
		return I2C_BUS_BUSY_ERROR;
	}
	while (!I2C_xrdy())
		;
	I2caRegs.I2CSAR.all = 0x50;
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CDXR.all = RomAddress;
	I2caRegs.I2CMDR.all = 0x6620;
	if (I2caRegs.I2CSTR.bit.NACK == 1)
		return I2C_BUS_BUSY_ERROR;
	DELAY_US(50);
	while (!I2C_xrdy())
		;
	I2caRegs.I2CSAR.all = 0x50;
	I2caRegs.I2CCNT = number;
	I2caRegs.I2CMDR.all = 0x6C20;      //主机模式，接收，7位
	if (I2caRegs.I2CSTR.bit.NACK == 1)      //收到无应答信号，
		return I2C_BUS_BUSY_ERROR;
	for (i = 0; i < number; i++)
	{
		while (!I2C_rrdy())
			;
		Temp = I2caRegs.I2CDRR.all;  //数据接收寄存器
		if (I2caRegs.I2CSTR.bit.NACK == 1)
			return I2C_BUS_BUSY_ERROR;
		*RamAddr = Temp;
		RamAddr++;
	}
	return I2C_SUCCESS;
}

void I2C_EEPROM_Test(void)
{
	int i, j, k;


	for(i = 0, j = 0, k = 0; i < 128; i++)
	{
		j++;
		EEPROM_BufferWrite[i] = 0xFF;
		if(j == 16)
		{
			k++;
			j = 0;
			WriteData(&EEPROM_BufferWrite[(k - 1) * 16], 0x60 + (k - 1) * 16, 16);
			DELAY_US(10000);
		}
	}

	DELAY_US(10000);

	for(i = 0; i < 128; i++)
	{
		EEPROM_BufferRead[i] = 0;
	}
	for(i = 0, j = 0, k = 0; i < 128; i++)
	{
		j++;
		if(j == 16)
		{
			k++;
			j = 0;
			ReadData(&EEPROM_BufferRead[(k - 1) * 16], 0x60 + (k - 1) * 16, 16);
			DELAY_US(10000);
		}
	}

	for(i = 0, j = 0, k = 0; i < 128; i++)
	{
		j++;
		EEPROM_BufferWrite[i] = i;
		if(j == 16)
		{
			k++;
			j = 0;
			WriteData(&EEPROM_BufferWrite[(k - 1) * 16], 0x60 + (k - 1) * 16, 16);
			DELAY_US(10000);
		}
	}
	DELAY_US(10000);




	for(i = 0; i < 128; i++)
	{
		EEPROM_BufferRead[i] = 0;
	}
	for(i = 0, j = 0, k = 0; i < 128; i++)
	{
		j++;
		if(j == 16)
		{
			k++;
			j = 0;
			ReadData(&EEPROM_BufferRead[(k - 1) * 16], 0x60 + (k - 1) * 16, 16);
			DELAY_US(10000);
		}
	}
}













