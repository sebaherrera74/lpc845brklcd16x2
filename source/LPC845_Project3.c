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


	if (SysTick_Config(SystemCoreClock / 1000U))
	{
		while (1)
		{
		}
	}

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	PRINTF("Hello World\n");

	while(1) {


		//LED_BLUE_TOGGLE();
		gpioOutputWrite(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_17,GPIO_Nivel_alto);
		 delayMs(1000);
		 gpioOutputToogle(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_16);


		 gpioOutputWrite(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_17,GPIO_Nivel_bajo);
		 delayMs(1000);

	}
	return 0 ;
}

/* Force the counter to be placed into memory. */
	//int i = 0 ;
	/* Enter an infinite loop, just incrementing a counter. */

	/*//for (i=0;i<250000;i++);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00380000);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x003800000);

	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x000700000);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x00070000);

	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x04480000);
	GPIO_PortClear(GPIO, GPIO_PORT_0,0x04000000);


	//GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);


	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00300000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);


	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00300000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);

	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x003C0000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<25;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<25;i++);

	//GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00080000);
	//GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<2500;i++);
	//GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<2500;i++);


	//GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00010000);
	//GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<2500;i++);
	//GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<2500;i++);




	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00070000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);

	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x000F0000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);

	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x00020000);
	GPIO_PortSet(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
	GPIO_PortClear(GPIO, GPIO_PORT_0, 0x10000000);
	//for (i=0;i<250;i++);
*/

	 //unsigned char LineOfCharacters[]={'H','O','l','a'};

	 //InitLCD_8b_2L();

	 //WriteInitial(LineOfCharacters);



