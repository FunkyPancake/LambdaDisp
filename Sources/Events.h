/* ###################################################################
**     Filename    : Events.h
**     Project     : KE04_DSP
**     Processor   : MKE04Z8VWJ4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-22, 00:07, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*!
**     @brief
**         Called at the end of the whole write / erase operation. if
**         the event is enabled. See SetEventMask() and GetEventMask()
**         methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
