/*
 * LineChase.c
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku
 */

#include "LineChase.h"
#include "stm32f4xx_hal.h"
#define DELTA_T 0.001

int16_t motor_L, motor_R;

double mon_def, mon_pid;
int16_t mon_cnt_L, mon_cnt_R;
int16_t mon_rev_L, mon_rev_R, mon_cnt;

int16_t sensor[LINESENSOR_ADC_NUM];

uint8_t side_sensor_L, side_sensor_R;
int16_t speed_L, speed_R;


void lineTrace(void){
	double p, d;
	static double i;
	double kp = 0.6, ki = 0.00, kd = 0.;
	double diff = 0.;
	static double pre_diff = 0.;

	/*if(i_pos_clear_flag == 1){
		i_pos = 0;
		i_pos_clear_flag = 0;
	}*/

	diff = ( ( sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4] + sensor[5] ) / 6 ) - ( ( sensor[6] + sensor[7] + sensor[8] + sensor[9] + sensor[10] + sensor[11] ) / 6 );

	p = kp * diff; //P制御
	i += ki * diff * DELTA_T; //I制御
	d = kd * (diff - pre_diff) / DELTA_T; //D制御

	motor_L = speed_L + (int)( p + i + d );
	motor_R = speed_R - ( p + i + d );

	motorSet(motor_L, motor_R);

	pre_diff = diff;

	mon_pid = p + i + d;

}

void updateSideSensorState()
{
	static uint16_t cnt_L, cnt_R;

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0) cnt_L++;
	else cnt_L = 0;

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0) cnt_R++;
	else cnt_R = 0;

	if(cnt_L >= 5){
		side_sensor_L = 1;
	}
	else{
		side_sensor_L = 0;
	}

	if(cnt_R >= 5){
		side_sensor_R = 1;
	}
	else{
		side_sensor_R = 0;
	}

	mon_cnt_L = cnt_L;
	mon_cnt_R = cnt_R;

}
