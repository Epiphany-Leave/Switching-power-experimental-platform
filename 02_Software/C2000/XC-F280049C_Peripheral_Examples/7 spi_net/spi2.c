#include "driverlib.h"
#include "device.h"
#include "config.h"
#include "socket.h"
#include "w5500.h"
//#include "ult.h"
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include "DSP2833x_Device.h"
uint8 SPI_I2S_ReceiveData(void);
void set_default(void);

void WIZ_SPI_Init(void)//Bluetooth
{

}

void WIZ_CS(uint8 val)
{
	if (val == 0)
    {
	    GPIO_writePin(59, 0);
        //GpioDataRegs.GPBDAT.bit.GPIO57 = 0;
    }
    else if (val == 1)
    {
        GPIO_writePin(59, 1);
        //GpioDataRegs.GPBDAT.bit.GPIO57 = 1;
    }
}

uint8 SPI2_SendByte(uint8 byte)
{
	uint8 SPIRXD;


	while((HWREGH(SPIB_BASE + SPI_O_STS) & SPI_STS_BUFFULL_FLAG) == SPI_STS_BUFFULL_FLAG)
	    ;
	SPI_writeDataNonBlocking(SPIB_BASE, byte<<8);
    while((HWREGH(SPIB_BASE + SPI_O_STS) & SPI_STS_INT_FLAG) != SPI_STS_INT_FLAG)
        ;
	SPIRXD = SPI_readDataBlockingNonFIFO(SPIB_BASE);


	//while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1);
	//SpiaRegs.SPITXBUF=(byte<<8);
	//while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);{}//Wait until data is received
	//SPIRXD = SpiaRegs.SPIRXBUF;

	return SPIRXD;

}





