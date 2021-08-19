/*
 * MH_UART.h
 *
 *  Created on: 7 jul. 2021
 *      Author: root
 */

#ifndef MH_UART_H_
#define MH_UART_H_

#include "fsl_common.h"


#define MAX_BUFF_RX 32
#define MAX_BUFF_TX 32
#define MAX_DATOS	255


int16_t UART0_PopTX(void);
void UART0_PushTX(uint8_t);
int16_t UART0_PopRX(void);
void UART0_PushRX(uint8_t);
int16_t Transmitir (const void *, uint8_t);
#define RxUART0() UART0_PopRX()


#endif /* MH_UART_H_ */
