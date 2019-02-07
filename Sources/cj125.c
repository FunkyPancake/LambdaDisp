/*
 * cj125.c
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */
#include "cj125.h"
#include "spi.h"

#include "HTR_PWM.h"
extern rt_data data;
extern pid_t heater_pid;
const cn_data_t con_data ={
		3000,2500,1500,1028
};
uint8_t CJ125SendCommand(uint8_t command, uint8_t data)
{
	SPI0_C1 |= SPI_C1_CPHA_MASK;
	uint8_t rdata;
	CS_CJ_CLEAR;
	if(SPISendChar(command) == 0xff)
		return -1;
	rdata = SPISendChar(data);
	CS_CJ_SET;
	SPI0_C1 &= ~(uint32_t)(SPI_C1_CPHA_MASK);
	return rdata;
}


int16_t Pid(int16_t process, int16_t target,pid_t* pid)
{
	int16_t error,derror;
	int32_t tmp;
	error = process- target;
	derror = error - pid->last;
	pid->iterm += error;
	pid->last = error;
	if(pid->iterm>pid->iterm_limit)
	   pid->iterm=pid->iterm_limit;
	if(pid->iterm<-pid->iterm_limit)
	  pid->iterm=-pid->iterm_limit;
	tmp = (pid->kp*error + ((pid->iterm*pid->ki)>>1)+derror*pid->kd);
	if(tmp>pid->upper_limit)
	{
		return pid->upper_limit;
	}
	if(tmp<0)
	{
		return 0;
	}
	return tmp;
}
//10ms period
void HeaterTask(void)
{
	static uint32_t task_timer = 0;
	switch(data.state)
	{
		case PREHEAT:
			if((task_timer < con_data.preheat_time)/* && (data.ur > con_data.condesation_switch_th)*/)
			{
				data.heater_v = 2000;
				task_timer++;
			}
			else
			{
				task_timer = 0;
				data.state =  RAMP_UP;
				data.heater_v = 8000;
			}
			break;
		case RAMP_UP:
			if(data.heater_v >12000)
			{
				data.state = HEATUP;
			}
			data.heater_v +=4;
			break;
		case HEATUP:
			if(data.ur < con_data.operational_switch_th)
			{
				data.state = OPERATIONAL;
			}
		case OPERATIONAL:
			data.heater_v = Pid(data.ur,con_data.pid_htr_trg,&heater_pid);
			break;
		default:
			data.heater_v = 0;
			break;
	}
	data.duty = 0xffff-((0xffffL*data.heater_v)/data.vbat);
	SetHeaterDuty(data.duty);
}
