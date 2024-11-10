/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// Address of the  clock control register (AHB1ENR) 0x40023800 + 0x30
// Address of the GPIOD mode register (used to control mode) 0x40020C00 + 0x00
// Address of the GPIOD output data register (used to write)  0x40020C00 + 0x14

int main(void)
{
	/* Loop forever */
	uint32_t volatile *clk_ctrl_reg_ptr = (uint32_t*)0x40023830;
	uint32_t volatile *port_d_mode_reg_ptr = (uint32_t*)0x40020C00;
	uint32_t volatile *port_d_mode_out_reg_ptr = (uint32_t*)0x40020C14;

	uint32_t volatile *port_a_mode_reg_ptr = (uint32_t*)0x40020000;
	uint32_t volatile *port_a_mode_in_reg_ptr = (uint32_t*)0x40020010;

	// GPIO Output
	// 1. enable the clock for GPIOD peripheral in the AHB1ENR
	*clk_ctrl_reg_ptr |= (1 << 3);         // 0x08

	// 2. configure the mode of the IO pin as output
	*port_d_mode_reg_ptr &= ~(3 << 26);    // 0xF3FFFFFF (a. clear the 26th and 27th bit positions (clear))
	*port_d_mode_reg_ptr |= (1 << 26);     // 0x04000000 (b. make 26th bit position as 1 (set))

	// 3. set 13th bit of the output data register to make I/O pin-12 as HIGH
	*port_d_mode_out_reg_ptr |= (1 << 13); // 0x2000 (ON) and &= ~(1 << 13) (OFF)

	// GPIO Input Pin
	// 1. enable the clock for GPIOA peripheral in the AHB1ENR
	*clk_ctrl_reg_ptr |= (1 << 0);

	// 2. configure the mode of the IO pin as output
	*port_a_mode_reg_ptr &= ~(3 << 0);   // clear and set


	uint8_t led_status = 0;      // LED initially OFF
	uint8_t prev_button_state = 0;  // Previous button state

	for(;;)
	{
		uint8_t button_state = (uint8_t)(*port_a_mode_in_reg_ptr & 0x1);

		if(button_state && !prev_button_state)
		{
			led_status = !led_status;

			if(led_status)
			{
				*port_d_mode_out_reg_ptr |= (1 << 13);
			}
			else
			{
				*port_d_mode_out_reg_ptr &= ~(1 << 13);
			}
		}

		prev_button_state = button_state;

		for (volatile int i = 0; i < 100000; i++);
	}
}








