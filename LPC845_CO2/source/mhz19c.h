/*
 * mhz19c.h
 *
 *  Created on: 8 jul. 2021
 *      Author: root
 */

#ifndef MHZ19C_H_
#define MHZ19C_H_

#include <stdint.h>

// Estados de maquina MH-Z19C
#define INICIAL 		1
#define PREHEAT 		2
#define LEER_CO2 		3
#define CONSULTAR_CO2   4
#define DEMORA_PREHEAT	120000
#define DEMORA_LECTURA	12000

// Estados de maquina de rx de MH-Z19C
#define IDLE 	1
#define COMANDO	2
#define DATOLO	3
#define DATOHI	4


void receptorMHZ19C(void);


#endif /* MHZ19C_H_ */
