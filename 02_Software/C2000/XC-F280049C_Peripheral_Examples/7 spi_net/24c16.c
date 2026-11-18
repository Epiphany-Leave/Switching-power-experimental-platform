#include "24c16.h"
#include "ult.h"
#include "config.h"

void at24c16_init(void)
{


}

void at24c16_start(void)
{

}

void at24c16_stop(void)
{

}

void write_1byte(unsigned char val)
{
  
}


unsigned char read_1byte(void)
{
  return 0;
}

void clock(void)
{

}

void at24c16_write(uint16 addr, uint8 val)
{

}

unsigned char at24c16_read(uint16 addr)
{
  return 0;
}
//eep block write
//eepAddr: eeprom start address
//dat: data array to be saved to eeprom
//index: data array start index
//len: how long to be write
void eep_block_write(uint16 eepAddr, uint8* dat, uint16 index, uint16 len)
{

}

void erase_eeprom(uint16 startAddr, uint16 len)
{	  

}

