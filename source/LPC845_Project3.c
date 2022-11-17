/*
 * Copyright 2016-2022 NXP
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

/**
 * @file    LPC845_Project3.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "digital.h"
#include "lcd16x2.h"
#include "delay.h"



const char tempChar[8] = {
		0b00001110,
		0b00001010,
		0b00001010,
		0b00001110,
		0b00001110,
		0b00010111,
		0b00011111,
		0b00001110
};

#define P0     0x0
#define P1     0x2
#define P2     0x40
#define P3     0x8000
#define P4     0x4000

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	LED_BLUE_INIT(1);
	GPIO_PortInit(GPIO,GPIO_PORT_0);
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_16,GPIO_Nivel_bajo ); //D0
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_17,GPIO_Nivel_bajo); //D1
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_18,GPIO_Nivel_bajo); //D2
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_19,GPIO_Nivel_bajo); //D3
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_20,GPIO_Nivel_bajo); //D4
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_21,GPIO_Nivel_bajo); //D5
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_22,GPIO_Nivel_bajo); //D6
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_23,GPIO_Nivel_bajo); //D7

	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_26,GPIO_Nivel_bajo); //RS
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_27,GPIO_Nivel_bajo); //RW
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_28,GPIO_Nivel_bajo); //E



	//gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_0,GPIO_Nivel_bajo);
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_1,GPIO_Nivel_bajo);
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_6,GPIO_Nivel_bajo);
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_14,GPIO_Nivel_bajo);
	gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_15,GPIO_Nivel_bajo);


	if (SysTick_Config(SystemCoreClock/1000U))
	{
		while (1)
		{
		}
	}

	lcd16x2CreateChar( 0, tempChar );

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	PRINTF("Hello World\n");

	//lcd16x2Init(16,2,5,8);

	lcd16x2Init4b(16,2,5,8);

	//lcd16x2SendStringRaw( "Tmp" );
	//lcd16x2Data(0);

	char string[5]={'H','o','l','a',125};
	//lcd16x2SendStringRaw("Hola mundo todo bien");
	//lcd16X2Clear();
	/*for (int i=34;i<191;i++){
		 lcd16x2Data(i);
		 delayMs(500);
		 //lcd16X2Clear();
	 }*/



	//lcd16X2Clear();

	//lcd16x2SendStringRaw(string);
	//lcd16X2Clear();
	//lcd16x2SendString( "Hola mundo todo bien" );
	//lcd16X2Clear();
	//DisplayLeft(20);




	while(1) {
		delayMs(1000);


		gpioOutputOff(GPIO,GPIO_PORT_0,GPIO_PORTPIN_0_1);
		gpioOutputOff(GPIO,GPIO_PORT_0,GPIO_PORTPIN_0_6);
		gpioOutputOff(GPIO,GPIO_PORT_0,GPIO_PORTPIN_0_14);
		gpioOutputOff(GPIO,GPIO_PORT_0,GPIO_PORTPIN_0_15);
		lcd16X2Clear();
		LED_BLUE_TOGGLE();
		lcd16X2Clear();
		lcd16x2SendString( "Hola mundo todo bien" );
		gpioMultOutputOn(GPIO,GPIO_PORT_0,P1|P2|P3|P4);
		//gpioMultOutputOn(GPIO,GPIO_PORT_0,P2);
		//gpioMultOutputOn(GPIO,GPIO_PORT_0,P3);
		//gpioMultOutputOn(GPIO,GPIO_PORT_0,P4);


	}
	return 0 ;
}



