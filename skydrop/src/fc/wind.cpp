/*
 * wind2.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: fiala
 */

#include "wind.h"
#include "fc.h"
#include "../common.h"


void wind_new_gps_fix()
{
	//DEBUG("Wind step #1");
	/*	GPS speed,heading input		*/
	float speed = fc.gps_data.ground_speed * FC_KNOTS_TO_MPS; // m/s
	float angle = fc.gps_data.heading;

	uint8_t sector = int(angle + (360 / WIND_NUM_OF_SECTORS / 2 )) % 360 / (360 / WIND_NUM_OF_SECTORS);

	fc.wind.dir[sector] = angle;
	fc.wind.spd[sector] = speed;

	//DEBUG(" angles: ");
	//	for(int i = 0; i < WIND_NUM_OF_SECTORS; i++)
	//		DEBUG(" %.1f", fc.wind.dir[i]);
	/*DEBUG(" speeds: ");
		for(int i = 0; i < WIND_NUM_OF_SECTORS; i++)
			DEBUG(" %.1f", fc.wind.spd[i]);

	DEBUG(" #2");
	*/
	if (sector == (fc.wind.old_sector + 1) % WIND_NUM_OF_SECTORS)
	{	//clockwise move
		if(fc.wind.sectors_cnt >= 0)
			fc.wind.sectors_cnt += 1;
		else
			fc.wind.sectors_cnt = 0;
	}
	else if (fc.wind.old_sector == (sector + 1) % WIND_NUM_OF_SECTORS)
	{	//counterclockwise move
		if(fc.wind.sectors_cnt <=0 )
			fc.wind.sectors_cnt -= 1;
		else
			fc.wind.sectors_cnt = 0;
	}
	else if (fc.wind.old_sector == sector)
	{	//same sector
	}
	else //more than (360 / number_of_sectors), discart data
		fc.wind.sectors_cnt = 0;

	fc.wind.old_sector = sector;
	//DEBUG(" #3 cnt=%d sec=%d", fc.wind.sectors_cnt, sector );

	int8_t min = 0;
	int8_t max = 0;
	if (abs( fc.wind.sectors_cnt) >= WIND_NUM_OF_SECTORS)
	{
		//DEBUG(" #4");
		for( int i = 0 ; i < WIND_NUM_OF_SECTORS ; i++ )
		{
			if (i == 0)
				continue;
			if (fc.wind.spd[i] > fc.wind.spd[max])
				max = i;
			if (fc.wind.spd[i] < fc.wind.spd[min])
				min = i;
		}

		int8_t sectorDiff = abs(max - min);
		//DEBUG("min=%d max=%d diff=%d",min, max, sectorDiff);
		if ((sectorDiff >= ( WIND_NUM_OF_SECTORS / 2 - 1 )) and (sectorDiff <= ( WIND_NUM_OF_SECTORS / 2 + 1 )))
		{
			fc.wind.speed = (fc.wind.spd[max] - fc.wind.spd[min]) / 2;
			fc.wind.direction = fc.wind.dir[min];
        	fc.wind.valid = true;
        	//DEBUG(" #5 wspd=%0.1f wdir=%0.1f", fc.wind.speed, fc.wind.direction);
		}
		//DEBUG(" #6");
	}

	//DEBUG(" end\n");
}

void wind_init()
{
	for(int i=0 ; i < WIND_NUM_OF_SECTORS ; i++)
	{
		fc.wind.spd[i] = 0;
		fc.wind.dir[i] = 0;
	}

	fc.wind.sectors_cnt = 0;
	fc.wind.old_sector = 0;
	fc.wind.valid = false;

	DEBUG("wind_init\n");
}

void wind_step()
{
	if (fc.gps_data.new_sample & FC_GPS_NEW_SAMPLE_WIND)
	{
		wind_new_gps_fix();

		fc.gps_data.new_sample &= ~FC_GPS_NEW_SAMPLE_WIND;
	}
}
