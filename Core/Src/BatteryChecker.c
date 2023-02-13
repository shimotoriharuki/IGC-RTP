/*
 * BatteryChecker.c
 *
 *  Created on: 2023/02/12
 *      Author: Haruki SHIMOTORI
 */

#include "BatteryChecker.h"

ADC_HandleTypeDef hadc2;
uint16_t adc2_value;

static bool battery_low_flag = false;

void initBatteryChecker()
{
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *) &adc2_value, 1); //ADC start
}

void batteryCheckFlip()
{
	static uint16_t cnt;

#ifdef RYUKU
	if(adc2_value <= 1875){ //2s: 1875, 3s: 2824
#elif defined(I7)
	if(adc2_value <= 3300){ //2s: 1875, 3s: 2824
#endif
		cnt++;
	}
	else cnt = 0;

	if(cnt >= 100) //100ms
		battery_low_flag = true;
	else
		battery_low_flag = false;

	if(cnt >= 5000) cnt = 5000;
}



bool isBatteryLow()
{
	return battery_low_flag;
}



