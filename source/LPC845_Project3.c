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
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
volatile uint32_t g_systickCounter;

    void SysTick_Handler(void)
    {
        if (g_systickCounter != 0U)
        {
            g_systickCounter--;
        }
    }

    void SysTick_DelayTicks(uint32_t n)
    {
        g_systickCounter = n;
        while (g_systickCounter != 0U)
        {
        }
    }






/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    LED_BLUE_INIT(1);


    gpioInitOutput(GPIO,GPIO_PORT_0, GPIO_PORTPIN_0_17,GPIO_Nivel_bajo);




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

    /* Force the counter to be placed into memory. */
  int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	LED_RED_TOGGLE();
        for (i=0;i<250000;i++);

        //SysTick_DelayTicks(500U);
        LED_BLUE_TOGGLE();
        for (i=0;i<250000;i++);

        for (i=0;i<250000;i++);
        GPIO_PortToggle(GPIO,0,1U << 17);
        for (i=0;i<250000;i++);
        GPIO_PortToggle(GPIO,0,1U << 16);

        gpioOutputOn(GPIO, GPIO_PORT_0,GPIO_PORTPIN_0_17);



    }
    return 0 ;
}
