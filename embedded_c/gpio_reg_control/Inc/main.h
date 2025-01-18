/*
 * main.h
 *
 *  Created on: Jan 18, 2025
 *      Author: serkan
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "main_types.h"

void delay_ms(unsigned int ms);
uint32_t calculatePortAddresses(Port port);

void initPort(Port port);
void pinMode(Port port, uint8_t pin_number, PinMode mode);
void writePin(Port port, uint8_t pin_number, PinState state);
uint8_t readPin(Port port, uint8_t pin_number);

#endif /* MAIN_H_ */
