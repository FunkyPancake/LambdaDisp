/*
 * led.h
 *
 *  Created on: Feb 14, 2017
 *      Author: Mati
 */

#ifndef LED_H_
#define LED_H_
#include <stdint.h>
#include "CS_DSP.h"
#include "DISP3.h"
#include "DISP2.h"
#include "DISP1.h"
#define DISP1_SET 		(DISP1_PutVal(1))
#define DISP1_CLEAR		(DISP1_PutVal(0))
#define DISP2_SET 		(DISP2_PutVal(1))
#define DISP2_CLEAR 	(DISP2_PutVal(0))
#define DISP3_SET		(DISP3_PutVal(1))
#define DISP3_CLEAR 	(DISP3_PutVal(0))
#define CS_DSP_SET 		(CS_DSP_PutVal(1))
#define CS_DSP_CLEAR 	(CS_DSP_PutVal(0))


void WriteLed(uint8_t err_code, uint8_t * outarray);
void NumTo7(int16_t input, uint8_t * outarray);
void LedMux(uint8_t* dig_tab);

#endif /* LED_H_ */
