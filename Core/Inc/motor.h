/*
 * Motor.h
 *
 *  Created on: Jan 26, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"

#define MAX_COUNTER_PERIOD 1678
#define MIN_COUNTER_PERIOD -1678

TIM_HandleTypeDef htim8;
int16_t motor_l_, motor_r_;

void motorInit(void);
void motorCtrlFlip(void);
void motorSet(int16_t, int16_t);


#endif /* INC_MOTOR_H_ */
