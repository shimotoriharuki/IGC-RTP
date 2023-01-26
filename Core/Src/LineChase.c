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
int16_t sensor0, sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8, sensor9, sensor10, sensor11;

double mon_def, mon_pid;
int16_t mon_cnt_L, mon_cnt_R;
int16_t mon_rev_L, mon_rev_R, mon_cnt;

static int16_t sen0[10];
static int16_t sen1[10];
static int16_t sen2[10];
static int16_t sen3[10];
static int16_t sen4[10];
static int16_t sen5[10];
static int16_t sen6[10];
static int16_t sen7[10];
static int16_t sen8[10];
static int16_t sen9[10];
static int16_t sen10[10];
static int16_t sen11[10];

uint8_t side_sensor_L, side_sensor_R;
int16_t speed_L, speed_R;

void motorSet() {
	int16_t motorPwm_L, motorPwm_R;
	int16_t rev_motor_L, rev_motor_R;

	if(motor_L >= MAX_COUNTER_PERIOD) motor_L = MAX_COUNTER_PERIOD;
	else if(motor_L <= MIN_COUNTER_PERIOD) motor_L = MIN_COUNTER_PERIOD;

	if(motor_R >= MAX_COUNTER_PERIOD) motor_R = MAX_COUNTER_PERIOD;
	else if(motor_R <= MIN_COUNTER_PERIOD) motor_R = MIN_COUNTER_PERIOD;

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


	if(rev_motor_L > 0) {
		motorPwm_L = rev_motor_L;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, motorPwm_L);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);

	}
	else {
		motorPwm_L = rev_motor_L*(-1) ;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, motorPwm_L);
	}


	if(rev_motor_R > 0) {
		motorPwm_R = rev_motor_R;
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, motorPwm_R);
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
	sen0[index] = analog[0];
	sen1[index] = analog[1];
	sen2[index] = analog[2];
	sen3[index] = analog[3];
	sen4[index] = analog[4];
	sen5[index] = analog[5];
	sen6[index] = analog[6];
	sen7[index] = analog[10];
	sen8[index] = analog[7];
	sen9[index] = analog[8];
	sen10[index] = analog[9];
	sen11[index] = analog[11];

	index++;
	if(index == 10) index = 0;
}

void getAnalogsensor(void) {
	sensor0 = ( sen0[0] + sen0[1] + sen0[2] + sen0[3] + sen0[4] + sen0[5] + sen0[6] + sen0[7] + sen0[8] + sen0[9] ) / 10;
	sensor1 = ( sen1[0] + sen1[1] + sen1[2] + sen1[3] + sen1[4] + sen1[5] + sen1[6] + sen1[7] + sen1[8] + sen1[9] ) / 10;
	sensor2 = ( sen2[0] + sen2[1] + sen2[2] + sen2[3] + sen2[4] + sen2[5] + sen2[6] + sen2[7] + sen2[8] + sen2[9] ) / 10;
	sensor3 = ( sen3[0] + sen3[1] + sen3[2] + sen3[3] + sen3[4] + sen3[5] + sen3[6] + sen3[7] + sen3[8] + sen3[9] ) / 10;
	sensor4 = ( sen4[0] + sen4[1] + sen4[2] + sen4[3] + sen4[4] + sen4[5] + sen4[6] + sen4[7] + sen4[8] + sen4[9] ) / 10;
	sensor5 = ( sen5[0] + sen5[1] + sen5[2] + sen5[3] + sen5[4] + sen5[5] + sen5[6] + sen5[7] + sen5[8] + sen5[9] ) / 10;
	sensor6 = ( sen6[0] + sen6[1] + sen6[2] + sen6[3] + sen6[4] + sen6[5] + sen6[6] + sen6[7] + sen6[8] + sen6[9] ) / 10;
	sensor7 = ( sen7[0] + sen7[1] + sen7[2] + sen7[3] + sen7[4] + sen7[5] + sen7[6] + sen7[7] + sen7[8] + sen7[9] ) / 10;
	sensor8 = ( sen8[0] + sen8[1] + sen8[2] + sen8[3] + sen8[4] + sen8[5] + sen8[6] + sen8[7] + sen8[8] + sen8[9] ) / 10;
	sensor9 = ( sen9[0] + sen9[1] + sen9[2] + sen9[3] + sen9[4] + sen9[5] + sen9[6] + sen9[7] + sen9[8] + sen9[9] ) / 10;
	sensor10 = ( sen10[0] + sen10[1] + sen10[2] + sen10[3] + sen10[4] + sen10[5] + sen10[6] + sen10[7] + sen10[8] + sen10[9] ) / 10;
	sensor11 = ( sen11[0] + sen11[1] + sen11[2] + sen11[3] + sen11[4] + sen11[5] + sen11[6] + sen11[7] + sen11[8] + sen11[9] ) / 10;


}

void lineTrace(void){
	double p, d;
	static double i;
	double kp = 0.6, ki = 0.00, kd = 0.;
	double def = 0.;
	static double pre_def = 0.;

	/*if(i_pos_clear_flag == 1){
		i_pos = 0;
		i_pos_clear_flag = 0;
	}*/

	def = ( ( sensor0 + sensor1 + sensor2 + sensor3 + sensor4 + sensor5 ) / 6 ) - ( ( sensor6 + sensor7 + sensor8 + sensor9 + sensor10 + sensor11 ) / 6 );

	p = kp * def; //P制御
	i += ki * def * DELTA_T; //I制御
	d = kd * (def - pre_def) / DELTA_T; //D制御

	motor_L = speed_L + (int)( p + i + d );
	motor_R = speed_R - ( p + i + d );

	pre_def = def;

	mon_def = def;
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
