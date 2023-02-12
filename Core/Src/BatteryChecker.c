/*
 * BatteryChecker.c
 *
 *  Created on: 2023/02/12
 *      Author: Haruki SHIMOTORI
 */

#include "BatteryChecker.h"

ADC_HandleTypeDef hadc2;
uint16_t adc2_value;

void initBatteryChecker()
{
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *) &adc2_value, 1); //ADC start
}

bool getBatteryVoltage()
{
	return adc2_value;
}



