/*
 * Running.h
 *
 *  Created on: Jan 28, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_RUNNING_H_
#define INC_RUNNING_H_

#include "stm32f4xx_hal.h"
#include "SideSensor.h"
#include "LineChase.h"
#include "Encoder.h"
#include "stdbool.h"
#include "Logger.h"

uint8_t isCrossLine();

void running();
void runningFlip();
void runningInit();
void saveLog();
void logStart();

bool isTargetDistance(float);

#endif /* INC_RUNNING_H_ */
