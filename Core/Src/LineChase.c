/*
 * LineChase.c
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#include "LineChase.h"
#include "stm32f4xx_hal.h"
#define DELTA_T 0.001

static int16_t speed_l, speed_r;
static uint8_t line_trace_flag;

void lineTraceFlip(void){
	double p, d;
	static double i;
	double kp = 0.6, ki = 0.00, kd = 0.;
	double diff = 0.;
	static double pre_diff = 0.;
	int16_t motor_L, motor_R;

	if(line_trace_flag == 1){
		/*if(i_pos_clear_flag == 1){
			i_pos = 0;
			i_pos_clear_flag = 0;
		}*/

		diff = ( ( sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4] + sensor[5] ) / 6 ) - ( ( sensor[6] + sensor[7] + sensor[8] + sensor[9] + sensor[10] + sensor[11] ) / 6 );

		p = kp * diff; //P制御
		i += ki * diff * DELTA_T; //I制御
		d = kd * (diff - pre_diff) / DELTA_T; //D制御

		motor_L = speed_l + (int)( p + i + d );
		motor_R = speed_r - (int)( p + i + d );

		setMotor(motor_L, motor_R);

		pre_diff = diff;
	}
}

void setSpeed(int16_t l, int16_t r)
{
	speed_l = l;
	speed_r = r;
}

void lineTraceStart()
{
	line_trace_flag = 1;
}

void lineTraceStop()
{
	line_trace_flag = 0;
	setMotor(0, 0);
}

