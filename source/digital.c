/*
 * digital.c
 *
 *  Created on: 12 oct. 2022
 *      Author: sebastian
 */

#include "digital.h"



void gpioInitOutput(GPIO_Type *base,gpio_port_en port, gpio_portpin_en pin, gpio_nivel_logico nivellogico){
	//GPIO_PortInit(GPIO,port);
    GPIO_PinInit(base,port,pin,&(gpio_pin_config_t){kGPIO_DigitalOutput,nivellogico});
}

void gpioOutputOn(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin){
	GPIO_PortSet(base,port,1U << pin);
}

void gpioOutputOff(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin){
	 GPIO_PortClear(base,port,1U << pin);
}

void gpioOutputToogle(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin){
	GPIO_PortToggle(base,port,1U << pin);
}

void gpioOutputWrite(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin,gpio_nivel_logico nivellogico){
	GPIO_PinWrite(base, port, pin, nivellogico);

}


