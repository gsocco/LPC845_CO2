/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * 18/08/2021
 *
 * Faltantes
 * Calibración
 * Temperatura y húmedad: Pedir en depo TH08C
 * Backlight
 *
 * */


/**
 * @file    LPC845_CO2.c
 * @brief   Application entry point.
 */
#include "main.h"


/* TODO: insert other include files here. */

volatile uint32_t delay = 0;
volatile int demoraLCD;
volatile int demoraMHZ19;
volatile uint16_t concentracionCO2 = 0;
volatile char bufferChar[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* TODO: insert other definitions and declarations here. */

void SysTick_Handler(void){
	if(delay)
		delay--;

	if(demoraLCD)
		demoraLCD--;

	if(demoraMHZ19)
		demoraMHZ19--;

	motorLCD();

}

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;


    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    SysTick_Config(30000);

    Inic_LCD();

	LCD_Display("Medidor de CO2",0,1);
	LCD_Display("400 a 5000 ppm",1,1);

	delay = 800;
	while(delay);


    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	if(!delay){
    		delay = 1000;
    		LED_VERDE_TOGGLE;
        	maquinaAPP();
    	}


    	receptorMHZ19C();

        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
