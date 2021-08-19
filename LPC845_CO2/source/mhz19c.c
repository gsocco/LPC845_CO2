/*
 * mhz19c.c
 *
 *  Created on: 8 jul. 2021
 *      Author: root
 */

#include <stdlib.h>
#include "mhz19c.h"
#include "MH_UART.h"
#include "lcd.h"



extern volatile uint32_t demoraMHZ19;
extern volatile uint16_t concentracionCO2;
uint8_t lecturaMHZ19C[8];

extern volatile char bufferChar[];

uint8_t cmdLeerCO2[]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

uint16_t obtieneCO2(uint8_t hi, uint8_t lo){
	uint16_t acumuladorCO2 = 0;
	acumuladorCO2 = hi*256 + lo;
	return acumuladorCO2;
}

uint8_t getCheckSum(uint8_t *paquete)
{
	uint8_t i, checksum;
	for( i = 1; i < 8; i++)
	{
		checksum += paquete[i];
	}
	checksum = 0xff - checksum;
	checksum = checksum + 1;
	return checksum;
}

void receptorMHZ19C(void){
	static uint8_t estadoRX = IDLE;
	static uint8_t indiceRXMHZ19C = 0;
	static uint8_t dato_Hi, dato_Lo;
	int16_t datoRX;

	datoRX = RxUART0();

	if(datoRX > 0){
		switch(estadoRX){
		case IDLE:
			if(datoRX == 0xFF){
				indiceRXMHZ19C++;
				estadoRX = COMANDO;
			}
			break;

		case COMANDO:
			if(datoRX == 0x86){
				estadoRX = DATOHI;
			}else{
				estadoRX = IDLE;
			}
			break;

		case DATOHI:
			dato_Hi = datoRX;
			estadoRX = DATOLO;
			break;
		case DATOLO:
			dato_Lo = datoRX;
			concentracionCO2 = obtieneCO2(dato_Hi, dato_Lo);
			estadoRX = IDLE;
			break;

		default:
			break;
		}
	}

}

