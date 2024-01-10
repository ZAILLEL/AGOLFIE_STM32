/*
 * AGOLFIE.h
 *
 *  Created on: 10 janv. 2024
 *      Author: kzail
 */

#ifndef INC_AGOLFIE_H_
#define INC_AGOLFIE_H_

#include "../debug_toolbox/Inc/uart_tools.h"
#include "DFRobot_URM13.h"


typedef struct us_sensor
{
	uint16_t distance;
	uint8_t addr;
}us_sensor;

struct AGOLFIE_SENSORS
{
	us_sensor Front_Left;
	us_sensor Front_Middle;
	us_sensor Front_Right;
	us_sensor Back_Left;
	us_sensor Back_Middle;
	us_sensor Back_Right;
};

typedef struct position{
	int b_l;
	int b_m;
	int b_r;
	int f_l;
	int f_m;
	int f_r;

}position;


struct obstacle
{
	position position1M;
	position position2M;
	position position3M;
	position position4M;

};


// PRIVATE
void Agolfie_config_sensors_address(uint8_t addr[]);
// PUBLIC
void Agolfie_sensors_begin();
void Agolfie_config_sensors();
void Agolfie_update_sensors_value();
uint16_t getDistanceMin();

void obstacle1M();
void obstacle2M();
void obstacle3M();
void obstacle4M();


#endif /* INC_AGOLFIE_H_ */
