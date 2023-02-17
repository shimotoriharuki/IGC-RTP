/*
 *
 * Motor.h
 *
 *  Created on: Jan 26, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "stdlib.h"

#define MAX_COUNTER_PERIOD 1679
#define MIN_COUNTER_PERIOD -1679

#define DRONE_MAX_COUNTER_PERIOD 839

void initMotor(void);
void motorCtrlFlip(void);
void droneMotorCtrlFlip(void);
void setMotor(int16_t, int16_t);
void setDroneMotor(int16_t, int16_t);


#endif /* INC_MOTOR_H_ */
