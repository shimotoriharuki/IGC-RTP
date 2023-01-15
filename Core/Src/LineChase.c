/*
 * LineChase.c
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku
 */

#include "LineChase.h"
#include "stm32f4xx_hal.h"
#define DELTA_T 0.001

TIM_HandleTypeDef htim8;

int16_t motor_L, motor_R;
int16_t sensorCL, sensorCR, sensorL, sensorR, sensorLL, sensorRR;
double mon_def, mon_pid;
int16_t mon_rev_L, mon_rev_R;

static int16_t senCL[10];
static int16_t senCR[10];
static int16_t senL[10];
static int16_t senR[10];
static int16_t senLL[10];
static int16_t senRR[10];

uint8_t wakeup_flag;

void motorSet() {
	int16_t motorPwm_L, motorPwm_R;
	int16_t rev_motor_L, rev_motor_R;

	if(motor_L > MAX_COUNTER_PERIOD) motor_L = MAX_COUNTER_PERIOD;
	if(motor_R > MAX_COUNTER_PERIOD) motor_R = MAX_COUNTER_PERIOD;
	if(motor_L < MIN_COUNTER_PERIOD) motor_L = MIN_COUNTER_PERIOD;
	if(motor_R < MIN_COUNTER_PERIOD) motor_R = MIN_COUNTER_PERIOD;

	if(motor_L >= 0){
		rev_motor_L = MAX_COUNTER_PERIOD - motor_L;
	}
	else{
		rev_motor_L = MIN_COUNTER_PERIOD - motor_L;
	}
	if(motor_R >= 0){
		rev_motor_R = MAX_COUNTER_PERIOD - motor_R;
		}
	else{
		rev_motor_R = MIN_COUNTER_PERIOD - motor_R;
	}
	mon_rev_L = rev_motor_L;
	mon_rev_R = rev_motor_R;

	/*
	if(wakeup_flage == 1){
		wakeup_flage = 0;

		//motor driver wakeup
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);
		HAL_Delay(100);
	}
	*/

	if(rev_motor_L > 0) {
		motorPwm_L = rev_motor_L;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, motorPwm_L);

	}
	else if(rev_motor_L == 0){
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);
	}
	else {
		motorPwm_L = rev_motor_L*(-1) ;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, motorPwm_L);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);
	}


	if(rev_motor_R > 0) {
		motorPwm_R = rev_motor_R;
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, motorPwm_R);
	}
	else if(rev_motor_R == 0){
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
	}
	else {
		motorPwm_R = rev_motor_R * (-1);
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, motorPwm_R);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
	}

}

void storeAdBuffer(void) {
	static uint8_t index;
	senCL[index] = analog[5];
	senCR[index] = analog[6];
	senL[index] = analog[4];
	senR[index] = analog[7];
	senLL[index] = analog[3];
	senRR[index] = analog[10];

	index++;
	if(index == 10) index = 0;
}

void getAnalogsensor(void) {
	sensorCL = ( senCL[0] + senCL[1] + senCL[2] + senCL[3] + senCL[4] + senCL[5] + senCL[6] + senCL[7] + senCL[8] + senCL[9] ) / 10;
	sensorCR = ( senCR[0] + senCR[1] + senCR[2] + senCR[3] + senCR[4] + senCR[5] + senCR[6] + senCR[7] + senCR[8] + senCR[9] ) / 10;
	sensorL = ( senL[0] + senL[1] + senL[2] + senL[3] + senL[4] + senL[5] + senL[6] + senL[7] + senL[8] + senL[9] ) / 10;
	sensorR = ( senR[0] + senR[1] + senR[2] + senR[3] + senR[4] + senR[5] + senR[6] + senR[7] + senR[8] + senR[9] ) / 10;
	sensorLL = ( senLL[0] + senLL[1] + senLL[2] + senLL[3] + senLL[4] + senLL[5] + senLL[6] + senLL[7] + senLL[8] + senCR[9] ) / 10;
	sensorRR = ( senRR[0] + senRR[1] + senRR[2] + senRR[3] + senRR[4] + senRR[5] + senRR[6] + senRR[7] + senRR[8] + senRR[9] ) / 10;


}

void lineTrace(void){
	double p, d;
	static double i;
	double kp = 0.4, ki = 0., kd = 0.;
	double def = 0.;
	static double pre_def = 0.;

	/*if(i_pos_clear_flag == 1){
		i_pos = 0;
		i_pos_clear_flag = 0;
	}*/

	def = ( sensorLL + sensorL + sensorCL ) - ( sensorRR + sensorR + sensorCR );

	p = kp * def; //P制御
	i += ki * def * DELTA_T; //I制御
	d = kd * (def - pre_def) / DELTA_T; //D制御

	motor_L = ( p + i + d );
	motor_R = -( p + i + d );

	pre_def = def;

	mon_def = def;
	mon_pid = p + i + d;

}
