/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Bit1.c
**     Project     : KE04_DSP
**     Processor   : MKE04Z8VWJ4
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-09-05, 23:30, # CodeGen: 74
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : Bit1
**          Pin for I/O                                    : PTC3/KBI1_P5/FTM2_CH3/ADC0_SE11
**          Pin signal                                     : 
**          Direction                                      : Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : yes
**          Safe mode                                      : no
**     Contents    :
**         Init   - LDD_TDeviceData* Bit1_Init(LDD_TUserData *UserDataPtr);
**         PutVal - void Bit1_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Bit1.c
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup Bit1_module Bit1 module documentation
**  @{
*/         

/* MODULE Bit1. */

/* {Default RTOS Adapter} No RTOS includes */
#include "Bit1.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserDataPtr;          /* Pointer to user data */
} Bit1_TDeviceData;                    /* Device data structure type */

typedef Bit1_TDeviceData *Bit1_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static Bit1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  Bit1_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* Bit1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  Bit1_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Configure pin as output */
  /* GPIOA_PDDR: PDD|=0x00080000 */
  GPIOA_PDDR |= GPIO_PDDR_PDD(0x00080000);
  /* Set initialization value */
  /* GPIOA_PDOR: PDO&=~0x00080000 */
  GPIOA_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x00080000));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_Bit1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}
/*
** ===================================================================
**     Method      :  Bit1_PutVal (component BitIO_LDD)
*/
/*!
**     @brief
**         The specified output value is set. If the direction is <b>
**         input</b>, the component saves the value to a memory or a
**         register and this value will be written to the pin after
**         switching to the output mode (using <tt>SetDir(TRUE)</tt>;
**         see <a href="BitIOProperties.html#SafeMode">Safe mode</a>
**         property for limitations). If the direction is <b>output</b>,
**         it writes the value to the pin. (Method is available only if
**         the direction = <u><tt>output</tt></u> or <u><tt>
**         input/output</tt></u>).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Val             - Output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
void Bit1_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (Val) {
    GPIO_PDD_SetPortDataOutputMask(Bit1_MODULE_BASE_ADDRESS, Bit1_PORT_MASK);
  } else { /* !Val */
    GPIO_PDD_ClearPortDataOutputMask(Bit1_MODULE_BASE_ADDRESS, Bit1_PORT_MASK);
  } /* !Val */
}

/* END Bit1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
