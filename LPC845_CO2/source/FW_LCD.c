/**
 \file		: lcd.c.c
 \brief     : Firmware de lcd
 \details   :
 \author    : GOS
 \date 	    : 2016.09.25
*/

#include <stdint.h>
#include "board.h"
#include "lcd.h"


extern struct LCD displayLCD;

extern volatile int demoraLCD;
uint8_t entero_ascii[6];
volatile uint32_t lcdDelay;

volatile uint8_t lcdBuffer[LCD_BUFFER_SIZE];
volatile uint32_t lcdInxIn;
volatile uint32_t lcdInxOut;
volatile uint32_t lcdDataCount;



/**
 * void LCDWaitLong(uint8_t ciclos)
 * Demora larga por SW
 *
 * */
void LCDWaitLong(uint16_t ciclos)
{
	uint16_t i;
	uint16_t x;

	for(i=0;i<ciclos;i++)
	{
		for(x = 0;x < 0x1FF6;x++);
	}
}

/**
 * void LCDWaitShort(uint8_t ciclos)
 * Demora corta por SW
 *
 * */
void LCDWaitShort(uint8_t ciclos)
{
	uint8_t i;
	uint16_t x;

	for(i=0;i<ciclos;i++)
	{
		for(x=0;x<0x9F6;x++);
	}
}


/**
 * void LCDDelay(uint16_t demora)
 * Demora medida por el tick
 *
 * */

void LCDDelay(uint16_t demora){

	demoraLCD = demora;
	while(demoraLCD);

}


/**
 * void LatchLcd(void)
 * Genera pulso de latch para LCD
 *
 * */
void LatchLcd(void){
	uint16_t i;

	LCD_E_ON;
	LCDWaitLong(5);
	for(i = 0; i < 40; i++);
	LCD_E_OFF;
}

/**
 * void Conversor(uint16_t valor_int)
 * Convierte un entero sin signo en ascii
 *
 * */
void Conversor(uint16_t valor_int){
	entero_ascii[4] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[3] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[2] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[1] = valor_int % 10 +48;
	entero_ascii[0] = valor_int /10 +48;

}

/**
 * void DisplayInt_lcd(uint16_t valor , uint8_t r , uint8_t p )
 * Escribe un entero en el LCD en la línea indicada por r
 * A partir de la posicion indicada por p
 *
 * */
void DisplayInt_lcd(uint16_t valor , uint8_t r , uint8_t p ){
	uint8_t i ;
	uint8_t flag_cero = 0;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	WComando8(p);
	Conversor(valor);
	for( i = 0 ; i < 5; i++ ){
		if(flag_cero == 0){
			if(entero_ascii[ i ] != '0'){
				flag_cero = 1;
				WDato(entero_ascii[ i ]);
			}
		}else{
			WDato(entero_ascii[ i ]);
		}

	}
}



/**
 * void Display_lcd( char *msg , char r , char p )
 * Escribe una cadena en el LCD en la línea indicada por r
 * A partir de la posicion indicada por p
 *
 * */
void Display_lcd( char *msg , char r , char p ){
	unsigned char i ;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	WComando8(p);
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		WDato(msg[ i ]);

}



/**
 * void Inic_PinesLCD(void)
 * Configura pines para manejo de LCD interfaz de 4 bits
 *
 * */
void Inic_PinesLCD(void){

}

/**
 * void WComando8(uint8_t comando)
 * Escribe un comando al LCD luego de inicialización
 * No usa BF
 *
 * */
void WComando8(uint8_t comando){
	LCD_RS_OFF;

	// Parte Alta del comando
	if((comando & 0x10) >> 4)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((comando & 0x20) >> 5)
		LCD_D5_ON;
	else
		LCD_D5_OFF;

	if((comando & 0x40) >> 6)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((comando & 0x80) >> 7)
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	LatchLcd();
	LCDDelay(1);

	// Parte Baja del comando
	if(comando & 0x01)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((comando & 0x02) >> 1)
		LCD_D5_ON;
	else
		LCD_D5_OFF;

	if((comando & 0x04) >> 2)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((comando & 0x08) >> 3)
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	LatchLcd();
	LCDDelay(2);

}

/**
 * void WComando4(uint8_t comando)
 * Escribe un comando al LCD en el proceso de inicialización
 * No usa BF
 *
 * */
void WComando4(uint8_t comando){
	LCD_RS_OFF;
	// Parte Alta del comando
	if((comando & 0x10) >> 4)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((comando & 0x20) >> 5)
		LCD_D5_ON;
	else
		LCD_D5_OFF;

	if((comando & 0x40) >> 6)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((comando & 0x80) >> 7)
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	LatchLcd();
	LCDDelay(1);

}

/**
 * void WDato (uint8_t dato)
 * Escribe un dato al LCD en interfaz de 4 bits
 * No usa BF
 *
 * */
void WDato (uint8_t dato)
{
	LCD_RS_ON;

	// Parte Alta del comando
	if((dato & 0x10) >> 4)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((dato & 0x20) >> 5)
		LCD_D5_ON;
	else
		LCD_D5_OFF;

	if((dato & 0x40) >> 6)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((dato & 0x80) >> 7)
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	LatchLcd();
//	LCDDelay(1);

	// Parte Baja del comando
	if(dato & 0x01)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((dato & 0x02) >> 1)
		LCD_D5_ON;
	else
		LCD_D5_OFF;

	if((dato & 0x04) >> 2)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((dato & 0x08) >> 3)
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	LatchLcd();
//	LCDDelay(2);
}

