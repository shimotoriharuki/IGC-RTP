/*
 * Switch.c
 *
 *  Created on: 2023/02/12
 *      Author: Haruki SHIMOTORI
 */

#include "Switch.h"

bool getSwitchStatus(uint8_t position)
{
	bool ret = false;

	if(position == 'L' && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == 0){
		ret = true;
	}
	else if (position == 'R' && HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8) == 0){
		ret = true;
	}

	return ret;
}


