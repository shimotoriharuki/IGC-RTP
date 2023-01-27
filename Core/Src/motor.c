/*
 * Motor.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Haruki SHIMOTORI
 */

#include <Motor.h>

TIM_HandleTypeDef htim8;

static int16_t motor_l, motor_r;

void motorInit(void)
{
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1); //PWM start
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2); //PWM start
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3); //PWM start
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4); //PWM start

	//motor driver wakeup
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);
	HAL_Delay(100);
}

void motorCtrlFlip(void)
{
	int16_t motor_pwm_l, motor_pwm_r;
	int16_t reverse_motor_l, reverse_motor_r;

	if(motor_l >= 0){
		reverse_motor_l = MAX_COUNTER_PERIOD - motor_l;
	}
	else{
		reverse_motor_l = MIN_COUNTER_PERIOD - motor_l;
	}
	if(motor_r >= 0){
		reverse_motor_r = MAX_COUNTER_PERIOD - motor_r;
	}
	else{
		reverse_motor_r = MIN_COUNTER_PERIOD - motor_r;
	}

	if(reverse_motor_l > 0) {
		motor_pwm_l = reverse_motor_l;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, motor_pwm_l);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);

	}
	else {
		motor_pwm_l = reverse_motor_l * (-1) ;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, motor_pwm_l);
	}


	if(reverse_motor_r > 0) {
		motor_pwm_r = reverse_motor_r;
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, motor_pwm_r);
	}
	else {
		motor_pwm_r = reverse_motor_r * (-1);
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, motor_pwm_r);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
	}
}

void setMotor(int16_t l, int16_t r)
{
	if(l >= MAX_COUNTER_PERIOD) l = MAX_COUNTER_PERIOD;
	else if(l <= MIN_COUNTER_PERIOD) l = MIN_COUNTER_PERIOD;

	if(r >= MAX_COUNTER_PERIOD) r = MAX_COUNTER_PERIOD;
	else if(r <= MIN_COUNTER_PERIOD) r = MIN_COUNTER_PERIOD;

	motor_l = l;
	motor_r = r;

}
