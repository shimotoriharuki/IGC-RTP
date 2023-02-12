/*
 * LineChase.c
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#include "LineChase.h"
#define DELTA_T 0.001

static int16_t speed_l, speed_r;
static uint8_t line_trace_enable_flag;
static uint8_t i_clear_flag;
static float line_following_term;

float mon_velo_term;

void calculateLineFollowingTermFlip(void){
	float p, d;
	static double i;
#ifdef RYUKU
	float kp = 0.85, ki = 0.00, kd = 0.009;
#elif defined(I7)
	float kp = 0.6, ki = 0.00, kd = 0.01;
#endif
	float diff = 0.;
	static double pre_diff = 0.;
	//int16_t motor_L, motor_R;

	if(line_trace_enable_flag == 1){
		if(i_clear_flag == 1){
			i = 0;
			i_clear_flag = 0;
		}

		diff = ( ( sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4] + sensor[5] ) / 6 ) - ( ( sensor[6] + sensor[7] + sensor[8] + sensor[9] + sensor[10] + sensor[11] ) / 6 );

		p = kp * diff; //P制御
		i += ki * diff * DELTA_T; //I制御
		d = kd * (diff - pre_diff) / DELTA_T; //D制御

		line_following_term = p + i + d;

		pre_diff = diff;
	}
}

void lineTraceFlip(void)
{
	float velocity_control_term = getVelocityControlTerm();
	float motor_l = velocity_control_term + line_following_term;
	float motor_r = velocity_control_term - line_following_term;

	mon_velo_term = velocity_control_term;
	setMotor(motor_l, motor_r);
}

float getLineFollowingTerm()
{
	return line_following_term;
}

void setSpeed(int16_t l, int16_t r)
{
	speed_l = l;
	speed_r = r;
}

void startLineTrace()
{
	line_trace_enable_flag = 1;
	i_clear_flag = 1;
}

void stopLineTrace()
{
	line_trace_enable_flag = 0;
	setMotor(0, 0);
}

