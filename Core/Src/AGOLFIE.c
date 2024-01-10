/*
 * AGOLFIE.c
 *
 *  Created on: 10 janv. 2024
 *      Author: kzail
 */
#include "AGOLFIE.h"

#define    MEASURE_RANGE_BIT        ((uint8_t)0x01 << 4)
#define    MEASURE_MODE_BIT         ((uint8_t)0x01 << 2)
#define    TEMP_CPT_ENABLE_BIT		((uint8_t)0x01 << 1)
#define    TEMP_CPT_SEL_BIT 		((uint8_t)0x01 << 0)

#define NB_SENSORS 6

struct AGOLFIE_SENSORS AGOLFIE_SENSORS;
struct obstacle obstacle;


uint8_t addr[NB_SENSORS -1];

void config_sensors_address(uint8_t addr[]){

	 AGOLFIE_SENSORS.Back_Left.addr    = 0x01;
	 AGOLFIE_SENSORS.Back_Middle.addr  = 0x02;
	 AGOLFIE_SENSORS.Back_Right.addr   = 0x03;
	 AGOLFIE_SENSORS.Front_Left.addr   = 0x04;
	 AGOLFIE_SENSORS.Front_Middle.addr = 0x05;
	 AGOLFIE_SENSORS.Front_Right.addr  = 0x06;

	addr[0] = AGOLFIE_SENSORS.Back_Left.addr;
	addr[1] = AGOLFIE_SENSORS.Back_Middle.addr;
	addr[2] = AGOLFIE_SENSORS.Back_Right.addr;
	addr[3] = AGOLFIE_SENSORS.Front_Left.addr;
	addr[4] = AGOLFIE_SENSORS.Front_Middle.addr;
	addr[5] = AGOLFIE_SENSORS.Front_Right.addr;

}




void Agolfie_sensors_begin()
{
	config_sensors_address(addr[NB_SENSORS -1 ]);

	for (int i = 0; i<NB_SENSORS; i++){
		URM13_begin(addr[i]);
	}
}


void Agolfie_config_sensors(){

	  uint8_t cfg = 0;

	  cfg &= ~MEASURE_RANGE_BIT;//clear bit4,long-range ranging mode
	  //cfg |= MEASURE_RANGE_BIT;//set bit4,short-range ranging mode
	  //cfg |= MEASURE_MODE_BIT;//Set bit2，i2c passive mode
	  cfg &= ~MEASURE_MODE_BIT;//clear bit2 , set to Automatic ranging mode
	  cfg &= ~TEMP_CPT_ENABLE_BIT;//clear bit1,enable temperature compensation
	  //cfg |= TEMP_CPT_ENABLE_BIT;//set bit1,disable temperature compensation
	  cfg &= ~TEMP_CPT_SEL_BIT;//clear bit0,select internal temperature compensation
	  //cfg |= TEMP_CPT_SEL_BIT;//set bit0,select external temperature compensation

	  for (int i =0 ; i<NB_SENSORS ; i++){

		  writeReg(0x09, &cfg, sizeof(cfg),addr[i]);
	  }
}


void Agolfie_update_sensors_value()
{

	uint16_t sensors_value[NB_SENSORS - 1];
	uint8_t cmd[8] = {0};
	for (int i = 0; i<NB_SENSORS; i++)
	{
		cmd[i] |=0x01;
		if (writeReg(0x0A, &cmd[i], sizeof(cmd[i]),addr[i]) != 0)
		{
			sensors_value[i] = getDistanceCm(addr[i]);
		}
	}
	AGOLFIE_SENSORS.Back_Left.distance     =   sensors_value[0];
	AGOLFIE_SENSORS.Back_Middle.distance   =   sensors_value[1];
	AGOLFIE_SENSORS.Back_Right.distance    =   sensors_value[2];
	AGOLFIE_SENSORS.Front_Left.distance    =   sensors_value[3];
	AGOLFIE_SENSORS.Front_Middle.distance  =   sensors_value[4];
	AGOLFIE_SENSORS.Front_Right.distance   =   sensors_value[5];

	udebug_formatted_six("Back_Left = %d | Back_Middle = %d | Back_Right = %d  \r\n Front_Left = %d | Front_Middle = %d | Front_Right = %d",
			AGOLFIE_SENSORS.Back_Left.distance ,
			AGOLFIE_SENSORS.Back_Middle.distance ,
			AGOLFIE_SENSORS.Back_Right.distance ,
			AGOLFIE_SENSORS.Front_Left.distance ,
			AGOLFIE_SENSORS.Front_Middle.distance ,
			AGOLFIE_SENSORS.Front_Right.distance );

}



void obstacle1M() {

	obstacle.position1M.b_l = (AGOLFIE_SENSORS.Back_Left.distance    < 100);
	obstacle.position1M.b_m = (AGOLFIE_SENSORS.Back_Middle.distance  < 100);
	obstacle.position1M.b_r = (AGOLFIE_SENSORS.Back_Right.distance   < 100);
	obstacle.position1M.f_l = (AGOLFIE_SENSORS.Front_Left.distance   < 100);
	obstacle.position1M.f_m = (AGOLFIE_SENSORS.Front_Middle.distance < 100);
	obstacle.position1M.f_r = (AGOLFIE_SENSORS.Front_Right.distance  < 100);
}

void obstacle2M() {

	obstacle.position2M.b_l = (AGOLFIE_SENSORS.Back_Left.distance    < 200);
	obstacle.position2M.b_m = (AGOLFIE_SENSORS.Back_Middle.distance  < 200);
	obstacle.position2M.b_r = (AGOLFIE_SENSORS.Back_Right.distance   < 200);
	obstacle.position2M.f_l = (AGOLFIE_SENSORS.Front_Left.distance   < 200);
	obstacle.position2M.f_m = (AGOLFIE_SENSORS.Front_Middle.distance < 200);
	obstacle.position2M.f_r = (AGOLFIE_SENSORS.Front_Right.distance  < 200);
}


void obstacle3M() {

	obstacle.position3M.b_l = (AGOLFIE_SENSORS.Back_Left.distance    < 300);
	obstacle.position3M.b_m = (AGOLFIE_SENSORS.Back_Middle.distance  < 300);
	obstacle.position3M.b_r = (AGOLFIE_SENSORS.Back_Right.distance   < 300);
	obstacle.position3M.f_l = (AGOLFIE_SENSORS.Front_Left.distance   < 300);
	obstacle.position3M.f_m = (AGOLFIE_SENSORS.Front_Middle.distance < 300);
	obstacle.position3M.f_r = (AGOLFIE_SENSORS.Front_Right.distance  < 300);
}


void obstacle4M() {

	obstacle.position4M.b_l = (AGOLFIE_SENSORS.Back_Left.distance    < 400);
	obstacle.position4M.b_m = (AGOLFIE_SENSORS.Back_Middle.distance  < 400);
	obstacle.position4M.b_r = (AGOLFIE_SENSORS.Back_Right.distance   < 400);
	obstacle.position4M.f_l = (AGOLFIE_SENSORS.Front_Left.distance   < 400);
	obstacle.position4M.f_m = (AGOLFIE_SENSORS.Front_Middle.distance < 400);
	obstacle.position4M.f_r = (AGOLFIE_SENSORS.Front_Right.distance  < 400);
}

