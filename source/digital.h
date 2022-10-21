/*
 * digital.h
 *
 *  Created on: 12 oct. 2022
 *      Author: sebastian
 */

#ifndef DIGITAL_H_
#define DIGITAL_H_


#include "fsl_gpio.h"

/** Enumeraciones de puertos disponibles */
typedef enum
{
	GPIO_PORT_0 = 0, /**< Puerto 0 */
	GPIO_PORT_1 /**< Puerto 1 */
}gpio_port_en;

/** Enumeraciones de puerto/pin disponibles */
typedef enum
{
	GPIO_PORTPIN_0_0 = 0, /**< Puerto 0, pin 0 */
	GPIO_PORTPIN_0_1, /**< Puerto 0, pin 1 */
	GPIO_PORTPIN_0_2, /**< Puerto 0, pin 2 */
	GPIO_PORTPIN_0_3, /**< Puerto 0, pin 3 */
	GPIO_PORTPIN_0_4, /**< Puerto 0, pin 4 */
	GPIO_PORTPIN_0_5, /**< Puerto 0, pin 5 */
	GPIO_PORTPIN_0_6, /**< Puerto 0, pin 6 */
	GPIO_PORTPIN_0_7, /**< Puerto 0, pin 7 */
	GPIO_PORTPIN_0_8, /**< Puerto 0, pin 8 */
	GPIO_PORTPIN_0_9, /**< Puerto 0, pin 9 */
	GPIO_PORTPIN_0_10, /**< Puerto 0, pin 10 */
	GPIO_PORTPIN_0_11, /**< Puerto 0, pin 11 */
	GPIO_PORTPIN_0_12, /**< Puerto 0, pin 12 */
	GPIO_PORTPIN_0_13, /**< Puerto 0, pin 13 */
	GPIO_PORTPIN_0_14, /**< Puerto 0, pin 14 */
	GPIO_PORTPIN_0_15, /**< Puerto 0, pin 15 */
	GPIO_PORTPIN_0_16, /**< Puerto 0, pin 16 */
	GPIO_PORTPIN_0_17, /**< Puerto 0, pin 17 */
	GPIO_PORTPIN_0_18, /**< Puerto 0, pin 18 */
	GPIO_PORTPIN_0_19, /**< Puerto 0, pin 19 */
	GPIO_PORTPIN_0_20, /**< Puerto 0, pin 20 */
	GPIO_PORTPIN_0_21, /**< Puerto 0, pin 21 */
	GPIO_PORTPIN_0_22, /**< Puerto 0, pin 22 */
	GPIO_PORTPIN_0_23, /**< Puerto 0, pin 23 */
	GPIO_PORTPIN_0_24, /**< Puerto 0, pin 24 */
	GPIO_PORTPIN_0_25, /**< Puerto 0, pin 25 */
	GPIO_PORTPIN_0_26, /**< Puerto 0, pin 26 */
	GPIO_PORTPIN_0_27, /**< Puerto 0, pin 27 */
	GPIO_PORTPIN_0_28, /**< Puerto 0, pin 28 */
	GPIO_PORTPIN_0_29, /**< Puerto 0, pin 29 */
	GPIO_PORTPIN_0_30, /**< Puerto 0, pin 30 */
	GPIO_PORTPIN_0_31, /**< Puerto 0, pin 31 */
	GPIO_PORTPIN_1_0, /**< Puerto 1, pin 0 */
	GPIO_PORTPIN_1_1, /**< Puerto 1, pin 1 */
	GPIO_PORTPIN_1_2, /**< Puerto 1, pin 2 */
	GPIO_PORTPIN_1_3, /**< Puerto 1, pin 3 */
	GPIO_PORTPIN_1_4, /**< Puerto 1, pin 4 */
	GPIO_PORTPIN_1_5, /**< Puerto 1, pin 5 */
	GPIO_PORTPIN_1_6, /**< Puerto 1, pin 6 */
	GPIO_PORTPIN_1_7, /**< Puerto 1, pin 7 */
	GPIO_PORTPIN_1_8, /**< Puerto 1, pin 8 */
	GPIO_PORTPIN_1_9, /**< Puerto 1, pin 9 */
	GPIO_PORTPIN_NOT_USED /**< Puerto/pin no utilizado */
}gpio_portpin_en;

/** Enumeraciones de direcciones posibles para un puerto/pin */
typedef enum
{
	GPIO_DIR_INPUT = 0, /**< Puerto/pin como entrada */
	GPIO_DIR_OUTPUT     /**< Puerto/pin como salida */
}gpio_dir_en;

typedef enum{
	GPIO_Nivel_bajo = 0,
	GPIO_Nivel_alto
}gpio_nivel_logico;


void gpioInitOutput(GPIO_Type *base,gpio_port_en port, gpio_portpin_en pin, gpio_nivel_logico nivellogico);

void gpioOutputOn(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin);

void gpioOutputOff(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin);

void gpioOutputToogle(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin);

void gpioOutputWrite(GPIO_Type *base,gpio_port_en port,gpio_portpin_en pin,gpio_nivel_logico nivellogico);

//Enciendo multiples salidas mediante una mascara
void gpioMultOutputOn(GPIO_Type *base,gpio_port_en port,uint32_t mask);


#endif /* DIGITAL_H_ */
