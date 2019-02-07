/*
 * cj125.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */

#ifndef CJ125_H_
#define CJ125_H_

#include<stdint.h>
#include "typedefs.h"
#include "CS_CJ.h"
#define CS_CJ_SET 		(CS_CJ_PutVal(1))
#define CS_CJ_CLEAR 	(CS_CJ_PutVal(0))
#define CJ125_CTRL1_W_ADDR 0x56
#define CJ125_CTRL2_W_ADDR 0x5A
#define CJ125_CTRL1_R_ADDR 0x6C
#define CJ125_CTRL2_R_ADDR 0x7E
#define CJ125_IDENT_R_ADDR 0x48
#define CJ125_DIAG_R_ADDR  0x78

#define SetHeaterDuty(x) HTR_PWM_SetRatio16(x)
#define UR_ERROR_MAX 1200


typedef struct
{
	int16_t preheat_time;
	int16_t condesation_switch_th;
	int16_t operational_switch_th;
	int16_t pid_htr_trg;
}cn_data_t;


uint8_t CJ125SendCommand(uint8_t command, uint8_t data);
int16_t Pid(int16_t process, int16_t target,pid_t* pid);
void HeaterTask(void);

#endif /* CJ125_H_ */
