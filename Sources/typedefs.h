/*
 * typedefs.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Mati
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

enum heater_state_e{
	PREHEAT,
	RAMP_UP,
	HEATUP,
	OPERATIONAL,
	FAILURE
};


typedef struct
{
	int16_t ain1,ain2,ain3;
	int16_t ur,un,vbat;
	int16_t heater_v;
	uint16_t duty;
	int16_t afr;
	int16_t dac_out1,dac_out2;
	uint8_t cj_status;
	uint8_t update;
	int16_t ur_offset,un_offset;
	enum heater_state_e state;
}rt_data;
typedef struct{
	int16_t upper_limit,lower_limit;
	int32_t iterm_limit;
	int32_t iterm;
	int16_t last;
	int16_t kp,ki,kd;
}pid_t;
#endif /* TYPEDEFS_H_ */
