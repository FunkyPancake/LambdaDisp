/* ###################################################################
**     Filename    : main.c
**     Project     : KE04_DSP
**     Processor   : MKE04Z8VWJ4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-22, 00:07, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PIT.h"
#include "DISP1.h"
#include "BitIoLdd1.h"
#include "DISP2.h"
#include "BitIoLdd2.h"
#include "DISP3.h"
#include "BitIoLdd3.h"
#include "BitIoLdd4.h"
#include "HTR_PWM.h"
#include "PwmLdd1.h"
#include "Bit1.h"
#include "TU2.h"
#include "SM1.h"
#include "CS_DAC.h"
#include "BitIoLdd5.h"
#include "SysTick.h"
#include "CS_CJ.h"
#include "BitIoLdd6.h"
#include "ADC.h"
#include "CS_DSP.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "table.h"
#include "cj125.h"
#include "led.h"
#include <string.h>
#include "typedefs.h"
#include "spi.h"



uint8_t dig_tab[3] = {0,0,0};
rt_data data;
pid_t heater_pid;
const curve_t dac1_c = {
		{65,70,75,81,86,92,97,103,108,113,119,124,130,135,141,146,151,157,162,168,173,179,184,190},
		{0,178,356,534,712,890,1068,1246,1424,1602,1780,1958,2136,2314,2492,2670,2848,3026,3204,3382,3560,3738,3916,4095}
};
const curve_t dac2_c =
{
		{65,70,75,81,86,92,97,103,108,113,119,124,130,135,141,146,151,157,162,168,173,179,184,190},
		{82,82,82,82,82,82,350,400,820,820,820,820,820,820,820,820,820,820,820,820,820,820,820,820}
};
const curve_t lambda_afr_c= 
{
		{510,707,884,1041,1104,1177,1299,1409,1448,1480,1500,1507,1548,1596,1624,1663,1832,1964,2069,2186,2342,2490,2565,2614},
		{65,70,75,80,82,85,90,95,97,99,100,101,105,110,113,118,143,170,199,243,341,540,750,1000}
};
curve_t dac1,dac2,lambda_afr;
uint16_t ui16_SimpleFilter(const uint16_t input,const uint16_t last_out);

uint16_t ui16_SimpleFilter(const uint16_t input,const uint16_t last_out)
{
	#define INPUT_WEIGHT 5
	#define LAST_OUT_WEIGTH 95
	return (INPUT_WEIGHT * input + LAST_OUT_WEIGTH * last_out) / (INPUT_WEIGHT + LAST_OUT_WEIGTH);
}

PE_ISR(sys_isr)
{
	static uint8_t tmp =0;
	//data.vbat = (int16_t)((20189*data.ain3)/0x0fff);

	if(tmp > 9){
		data.update = 1;
		tmp=0;
	}
	else
		tmp++;
	
}

PE_ISR(adc_isr)
{
	int16_t tmp[3];
	tmp[0] = ADC_R;
	tmp[1] = ADC_R;
	//tmp[2] = ADC_R;
	data.ain1 = ui16_SimpleFilter(tmp[0],data.ain1);
	data.ain2 = ui16_SimpleFilter(tmp[1],data.ain2);
	//data.ain3 = ui16_SimpleFilter(tmp[2],data.ain3);
}
PE_ISR(Mux_isr)
{
	static uint8_t ev_cnt =0;
	if(data.state == OPERATIONAL)
	{
		if(ev_cnt & 0x3)
		{
			DacSendCode(data.dac_out1,0);
			DacSendCode(data.dac_out2,1);
		}
	}
	LedMux(dig_tab);
	ev_cnt++;
	PIT_TFLG1 = 1;
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	int16_t i;
	//uint32_t mean[2] = {0,0};
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
 
  /* Write your code here */
  SPI0_C1 &= ~(uint32_t)(SPI_C1_CPHA_MASK);
  SPI0_C2 &= ~(uint32_t)(SPI_C2_MODFEN_MASK);
  ADC_SC1 = 4;
  ADC_SC1 = (ADC_SC1_AIEN_MASK | 9);
  heater_pid.upper_limit = 11500;
  heater_pid.iterm_limit = 6000;
  heater_pid.kp = 10;
  heater_pid.ki= 2;
  heater_pid.kd = 0;
  data.state = PREHEAT;
  memcpy(&dac1,&dac1_c,sizeof(table_2d_1r_t));
  memcpy(&dac2,&dac2_c,sizeof(table_2d_1r_t));
  memcpy(&lambda_afr,&lambda_afr_c,sizeof(table_2d_1r_t));
  DacHighZ(0);
  DacHighZ(1);
  PIT_Init();
  /*cj125 init*/
  CJ125SendCommand(CJ125_CTRL1_W_ADDR,0x84);
  CJ125SendCommand(CJ125_CTRL2_W_ADDR,0x02);
  i = CJ125SendCommand(CJ125_DIAG_R_ADDR,0);
  SPI0_C1 &= ~(uint32_t)(SPI_C1_CPHA_MASK);
  SPI0_C2 &= ~(uint32_t)(SPI_C2_MODFEN_MASK);
  if((i & 0xc0)!= 0xc0)
  {
	  data.state = FAILURE;
	  data.cj_status = 1;
  }
 /* i = CJ125SendCommand(CJ125_IDENT_R_ADDR,0);
  if(i == 0x63)
  {
    CJ125SendCommand(CJ125_CTRL1_W_ADDR,0x9c);
    CJ125SendCommand(CJ125_CTRL2_W_ADDR,0x02);
    for(i=0;i<100;i++)
    {
    	while((ADC_SC1 & ADC_SC1_COCO_MASK) == ADC_SC1_COCO_MASK)
    		;
    	mean[0] = ADC_R;
    	mean[1] = ADC_R;
    }
    data.un_offset =  mean[0]/100;//UN
    data.ur_offset = mean[1]/100;//UR
    
  }*/

  /* For example: for(;;) { } */
  WDog1_Enable();
  for(;;)
  {
	if(data.update == 1)
	{
		data.vbat = 12000;
		data.ur = (int16_t)((5000*data.ain1)/0x0fff);
		data.un = (int16_t)((5000*data.ain2)/0x0fff);

		HeaterTask();
		LookupCurve(data.un,&data.afr,&lambda_afr);
		LookupCurve(data.afr,&data.dac_out1,&dac1);
		LookupCurve(data.afr,&data.dac_out2,&dac2);
		if(data.state == OPERATIONAL)
		{
			if(data.afr==1000)
			{
				WriteLed(10,dig_tab);
			}
			else
			NumTo7(data.afr,dig_tab);
		}
		else
		{
			WriteLed(data.cj_status,dig_tab);
			data.dac_out1 = 0;
			data.dac_out2 = 0;
		}
		data.update = 0;
	}
	WDog1_Clear();
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