/**
 * void WString (uint8_t *ptr)
 * Escribe cadena de caracteres al LCD
 * No posiciona
 *
 * */
void WString (uint8_t *ptr)
{
	while(*ptr != 0x00)
	{
		WDato(*ptr++);
	}
}



/**
 * void Inic_LCD(void)
 * Inicializa LCD en modo de 4 bits de datos
 * No usa BF
 *
 * */
void Inic_LCD(void)
{
	Inic_PinesLCD();		// Configura pines de interfaz con LCD
	LCDDelay(400);			// Demora inicial

	LCDWaitLong(15);		// Funsion Set para 4 bits
	WComando4(MODO_8BITS);
	LCDWaitLong(15);
	WComando4(MODO_8BITS);
	LCDWaitShort(6);
	WComando4(MODO_8BITS);
	LCDWaitShort(6);
	WComando4(MODO_4BITS);		// 4 bits
	LCDWaitShort(3);
	WComando4(MODO_4BITS);		// 4 bits
	LCDWaitShort(3);
	WComando4(LIMPIA_LCD);		// Clear del LCD
	LCDWaitShort(12);
	WComando4(APAGA_LCD_CURSOR);		// Display y cursor off
	LCDWaitShort(3);
	WComando4(LINEAS_FROMATO);		// Display de dos lineas caractetes de 5x11
	LCDWaitShort(15);
	WComando8(LCD_CLEAR);	// Limpia LCd y va a Home

}


/**
	@fn  		int8_t LCD_Push( uint8_t data , uint8_t control )
	@brief 		Coloca los datos a imprimir en el LCD en el buffer circular
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param [in] data: dato a almacenar
 	@param [in] control: indica si es dato o control
	@return 0 por Exito, -1 por Error
*/
int8_t LCD_Push( uint8_t data , uint8_t control )
{
//	if ( lcdDataCount >= LCD_BUFFER_SIZE )
//		return -1;


	lcdBuffer [ lcdInxIn ] = ( data >> 4 ) & 0x0f;
	if ( control == LCD_CONTROL )
		lcdBuffer [ lcdInxIn ] |= 0x80;

	lcdInxIn ++;

	lcdBuffer [ lcdInxIn ] = data & 0x0f;
	if ( control == LCD_CONTROL )
		lcdBuffer [ lcdInxIn ] |= 0x80;
	lcdDataCount += 2;

	lcdInxIn ++;
	lcdInxIn %= LCD_BUFFER_SIZE;

	return 0;
}

/**
	@fn  		int16_t LCD_Pop( void )
	@brief 		Toma los  datos a imprimir en el LCD del buffer circular
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param 		void
	@return 	dato por Exito, -1 por Error
*/
int16_t LCD_Pop( void )
{
	uint8_t dato;

//	if ( lcdDataCount == 0 )
//		return -1;
	if ( lcdInxOut == lcdInxIn )
		return -1;

	dato = lcdBuffer [ lcdInxOut ] ;

	lcdDataCount --;

	lcdInxOut ++;
	lcdInxOut %= LCD_BUFFER_SIZE;

	return dato;
}



/**
	@fn  		void LCD_Display( const char *string , uint8_t line , uint8_t pos )
	@brief 		Muestra una srting en un LCD de 2 x 16
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param [in]	sring: direcion de comienzo de la string
 	@param [in] line: numero de renglon del Display
		<ul>
			<li> Parametros de line
			<ol>
			<li> DSP0: renglon superior
			<li> DSP1: renglon inferior
			</ol>
		</ul>
 	@param [in] pos: posicion relativa dentro del renglon
	@return void
*/
void LCD_Display( const char *string , uint8_t line , uint8_t pos )
{
	uint8_t i ;
	switch( line )
	{
		case 0:
			LCD_Push( pos + ( 0x80 | LINE_1_ADDRESS ), LCD_CONTROL );
			break;
		case 1:
			LCD_Push( pos + ( 0x80 | LINE_2_ADDRESS ), LCD_CONTROL );
			break;
	}
	for(i = 0; string[ i ] != '\0'; i++ )
		LCD_Push( string[ i ], LCD_DATA );
}


void motorLCD(void){
	int16_t data;

	if ( lcdDelay )
		lcdDelay--;

	data = LCD_Pop();

	if (data == -1 )
		return;

	if((data >> 0) & 0x01)
		LCD_D4_ON;
	else
		LCD_D4_OFF;

	if((data >> 1) & 0x01)
		LCD_D5_ON;
	else
			LCD_D5_OFF;

	if(( data >> 2) & 0x01)
		LCD_D6_ON;
	else
		LCD_D6_OFF;

	if((data >> 3) & 0x01 )
		LCD_D7_ON;
	else
		LCD_D7_OFF;

	if(data  & 0x80 )
		LCD_RS_OFF;
	else
		LCD_RS_ON;

	LCD_E_ON;
	LCD_E_ON;
	LCD_E_ON;
	LCD_E_ON;

	LCD_E_OFF;
	LCD_E_OFF;

}


