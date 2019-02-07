/*
 * led.c
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */

#include "led.h"
#include "spi.h"



extern uint8_t dig_tab[3];
const uint8_t seg71[] =
{
		0xB7,   //0
		0xA0,   //1
		0xC7,   //2
		0xE6,   //3
		0xF0,   //4
		0x76,   //5
		0x77,   //6
		0xA4,   //7
		0xF7,   //8
		0xF6,   //9
		0x40,   //-
		0x8,   //dp
		0x57,   //E
		0xF1,   //H
		0xB3,   //U
		0xD5,   //P
		0xF5,   //A
		0x20,   //i
		0x41   //r
};
//do poprawy
void NumTo7(int16_t input, uint8_t * outarray) 
{
	uint8_t digit[3];
	uint8_t i = 0;
	if(input < 0)
	{
		input*=(-1);
		i = 1;
	}
	digit[2] = input%10;
	input = input / 10;
	digit[1] = input%10;
	input = input / 10;
	if(i == 1)
		digit[0] = 10;
	else
		digit[0] = input%10; 
	for(i = 0;i<3;i++)
	{
	  *(outarray+i) = seg71[digit[i]];
	}      
	*(outarray) += seg71[11];
	return;
} 

void WriteLed(uint8_t err_code, uint8_t * outarray)
{
	uint8_t digit[3];
	uint8_t i = 0;
	switch (err_code)
	{
		case 0:
		{
			for(i = 0;i<3;i++)
			{
				digit[i] = i+13;
			}     
		
		break;
		}
		case 10:
		{
			for(i = 0;i<3;i++)
			{
				digit[i] = i+16;
			}    
			break;
		}
		default:
		{
			digit[0] = 12;
			digit[2] = err_code%10;
			err_code = err_code / 10;
			digit[1] = err_code%10;
		}	
	}
	for(i = 0;i<3;i++)
	{
	  *(outarray+i) = seg71[digit[i]];
	}  
	return;	
}

void LedMux(uint8_t *dig_tab)
{
	static uint8_t dnum = 0;	

	DISP1_SET;
	DISP2_SET;
	DISP3_SET;
	switch (dnum) 
	{
	case 0: 
		SPISendChar(dig_tab[2]);
		SPISendChar(0xff);
		CS_DSP_SET;	
		CS_DSP_CLEAR;
		dnum++;
		DISP1_CLEAR;
		break;
	case 1:
		SPISendChar(dig_tab[1]);
		SPISendChar(0xff);
		CS_DSP_SET;	
		CS_DSP_CLEAR;
		dnum++;
		DISP2_CLEAR;
		break;	
	case 2:
		SPISendChar(dig_tab[0]);
		SPISendChar(0xff);
		CS_DSP_SET;	
		CS_DSP_CLEAR;
		dnum=0;
		DISP3_CLEAR;
		break;
	default:
		dnum = 0;
		break;
	}
}
