/*
 * table.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */

#ifndef TABLE_H_
#define TABLE_H_

#define TABLE_2D_LENGTH 24
typedef struct{
	uint16_t x[TABLE_2D_LENGTH];
	int16_t  y[TABLE_2D_LENGTH];
	uint8_t  li;//last index
}curve_t;
int8_t LookupCurve(uint16_t xval,int16_t* yval,table_2d_1r_t* map);

#endif /* TABLE_H_ */
