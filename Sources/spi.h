/*
 * spi.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */
#include <stdint.h>
#include "CS_DAC.h"
#ifndef SPI_H_
#define SPI_H_

#define CS_DAC_SET 		(CS_DAC_PutVal(1))
#define CS_DAC_CLEAR 	(CS_DAC_PutVal(0))

#define MCP4922_SET_DAC(x) (x<<15)
#define MCP4922_BUF_MASK 0x4000
#define MCP4922_GA_MASK 0x2000
#define MCP4922_SHDN_MASK 0x1000



uint8_t SPISendChar(uint8_t data);

void DacSendCode(uint16_t data,uint8_t dac_num);

void DacHighZ(uint8_t dac_num);

#endif /* SPI_H_ */
