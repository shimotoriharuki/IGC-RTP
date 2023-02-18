/*
 * LineChase.c
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#include "LineChase.h"
#define DELTA_T 0.001
#define SENSOR_ALL_DARK 50

static int16_t speed_l, speed_r;
static uint8_t line_trace_enable_flag;
static uint8_t i_clear_flag;
static float line_following_term;
static bool dark_flag;

float mon_velo_term;

void calculateLineFollowingTermFlip(void){
	float p, d;
	static double i;
#ifdef RYUKU
	float kp = 0.85, ki = 0.00, kd = 0.025;
#elif defined(I7)
	//float kp = 0.6, ki = 0.00, kd = 0.006;
	float kp = 0.6, ki = 0.00, kd = 0.0065;
	//float kp = 0.65, ki = 0.00, kd = 0.0070;
#endif
	float diff = 0.;
	static double pre_diff = 0.;
	//int16_t motor_L, motor_R;

	if(line_trace_enable_flag == 1){
		if(i_clear_flag == 1){
			i = 0;
			i_clear_flag = 0;
		}

		diff = ( ( sensor[0] * 3.2 + sensor[1] * 2.8 + sensor[2] * 2.4 + sensor[3] * 2.0 + sensor[4] * 1.6 + sensor[5] * 1.2 ) / 6 ) - ( ( sensor[6] * 1.2 + sensor[7] * 1.6 + sensor[8] * 2.0 + sensor[9] * 2.4 + sensor[10] * 2.8 + sensor[11] * 3.2 ) / 6 );

		p = kp * diff; //P制御
		i += ki * diff * DELTA_T; //I制御
		d = kd * (diff - pre_diff) / DELTA_T; //D制御

		line_following_term = p + i + d;

		pre_diff = diff;
	}
}

void lineTraceFlip(void)
{
	if(line_trace_enable_flag == 1){
		float limit = MAX_COUNTER_PERIOD * 0.9;
		float velocity_control_term = getVelocityControlTerm();

		if(velocity_control_term >= limit) velocity_control_term = limit;
		else if(velocity_control_term <= -limit) velocity_control_term = -limit;

		float exceeded = 0;
		if(velocity_control_term + line_following_term >= MAX_COUNTER_PERIOD){
			exceeded = (velocity_control_term + line_following_term) - MAX_COUNTER_PERIOD;
		}
		else if(velocity_control_term - line_following_term <= -MAX_COUNTER_PERIOD){
			exceeded = -MAX_COUNTER_PERIOD - (velocity_control_term - line_following_term) ;
		}

		velocity_control_term -= exceeded;
		line_following_term += exceeded;

		float motor_l = velocity_control_term + line_following_term;
		float motor_r = velocity_control_term - line_following_term;

		/*
		float motor_l = velocity_control_term ;
		float motor_r = velocity_control_term ;
		*/

		mon_velo_term = velocity_control_term;
		setMotor(motor_l, motor_r);
	}
	else{
		setMotor(0, 0);
	}
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

void checkCourseOut(void){
	uint16_t all_sensor;
	static uint16_t dark_cnt;

	all_sensor = (sensor[0] + sensor[1] + sensor[2] + sensor[3] + sensor[4] + sensor[5] + sensor[6] + sensor[7] + sensor[8] + sensor[9] + sensor[10] + sensor[11]) / 12;
	if(all_sensor > 2400){
		dark_cnt++;
	}
	else dark_cnt = 0;

	if(dark_cnt >= SENSOR_ALL_DARK) dark_flag = true;
	else dark_flag = false;

}

bool getCouseOutFlag()
{
	return dark_flag;
}
