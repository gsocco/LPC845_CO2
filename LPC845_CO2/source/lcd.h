/*
 * lcd.h
 *
 *  Created on: 24/09/2013
 *      Author: gabriel
 *
 * LCD_D4	P0.5
 * LCD_D5	P0.10
 * LCD_D6	P2.4
 * LCD_D7	P2.5
 * LCD_E	P0.4
 * LCD_RS	P2.6
 *
 **/

/*
 * lcd.h
 *
 *  Created on: 24/09/2013
 *      Author: gabriel
 *
 * LCD_D4	P0.5
 * LCD_D5	P0.10
 * LCD_D6	P2.4
 * LCD_D7	P2.5
 * LCD_E	P0.4
 * LCD_RS	P2.6
 *
 **/

#ifndef LCD_H_
#define LCD_H_




void Inic_LCD(void);			// Inicialización del LCD
void WComando8(uint8_t);
void WDato(uint8_t);
void WString (uint8_t *);
void LCDDelay(uint16_t);
void Display_lcd( char *, char, char);
void DisplayInt_lcd(uint16_t, uint8_t, uint8_t);

void motorLCD(void);
void LCD_Display(const char *string, uint8_t line ,uint8_t pos);



#define		LCD_CONTROL		1
#define		LCD_DATA		0

#define 	LCD_BUFFER_SIZE	340

#define	 	LCD_LINE_SIZE	20
#define 	LCD_LINES		2

#define 	DSP0			0
#define 	DSP1			1

#define 	LINE_1_ADDRESS	0x00
#define 	LINE_2_ADDRESS	0x40



#define		TOPE_BUFFER_LCD		100
#define 	BUFFER_VACIO		255

#define		LCD_CONTROL			1
#define		LCD_DATA			0

#define 	RENGLON_1			0
#define 	RENGLON_2			1


#define		LCD_OFF				0x08
#define		LCD_ON				0x0C		// cursor off blink off
#define		LCD_CLEAR			0x01
#define 	LCD_INC				0x1C
#define 	LCD_DEC				0x18
#define 	CURSOR_ON			0x0E
#define		BLINK_ON			0x0D
#define 	LCD_CURSORON		0x0F
#define 	LCD_CURSOROFF		0x0C
#define 	LCD_CURSORDEC		0x10
#define 	LCD_CURSORINC		0x14
#define 	CURSOR				0x7E
#define		LCD_HOME1			0x80
#define		LCD_HOME2			0xA8

#define		IDLE				0
#define		NIBLE1_CMD			1
#define		NIBLE2_CMD			2
#define		LATCH_CMD			3
#define		NIBLE1_POS			4
#define		NIBLE2_POS			5
#define		LATCH_POS			6

#define		NIBLE1_DATO			7
#define		NIBLE2_DATO			8
#define		LATCH_DATO			9
#define		GET_TEXTO			10
#define		GET_CMD				11
#define		GET_POS				12

#define		MODO_8BITS			0x30
#define		MODO_4BITS			0x20
#define		LIMPIA_LCD			0x80
#define		APAGA_LCD_CURSOR	0x00
#define		LINEAS_FROMATO		0xC0

#define		LCD_Clear()		LCD_Push( 0x01 , LCD_CONTROL )



#endif /* LCD_H_ */
