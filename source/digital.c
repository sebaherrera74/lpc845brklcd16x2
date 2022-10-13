/*
 * digital.c
 *
 *  Created on: 12 oct. 2022
 *      Author: sebastian
 */

#include "digital.h"



void gpioInitOutput(GPIO_Type *base,gpio_port_en port, gpio_portpin_en pin, gpio_nivel_logico nivellogico){
	GPIO_PortInit(GPIO,port);
    GPIO_PinInit(GPIO,port,pin,&(gpio_pin_config_t){kGPIO_DigitalOutput,nivellogico});

}
