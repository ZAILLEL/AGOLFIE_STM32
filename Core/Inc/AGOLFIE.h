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


#define FRONT_STATUS
#define BACK_STATUS

enum {
	FRONT_OUT = 0,
	FRONT_L,
	FRONT_R,
	FRONT_C,
	FRONT_CL,
	FRONT_CR,
	FRONT_MS_MAX
};
__attribute__((unused)) static const char* _DEBUG_AGOLFIE_FORWARD[FRONT_MS_MAX] = {
	"FRONT_OUT",
	"FRONT_L",
	"FRONT_R",
	"FRONT_C",
	"FRONT_CL",
	"FRONT_CR",
};



enum {
	BACK_OUT = 0,
	BACK_L,
	BACK_R,
	BACK_C,
	BACK_CL,
	BACK_CR,
	BACK_MS_MAX
};
__attribute__((unused)) static const char* _DEBUG_AGOLFIE_BACKWARD[BACK_MS_MAX] = {
	"BACK_OUT",
	"BACK_L",
	"BACK_R",
	"BACK_C",
	"BACK_CL",
	"BACK_CR"
};




typedef struct us_sensor
{
	uint16_t distance;
	uint8_t addr;
}us_sensor;

struct AGOLFIE_SENSORS
{
	us_sensor Front_Left;
	us_sensor Front_CenterLeft;
	us_sensor Front_CenterRight;
	us_sensor Front_Right;

	us_sensor Back_Left;
	us_sensor Back_CenterLeft;
	us_sensor Back_CenterRight;
	us_sensor Back_Right;


	uint8_t front_status;
	uint8_t back_status;

	uint8_t ZONE_FRONT;
	uint8_t ZONE_BACK;
};

typedef struct position{
	int FL;
	int FCL;
	int FCR;
	int FR;
	int BL;
	int BCL;
	int BCR;
	int BR;
}position;

typedef struct zone{

}zone;

struct obstacle
{
	position position;
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
void Agolfie_SetSpeed(uint8_t p);


void refresh_obstacle(uint8_t distance_cm);
uint8_t refresh_front(uint8_t ZONE);
uint8_t refresh_back(uint8_t ZONE);
void obstacle1M();
void obstacle2M();
void obstacle3M();
void obstacle4M();


void Agolfie_Forward_dostep(uint8_t ZONE);

void Agolfie_Backward_dostep(uint8_t ZONE);

#endif /* INC_AGOLFIE_H_ */
