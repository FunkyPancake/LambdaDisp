/*
 * table.c
 *
 *  Created on: Feb 11, 2017
 *      Author: Mati
 */
#include <stdint.h>
#include"table.h"

int8_t LookupCurve(uint16_t xval,int16_t* yval,table_2d_1r_t* map)
{
	uint8_t i,j;
	if(xval >= map->x[map->li])
		i =map->li;
	else
		i=0;
	if(xval <= map->x[0])
	{
		*yval =  map->y[0];
		return 2;
	}
	if(xval >= map->x[TABLE_2D_LENGTH-1])
	{
		*yval = map->y[TABLE_2D_LENGTH-1];
		return 2;
	}
	for(;i<TABLE_2D_LENGTH;i++)
	{
		if(xval == map->x[i])
		{
			*yval = map->y[i];
			map->li = i;
			return 1;
		}
		if(xval < map->x[i])
			break;

	}
	j = i-1;
	map->li = j;
	
	*yval =(int16_t) ((map->y[i]-map->y[j])*(xval-map->x[j])/(map->x[i]-map->x[j]));
	*yval += map->y[j];
	return 0;
}
