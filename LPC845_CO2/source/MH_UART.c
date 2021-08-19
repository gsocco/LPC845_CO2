/*
 * MH_UART.c
 *
 *  Created on: 7 jul. 2021
 *      Author: root
 */

#include "peripherals.h"
#include "MH_UART.h"


unsigned char UART0_BufferRx[MAX_BUFF_RX];
unsigned char UART0_inRX = 0;
unsigned char UART0_outRX = 0;
unsigned char UART0_BufferTx[MAX_BUFF_TX];
unsigned char UART0_inTX = 0;
unsigned char UART0_outTX = 0;
bool UART0_flagTx = 0;


/**
	\fn int16_t Transmitir ( uint8_t com , const void * datos , uint8_t cant)
	\brief despacha los datos a transmitir
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t com: Puerto que sera utilizado
	\param [in] const void * datos: datos a transmitir
	\param [in] uint8_t cant: cantidad de datos a transmitir
	\return 0 por exito, -1 por Error (datos exedidos)
*/
int16_t Transmitir (const void * datos , uint8_t cant )
{
	uint8_t	i;

	if ( cant > MAX_DATOS )
		return -1;

	for ( i = 0 ; i < cant ; i++ )
		UART0_PushTX( * ( ( uint8_t * ) ( datos + i ) ) );

	return 0 ;
}



/* TODO: insert other definitions and declarations here. */
/**
	\fn  void PushRX( uint8_t dato )
	\brief pone un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART0_PushRX(uint8_t dato){
	UART0_BufferRx[UART0_inRX] = dato;
	UART0_inRX++;
	UART0_inRX %= MAX_BUFF_RX;
}

/**
	\fn  int16_t PopRX( void )
	\brief saca un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART0_PopRX(void){

	short salida = -1;
	if(UART0_inRX != UART0_outRX){
		salida = UART0_BufferRx[UART0_outRX];
		UART0_outRX++;
		UART0_outRX %= MAX_BUFF_RX;
	}
	return salida;
}


/**
	\fn  void PushTX( uint8_t dato )
	\brief pone un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART0_PushTX( uint8_t dato )
{
	if ( !UART0_flagTx )
	{
		UART0_flagTx = 1;
		USART0->TXDAT = dato;
		USART0->INTENSET |= USART_STAT_TXRDY_MASK; // Habilita interrupción de TXRDY
		return;
	}

	UART0_BufferTx[ UART0_inTX ] = dato;
	UART0_inTX ++;
	UART0_inTX %= MAX_BUFF_TX;
}

/**
	\fn int16_t PopTX( void )
	\brief saca un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART0_PopTX( void )
{
	int16_t salida = -1;

	if ( UART0_inTX != UART0_outTX )
	{
		salida = UART0_BufferTx[ UART0_outTX ] ;

		UART0_outTX ++;
		UART0_outTX %= MAX_BUFF_TX;
	}/*else{
		USART0->INTENSET &= ~USART_STAT_TXRDY_MASK;  // Deshabilita interrupción de TXRDY
	}*/
	return salida;
}

/* USART0_IRQn interrupt handler */
void USART0_USART_IRQHANDLER(void) {
  /*  Place your code here */
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif

    unsigned char temp = 0;
    short datoTx;
    if(USART0->INTSTAT & USART_STAT_RXRDY_MASK){
		// Rx
		temp = (unsigned char) USART0->RXDAT;
		UART0_PushRX(temp);
    }

    if(USART0->INTSTAT & USART_STAT_TXRDY_MASK){
		// Tx
		datoTx = UART0_PopTX();
		if ( datoTx != -1 )
			USART0->TXDAT = (uint8_t) datoTx;
		else{
			UART0_flagTx = 0;
			USART0->INTENCLR |= USART_STAT_TXRDY_MASK;  // Deshabilita interrupción de TXRDY
 		}
    }
}



