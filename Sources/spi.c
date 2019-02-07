/*
 * spi.c
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */
#include "spi.h"
#include "MKE04Z4.h"


uint8_t SPISendChar(uint8_t data)
{
	volatile uint16_t timeout =0xffff;
	while(((SPI0_S & SPI_S_SPTEF_MASK) == 0) && (timeout))
		timeout--;
	SPI0_D = data;
	timeout =0xffff;
	while(((SPI0_S & SPI_S_SPRF_MASK) == 0) && (timeout))
		timeout--;
	data = SPI0_D;
	return data;
}


void DacSendCode(uint16_t data,uint8_t dac_num)
{
	data &= 0x0fff;
	data |= MCP4922_SET_DAC(dac_num) + MCP4922_SHDN_MASK + MCP4922_GA_MASK +MCP4922_BUF_MASK;
	CS_DAC_CLEAR;
	SPISendChar((uint8_t)(data>>8));
	SPISendChar(data);
	CS_DAC_SET;

}
void DacHighZ(uint8_t dac_num)
{
	uint16_t data = 0x0fff;
	data |= MCP4922_SET_DAC(dac_num);
	CS_DAC_CLEAR;
	SPISendChar((uint8_t)(data>>8));
	SPISendChar(data);
	CS_DAC_SET;
}

