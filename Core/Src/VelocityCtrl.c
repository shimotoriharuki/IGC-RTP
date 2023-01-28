/*
 * VelocityCtrl.c
 *
 *  Created on: 2023/01/28
 *      Author: Haruki SHIMOTORI
 */

#include "VelocityCtrl.h"

#define WHEEL_RADIUS 11 //[mm]
#define PI 3.1415926535
#define ENCODER_RESOLUTION 4096
#define REDUCTION_RATIO 0.35 //Gear reduction ratio 0.35
#define VELOCITY_PER_CNT (2 * PI * WHEEL_RADIUS * REDUCTION_RATIO / ENCODER_RESOLUTION) //[m/s per cnt]
#define DELTA_T 0.001

static uint8_t velocity_control_enable_flag;
static uint8_t i_clear_flag;

static float velocity_control_term;
static float target_velocity;

float mon_current_velocity;

void calculateVelocityControlFlip(void)
{
	float p, d;
	static float i;
#ifdef RYUKU
	float kp = 3000, ki = 30000, kd = 0.;
#elif defined(I7)
	float kp = 3000, ki = 30000, kd = 0.;
#endif
	float diff = 0.;
	static double pre_diff = 0.;
	float current_velocity = getCurrentVelocity();

	if(velocity_control_enable_flag == 1){
		if(i_clear_flag == 1){
			i = 0;
			i_clear_flag = 0;
		}

		diff = target_velocity - current_velocity;
		p = kp * diff; //P制御
		i += ki * diff * DELTA_T; //I制御
		d = kd * (diff - pre_diff) / DELTA_T; //D制御

		velocity_control_term = p + i + d;

		pre_diff = diff;

	}

}

float getVelocityControlTerm(void)
{
	return velocity_control_term;
}

void setTargetVelocity(float velocity)
{
	target_velocity = velocity;
}

float getCurrentVelocity(void)
{
	int16_t enc_l, enc_r;
	getEncoderCnt(&enc_l, &enc_r);
	float enc_cnt = (enc_l + enc_r) / 2;

	float current_velocity = VELOCITY_PER_CNT * enc_cnt;
	mon_current_velocity = current_velocity;

	return current_velocity;
}

void startVelocityControl(void)
{
	velocity_control_enable_flag = 1;
	i_clear_flag = 1;
}

void stopVelocityControl(void)
{
	velocity_control_enable_flag = 0;
}
