/*
 * main.h
 *
 *  Created on: Nov 12, 2024
 *      Author: serkan
 */

#ifndef MAIN_H_
#define MAIN_H_

// Address of the  clock control register (AHB1ENR)
// RCC Address (0x40023800) + RCC_AHB1ENR Offset (0x30)
#define RCC_REG (0x40023800)
#define AHB1ENR_OFFSET (0x30)
#define RCC_AHB1ENR_REG (RCC_REG + AHB1ENR_OFFSET)

#define PORTA_REG (0x40020000)
#define PORTB_REG (0x40020400)
#define PORTC_REG (0x40020800)
#define PORTD_REG (0x40020C00)
#define PORTE_REG (0x40021000)
#define PORTH_REG (0x40021C00)

#define PORT_INPUT_OFFSET (0x10)
#define PORT_OUTPUT_OFFSET (0x14)

#define GREEN_LD
#define ORANGE_LD
#define RED_LD
#define BLUE_LD

#endif /* MAIN_H_ */
