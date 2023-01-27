/*
 * SideSensor.c
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef SRC_SIDESENSOR_C_
#define SRC_SIDESENSOR_C_

#include "SideSensor.h"

static uint8_t side_sensor_l, side_sensor_r;

void updateSideSensorStatus()
{
	static uint16_t cnt_L, cnt_R;

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0) cnt_L++;
	else cnt_L = 0;

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0) cnt_R++;
	else cnt_R = 0;

	if(cnt_L >= 5){
		side_sensor_l = 1;
	}
	else{
		side_sensor_l = 0;
	}

	if(cnt_R >= 5){
		side_sensor_r = 1;
	}
	else{
		side_sensor_r = 0;
	}

}

uint8_t getSideSensorStatusL()
{
	return side_sensor_l;
}

uint8_t getSideSensorStatusR()
{
	return side_sensor_r;
}

#endif /* SRC_SIDESENSOR_C_ */
