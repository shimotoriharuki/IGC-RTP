/*
 * motor.c
 *
 *  Created on: Jan 26, 2023
 *      Author: Haruki SHIMOTORI
 */

#include "motor.h"

void motorInit(void)
{
  HAL_TIM_PWM_Start(&htim8_, TIM_CHANNEL_1); //PWM start
  HAL_TIM_PWM_Start(&htim8_, TIM_CHANNEL_2); //PWM start
  HAL_TIM_PWM_Start(&htim8_, TIM_CHANNEL_3); //PWM start
  HAL_TIM_PWM_Start(&htim8_, TIM_CHANNEL_4); //PWM start

  //motor driver wakeup
  __HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
  __HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
  __HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
  __HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);
  HAL_Delay(100);
}

void motorCtrlFlip(void)
{
	int16_t motor_pwm_l, motor_pwm_r;
	int16_t rev_motor_l, rev_motor_r;

	if(motor_l_ >= MAX_COUNTER_PERIOD) motor_l_ = MAX_COUNTER_PERIOD;
	else if(motor_l_ <= MIN_COUNTER_PERIOD) motor_l_ = MIN_COUNTER_PERIOD;

	if(motor_r_ >= MAX_COUNTER_PERIOD) motor_r_ = MAX_COUNTER_PERIOD;
	else if(motor_r_ <= MIN_COUNTER_PERIOD) motor_r_ = MIN_COUNTER_PERIOD;

	if(motor_l_ >= 0){
		rev_motor_l = MAX_COUNTER_PERIOD - motor_l_;
	}
	else{
		rev_motor_l = MIN_COUNTER_PERIOD - motor_l_;
	}
	if(motor_r_ >= 0){
		rev_motor_r = MAX_COUNTER_PERIOD - motor_r_;
	}
	else{
		rev_motor_r = MIN_COUNTER_PERIOD - motor_r_;
	}

	if(rev_motor_l > 0) {
		motor_pwm_l = rev_motor_l;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_3, motor_pwm_l);
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_4, MAX_COUNTER_PERIOD);

	}
	else {
		motor_pwm_l = rev_motor_l*(-1) ;
		// motor1
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_3, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_4, motor_pwm_l);
	}


	if(rev_motor_r > 0) {
		motor_pwm_r = rev_motor_r;
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_1, MAX_COUNTER_PERIOD);
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_2, motor_pwm_r);
	}
	else {
		motor_pwm_r = rev_motor_r * (-1);
		//motor2
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_1, motor_pwm_r);
		__HAL_TIM_SET_COMPARE(&htim8_, TIM_CHANNEL_2, MAX_COUNTER_PERIOD);
	}
}

void motorSet(int16_t l, int16_t r)
{
	motor_l_ = l;
	motor_r_ = r;
}
