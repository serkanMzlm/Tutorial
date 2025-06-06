/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
 * Debug yapmak için syscalls.c dosyasına ITM_SendChar fonksiyonu oluşturulur _write fonksiyonu
 * içine ITM_SendChar fonksiyonu konulur. serial ekranda görüntülemek için  "SWV ITM Data Console"
 * açılır. Configure Trace kısmında port seçilir ve Start Trace kısmına açılır.
 *
 * Volatile kullanmanın nedeni derleyicinin değişkeni yorumlamasını engellemektir.
 */

int main(void)
{
	printf("Started Programing...\n");
	initPort(A);
	initPort(D);

	pinMode(A, USER_BUTTON, INPUT);

	pinMode(D, GREEN_LED, OUTPUT);
	pinMode(D, RED_LED, OUTPUT);
	pinMode(D, ORANGE_LED, OUTPUT);
	pinMode(D, BLUE_LED, OUTPUT);

	uint8_t counter = 0;
	uint8_t prev_counter = 3;
	uint8_t prev_button_state = 0;

	for(;;)
	{
		uint8_t button_state = readPin(A, 0);
		if(button_state && !prev_button_state)
		{
			prev_counter = counter;
			if(++counter >= 4)
			{
				counter = 0;
				printf("Counter Reset \n");
			}
			printf("Counter: %d, Prev Counter: %d\n", counter, prev_counter);
		}

		writePin(D, (12 + prev_counter), LOW);
		writePin(D, (12 + counter), HIGH);
		delay_ms(10);
		prev_button_state = button_state;
	}

 de
}

void delay_ms(unsigned int ms)
{
	for (volatile int i = 0; i < ms * 1000; i++);
}

uint32_t calculatePortAddresses(Port port)
{
	uint32_t volatile port_addres = 0;
	if((int)port <= 4)
	{
		port_addres = PORTA_REG + (int)port * PORT_OFFSET;
	}
	else
	{
		port_addres = PORTH_REG;
	}
	return port_addres;
}

void initPort(Port port)
{
	uint32_t volatile *clk_ctrl_reg_ptr = (uint32_t*)RCC_AHB1ENR_REG;
	*clk_ctrl_reg_ptr |= (1 << (int)port); // AHB1ENR'de clock GPIOx birimini etkinleştirir
}

void pinMode(Port port, uint8_t pin_number, PinMode mode)
{
	int volatile pin_index = pin_number * 2;
	uint32_t volatile *port_mode_reg_ptr = (uint32_t*)(calculatePortAddresses(port));

	// x ve x+1 yeri bitlerini 0 yapılır
	*port_mode_reg_ptr &= ~(3 << pin_index);
	switch(mode)
	{
	case OUTPUT:
		*port_mode_reg_ptr |= (1 << pin_index);
		break;
	case INPUT:
		break;
	}
}

void writePin(Port port, uint8_t pin_number, PinState state)
{
	uint32_t volatile *port_mode_out_reg_ptr = (uint32_t*)(calculatePortAddresses(port) + PORT_OUTPUT_OFFSET);
	if(state == HIGH) {
		*port_mode_out_reg_ptr |= (1 << pin_number);
	} else {
		*port_mode_out_reg_ptr &= ~(1 << pin_number);
	}
}

uint8_t readPin(Port port, uint8_t pin_number)
{
	uint32_t volatile *port_mode_in_reg_ptr = (uint32_t*)(calculatePortAddresses(port) + PORT_INPUT_OFFSET);
	return ((uint8_t) (*port_mode_in_reg_ptr & 0x1));
}
