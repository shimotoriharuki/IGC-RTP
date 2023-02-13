/*
 * SideSensor.c
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef SRC_SIDESENSOR_C_
#define SRC_SIDESENSOR_C_

#include "SideSensor.h"

static bool side_sensor_l, side_sensor_r;
//static uint8_t ignore_flag;
static uint16_t timer_l, timer_r;
static bool rise_fall_flag_l = true, rise_fall_flag_r = true;

void updateStatusLeftExti()
{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_SET){ // 立ち上がり Black
		timer_l = 0;
		rise_fall_flag_l = true;
	}
	else{	//White
		timer_l = 0;
		rise_fall_flag_l = false;
	}
}

void updateStatusRightExti()
{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET){ // 立ち上がり Black
		timer_r = 0;
		rise_fall_flag_r = true;
	}
	else{	//White
		timer_r = 0;
		rise_fall_flag_r = false;
	}
}

void updateSideSensorStatus()
{
	timer_l++;
	timer_r++;
	if(timer_l >= 10000) timer_l = 10000;
	if(timer_r >= 10000) timer_r = 10000;

	if(rise_fall_flag_l == true && timer_l >= 2){
		side_sensor_l = false;
	}
	else if(rise_fall_flag_l == false && timer_l >= 2){
		side_sensor_l = true;
	}

	if(rise_fall_flag_r == true && timer_r >= 2){
		side_sensor_r = false;
	}
	else if(rise_fall_flag_r == false && timer_r >= 2){
		side_sensor_r = true;
	}
	/*
	//if(ignore_flag == 0){
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
	//}
	 */

	/*
	else{
		cnt_L = 0;
		cnt_R = 0;
	}
	*/

}

bool getSideSensorStatusL()
{
	return side_sensor_l;
}

bool getSideSensorStatusR()
{
	return side_sensor_r;
}

/*
void enableSideSensorIgnore(void)
{
	ignore_flag = 1;
}

void disableSideSensorIgnore(void)
{
	ignore_flag = 0;
}

uint8_t getSideSensorIgnoreFlag(void)
{
	return ignore_flag;
}
*/

#endif /* SRC_SIDESENSOR_C_ */
