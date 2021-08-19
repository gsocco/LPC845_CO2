/*
 * app.c
 *
 *  Created on: 12 ago. 2021
 *      Author: root
 */

#include "main.h"

extern volatile int demoraMHZ19;
extern volatile char bufferChar[];
extern volatile uint16_t concentracionCO2;
extern uint8_t cmdLeerCO2[];


void maquinaAPP(void){

	static estadoAPP = IDLE;

	switch(estadoAPP){
	case IDLE:
		demoraMHZ19 = DEMORA_PREHEAT;
		LCD_Clear();
		LCD_Display("Calentando",0,3);
		LCD_Display("Sensor ",1,3);
		estadoAPP = CALENTANDO;
		break;
	case CALENTANDO:
		LCD_Display("    ",1,10);
		LCD_Display(itoa((demoraMHZ19/1000),bufferChar,10),1,10);

		if(!demoraMHZ19){
			LCD_Clear();
			LCD_Display("CO2: ",0,1);
			LCD_Display(itoa((concentracionCO2),bufferChar,10),0,8);
			LCD_Display("ppm",0,12);
			Transmitir (cmdLeerCO2, 9);
			estadoAPP = MIDIENDO;
		}
		break;
	case MIDIENDO:
		Transmitir (cmdLeerCO2, 9);
		LCD_Display("    ",0,8);
		LCD_Display(itoa((concentracionCO2),bufferChar,10),0,7);
		if(concentracionCO2 > 800){
			estadoAPP = ALARMA;
		}else{
			estadoAPP = NORMAL;
		}
		break;

	case NORMAL:
		BUZZER_OFF;
		LED_ROJO_OFF;
		LCD_Display("                ",1,0);
		LCD_Display("Ventilacion OK",1,1);
		estadoAPP = MIDIENDO;
		break;

	case ALARMA:
		LCD_Display("                ",1,0);
		LCD_Display("***VENTILAR***",1,1);
		LED_ROJO_ON;
		BUZZER_TOGGLE;
		estadoAPP = MIDIENDO;
		break;

	case CALIBRANDO:
		break;
	default:
		break;
	}

}
