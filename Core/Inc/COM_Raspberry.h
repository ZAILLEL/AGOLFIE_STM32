/*
 * COM_Raspberry.h
 *
 *  Created on: Jan 10, 2024
 *      Author: kzail
 */

#ifndef INC_COM_RASPBERRY_H_
#define INC_COM_RASPBERRY_H_

#include "main.h"



void mainUART(uint16_t BL, uint16_t BM, uint16_t BR, uint16_t FL, uint16_t FM, uint16_t FR);
void buffering5ms(uint16_t CPT1, uint16_t CPT2, uint16_t CPT3, uint16_t CPT4, uint16_t CPT5, uint16_t CPT6);
void sendingData();


#endif /* INC_COM_RASPBERRY_H_ */
