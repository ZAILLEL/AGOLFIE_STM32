/*
 * AGOLFIE.c
 *
 *  Created on: 10 janv. 2024
 *      Author: kzail
 */
#include "AGOLFIE.h"
#include "gpio.h"


#define    MEASURE_RANGE_BIT        ((uint8_t)0x01 << 4)
#define    MEASURE_MODE_BIT         ((uint8_t)0x01 << 2)
#define    TEMP_CPT_ENABLE_BIT		((uint8_t)0x01 << 1)
#define    TEMP_CPT_SEL_BIT 		((uint8_t)0x01 << 0)

#define NB_SENSORS 8

struct AGOLFIE_SENSORS AGOLFIE_SENSORS;
struct obstacle obstacle;


uint8_t addr[NB_SENSORS -1];

void config_sensors_address(uint8_t addr[]){

	AGOLFIE_SENSORS.Back_Left.addr            = 0x01;
	AGOLFIE_SENSORS.Back_CenterLeft.addr      = 0x02;
	AGOLFIE_SENSORS.Back_CenterRight.addr     = 0x03;
	AGOLFIE_SENSORS.Back_Right.addr           = 0x04;

	AGOLFIE_SENSORS.Front_Left.addr           = 0x05;
	AGOLFIE_SENSORS.Front_CenterLeft.addr     = 0x06;
	AGOLFIE_SENSORS.Front_CenterRight.addr    = 0x07;
	AGOLFIE_SENSORS.Front_Right.addr          = 0x08;

	addr[0] = AGOLFIE_SENSORS.Back_Left.addr        ;
	addr[1] = AGOLFIE_SENSORS.Back_CenterLeft.addr  ;
	addr[2] = AGOLFIE_SENSORS.Back_CenterRight.addr ;
	addr[3] = AGOLFIE_SENSORS.Back_Right.addr       ;

	addr[4] = AGOLFIE_SENSORS.Back_Left.addr        ;
	addr[5] = AGOLFIE_SENSORS.Back_CenterLeft.addr  ;
	addr[6] = AGOLFIE_SENSORS.Back_CenterRight.addr ;
	addr[7] = AGOLFIE_SENSORS.Back_Right.addr       ;
}



void Agolfie_sensors_begin()
{
	config_sensors_address(addr);

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

	uint8_t sensors_value[NB_SENSORS - 1];
	uint8_t cmd[8] = {0};

	for (int i = 0; i<NB_SENSORS; i++)
	{
		cmd[i] |=0x01;
		if (writeReg(0x0A, &cmd[i], sizeof(cmd[i]),addr[i]) != 0)
		{
			sensors_value[i] = getDistanceCm(addr[i]);

		}
		HAL_Delay(20);
	}

	AGOLFIE_SENSORS.Front_Left.distance          =   sensors_value[0];
	AGOLFIE_SENSORS.Front_CenterLeft.distance    =   sensors_value[1];
	AGOLFIE_SENSORS.Front_CenterRight.distance   =   sensors_value[2];
	AGOLFIE_SENSORS.Front_Right.distance         =   sensors_value[3];
	AGOLFIE_SENSORS.Back_Left.distance           =   sensors_value[4];
	AGOLFIE_SENSORS.Back_CenterLeft.distance     =   sensors_value[5];
	AGOLFIE_SENSORS.Back_CenterRight.distance    =   sensors_value[6];
	AGOLFIE_SENSORS.Back_Right.distance  	     =   sensors_value[7];



	udebug_formatted_eight("Front_Left = %d | Front_CL = %d | Front_CR = %d | Front_Right = %d  \r\n  Back_Left = %d | Back_CL = %d | Back_CR = %d | Back_Right = %d ",
			AGOLFIE_SENSORS.Front_Left.distance,
			AGOLFIE_SENSORS.Front_CenterLeft.distance,
			AGOLFIE_SENSORS.Front_CenterRight.distance,
			AGOLFIE_SENSORS.Front_Right.distance,
			AGOLFIE_SENSORS.Back_Left.distance,
			AGOLFIE_SENSORS.Back_CenterLeft.distance ,
			AGOLFIE_SENSORS.Back_CenterRight.distance,
			AGOLFIE_SENSORS.Back_Right.distance  	  );


}





