
/*******************************************************************
*
* CAUTION: This file is automatically generated by HSI.
* Version: 2020.2
* DO NOT EDIT.
*
* Copyright (C) 2010-2021 Xilinx, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT 

* 
* Description: Driver configuration
*
*******************************************************************/

#include "xparameters.h"
#include "xgpio.h"

/*
* The configuration table for devices
*/

XGpio_Config XGpio_ConfigTable[XPAR_XGPIO_NUM_INSTANCES] =
{
	{
		XPAR_AXI_GPIO_BUTTONS_DEVICE_ID,
		XPAR_AXI_GPIO_BUTTONS_BASEADDR,
		XPAR_AXI_GPIO_BUTTONS_INTERRUPT_PRESENT,
		XPAR_AXI_GPIO_BUTTONS_IS_DUAL
	},
	{
		XPAR_AXI_GPIO_DISPLAYS_DEVICE_ID,
		XPAR_AXI_GPIO_DISPLAYS_BASEADDR,
		XPAR_AXI_GPIO_DISPLAYS_INTERRUPT_PRESENT,
		XPAR_AXI_GPIO_DISPLAYS_IS_DUAL
	},
	{
		XPAR_AXI_GPIO_LEDS_DEVICE_ID,
		XPAR_AXI_GPIO_LEDS_BASEADDR,
		XPAR_AXI_GPIO_LEDS_INTERRUPT_PRESENT,
		XPAR_AXI_GPIO_LEDS_IS_DUAL
	},
	{
		XPAR_AXI_GPIO_SWITCHES_DEVICE_ID,
		XPAR_AXI_GPIO_SWITCHES_BASEADDR,
		XPAR_AXI_GPIO_SWITCHES_INTERRUPT_PRESENT,
		XPAR_AXI_GPIO_SWITCHES_IS_DUAL
	}
};


