/*
 * COM_Raspberry.c
 *
 *  Created on: Jan 10, 2024
 *      Author: kzail
 */


#include "COM_Raspberry.h"
#include "usart.h"
// Déclaration des tampons et du buffer
uint8_t Val1[4], Val2[4], Val3[4], Val4[4], Val5[4], Val6[4], Val7[4];
uint8_t buff[28];
int i = 0;


// Fonction principale pour envoyer les données via la communication UART
void mainUART(uint16_t BL, uint16_t BM, uint16_t BR, uint16_t FL, uint16_t FM, uint16_t FR) {
  // Appel de la fonction pour préparer les données dans les tampons
  buffering5ms(BL, BM, BR, FL, FM, FR);

  // Condition pour envoyer les données lorsque le compteur atteint 4
  if (i == 4) {
    // Appel de la fonction pour envoyer les données via la communication UART
    sendingData();
    i = 0;
  }
}

// Fonction pour préparer les données dans les tampons
void buffering5ms(uint16_t CPT1, uint16_t CPT2, uint16_t CPT3, uint16_t CPT4, uint16_t CPT5, uint16_t CPT6) {
  // Mis en forme des données 16 bits en 2 fois 8
	  Val1[0+i] = CPT1 >> 8;
	  Val1[1+i] = CPT1 & 0x00FF;

	  Val2[0+i] = CPT2 >> 8;
	  Val2[1+i] = CPT2 & 0x00FF;

	  Val3[0+i] = CPT3 >> 8;
	  Val3[1+i] = CPT3 & 0x00FF;

	  Val4[0+i] = CPT4 >> 8;
	  Val4[1+i] = CPT4 & 0x00FF;

	  Val5[0+i] = CPT5>>8;
	  Val5[1+i] = CPT5 & 0x00FF;

	  Val6[0+i] = CPT6>>8;
	  Val6[1+i] = CPT6 & 0x00FF;


  // Ajoutez des lignes similaires pour les autres capteurs

  i += 2;
}

// Fonction pour envoyer les données via la communication UART
void sendingData() {
  // Copie des octets des tampons dans le buffer pour former une trame de données
  buff[0] = Val1[0];
  buff[1] = Val1[1];

  buff[0] = Val1[0];
  buff[1] = Val1[1];

  buff[2] = Val2[0];
  buff[3] = Val2[1];

  buff[4] = Val3[0];
  buff[5] = Val3[1];

  buff[6] = Val4[0];
  buff[7] = Val4[1];

  buff[8] = Val5[0];
  buff[9] = Val5[1];

  buff[10] = Val6[0];
  buff[11] = Val6[1];

  buff[12] = Val7[0];
  buff[13] = Val7[1];

  buff[14] = Val1[2];
  buff[15] = Val1[3];

  buff[16] = Val2[2];
  buff[17] = Val2[3];

  buff[18] = Val3[2];
  buff[19] = Val3[3];

  buff[20] = Val4[2];
  buff[21] = Val4[3];

  buff[22] = Val5[2];
  buff[23] = Val5[3];

  buff[24] = Val6[2];
  buff[25] = Val6[3];

  buff[26] = Val7[2];
  buff[27] = Val7[3];

  // Ajoutez des lignes similaires pour les autres capteurs

  // Envoi du buffer via la communication UART
  HAL_UART_Transmit(&huart1, buff, sizeof(buff), HAL_MAX_DELAY);
}