void refresh_obstacle(uint8_t distance_min_cm, uint8_t distance_max_cm) {


	Agolfie_update_sensors_value();

	obstacle.position.FL  = ((AGOLFIE_SENSORS.Front_Left.distance         < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.FCL = ((AGOLFIE_SENSORS.Front_CenterLeft.distance   < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.FCR = ((AGOLFIE_SENSORS.Front_CenterRight.distance  < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.FR  = ((AGOLFIE_SENSORS.Front_Right.distance        < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));

	obstacle.position.BL  = ((AGOLFIE_SENSORS.Back_Left.distance          < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.BCL = ((AGOLFIE_SENSORS.Back_CenterLeft.distance    < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.BCR = ((AGOLFIE_SENSORS.Back_CenterRight.distance   < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));
	obstacle.position.BR  = ((AGOLFIE_SENSORS.Back_Right.distance  	      < distance_max_cm)  && (AGOLFIE_SENSORS.Front_Left.distance         > distance_min_cm));


	AGOLFIE_SENSORS.front_status ^= ((AGOLFIE_SENSORS.front_status & 8) ^ (obstacle.position.FL   << 3));
	AGOLFIE_SENSORS.front_status ^= ((AGOLFIE_SENSORS.front_status & 4) ^ (obstacle.position.FCL  << 2));
	AGOLFIE_SENSORS.front_status ^= ((AGOLFIE_SENSORS.front_status & 2) ^ (obstacle.position.FCR  << 1));
	AGOLFIE_SENSORS.front_status ^= ((AGOLFIE_SENSORS.front_status & 1) ^ (obstacle.position.FR   << 0));

	AGOLFIE_SENSORS.back_status  ^= ((AGOLFIE_SENSORS.back_status & 8) ^ (obstacle.position.BL    << 3));
	AGOLFIE_SENSORS.back_status  ^= ((AGOLFIE_SENSORS.back_status & 4) ^ (obstacle.position.BCL   << 2));
	AGOLFIE_SENSORS.back_status  ^= ((AGOLFIE_SENSORS.back_status & 2) ^ (obstacle.position.BCR   << 1));
	AGOLFIE_SENSORS.back_status  ^= ((AGOLFIE_SENSORS.back_status & 1) ^ (obstacle.position.BR    << 0));

}


void Agolfie_Forward_dostep(uint8_t ZONE)
{
	ZONE = refresh_front(ZONE);

	switch(ZONE){

	case FRONT_OUT:
		Agolfie_SetSpeed(50);
		break;
	case FRONT_L:
		Agolfie_SetSpeed(0);
		break;
	case FRONT_R:
		Agolfie_SetSpeed(0);
		break;
	case FRONT_C:
		Agolfie_SetSpeed(0);
		break;
	case FRONT_CL:
		Agolfie_SetSpeed(0);
		break;
	case FRONT_CR:
		Agolfie_SetSpeed(0);
		break;
	}
}


void Agolfie_Backward_dostep(uint8_t ZONE) {

	ZONE = refresh_back(ZONE);

	switch(ZONE){

	case BACK_OUT:
		break;
	case BACK_L:
		break;
	case BACK_R:
		break;
	case BACK_C:
		break;
	case BACK_CL:
		break;
	case BACK_CR:
		break;
	}

}


uint8_t refresh_front(uint8_t ZONE) {

	switch (AGOLFIE_SENSORS.front_status) {
	case 0b0000:
		ZONE = FRONT_OUT;
		break;
	case 0b0001:
		ZONE = FRONT_R;
		break;
	case 0b1010:
		ZONE = FRONT_CR;
		break;
	case 0b0101:
		ZONE = FRONT_CL;
		break;
	case 0b1000:
		ZONE = FRONT_L;
		break;
	case 0b0110:
		ZONE = FRONT_C;
		break;
	}

	return ZONE;
}



void proto_sm()
{

	refresh_obstacle(50,80);


	/*********  LEDS en fonctions des capteurs **********/
	/*********       CAPTEURS AVANT            **********/

	if (AGOLFIE_SENSORS.front_status & 0b0001)
	{
		HAL_GPIO_WritePin(LED_FR_GPIO_Port,LED_FR_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_FR_GPIO_Port,LED_FR_Pin,0);
	}


	if (AGOLFIE_SENSORS.front_status & 0b0010)
	{
		HAL_GPIO_WritePin(LED_FCR_GPIO_Port,LED_FCR_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_FCR_GPIO_Port,LED_FCR_Pin,0);
	}


	if (AGOLFIE_SENSORS.front_status & 0b0100)
	{
		HAL_GPIO_WritePin(LED_FCL_GPIO_Port,LED_FCL_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_FCL_GPIO_Port,LED_FCL_Pin,0);
	}


	if (AGOLFIE_SENSORS.front_status & 0b1000)
	{
		HAL_GPIO_WritePin(LED_FL_GPIO_Port,LED_FL_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_FL_GPIO_Port,LED_FL_Pin,0);
	}





	/*********  LEDS en fonctions des capteurs **********/
	/*********       CAPTEURS ARRIERRES        **********/

	if (AGOLFIE_SENSORS.back_status & 0b0001)
	{
		HAL_GPIO_WritePin(LED_BR_GPIO_Port,LED_BR_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_BR_GPIO_Port,LED_BR_Pin,0);
	}

	if (AGOLFIE_SENSORS.back_status & 0b0010)
	{
		HAL_GPIO_WritePin(LED_BCR_GPIO_Port,LED_BCR_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_BCR_GPIO_Port,LED_BCR_Pin,0);
	}

	if (AGOLFIE_SENSORS.back_status & 0b0100)
	{
		HAL_GPIO_WritePin(LED_BCL_GPIO_Port,LED_BCL_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_BCL_GPIO_Port,LED_BCL_Pin,0);
	}

	if (AGOLFIE_SENSORS.back_status & 0b1000)
	{
		HAL_GPIO_WritePin(LED_BL_GPIO_Port,LED_BL_Pin,1);
	}
	else {
		HAL_GPIO_WritePin(LED_BL_GPIO_Port,LED_BL_Pin,0);
	}


}


uint8_t refresh_back(uint8_t ZONE)
{
	switch (AGOLFIE_SENSORS.back_status) {
	case 0b0000:
		ZONE = BACK_OUT;
		break;
	case 0b0001:
		ZONE = BACK_R;
		break;
	case 0b1010:
		ZONE = BACK_CR;
		break;
	case 0b0101:
		ZONE = BACK_CL;
		break;
	case 0b1000:
		ZONE = BACK_L;
		break;
	case 0b0110:
		ZONE = BACK_C;
		break;
	}

	return ZONE;
}




void Agolfie_init()
{
	AGOLFIE_SENSORS.ZONE_BACK = BACK_OUT;
	AGOLFIE_SENSORS.ZONE_FRONT = FRONT_OUT;
}



void Agolfie_SetSpeed(uint8_t p) {

    uint16_t dacValue = (p * 4095) / 100;



}


