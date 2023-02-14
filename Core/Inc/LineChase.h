/*
 * LineChase.h
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#ifndef INC_LINECHASE_H_
#define INC_LINECHASE_H_

#include "stm32f4xx_hal.h"
#include "Motor.h"
#include "LineSensor.h"
#include "VelocityCtrl.h"

void calculateLineFollowingTermFlip(void);
void lineTraceFlip(void);
void astrayStop();

float getLineFollowingTerm(void);

void setSpeed(int16_t, int16_t);

void startLineTrace();
void stopLineTrace();

void checkCourseOut(void);
bool getCouseOutFlag(void);

#endif /* INC_LINECHASE_H_ */
