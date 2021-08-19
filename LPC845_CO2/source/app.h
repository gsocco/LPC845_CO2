/*
 * app.h
 *
 *  Created on: 12 ago. 2021
 *      Author: root
 */

#ifndef APP_H_
#define APP_H_

/**
 * Estados máuina APP
 * */
#define IDLE 		1
#define CALENTANDO 	2
#define MIDIENDO	3
#define NORMAL		4
#define ALARMA		5
#define CALIBRANDO	6



void maquinaAPP(void);

#endif /* APP_H_ */
