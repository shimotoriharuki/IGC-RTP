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
#include "IMU.h"
#include "stdlib.h"
#include "LED.h"

bool isCrossLine();

float velocity_table[6000];

void running();
void runningFlip();
void runningInit();
void saveLog();
void startLogging();
void stopLogging();
void startVelocityUpdate();
void stopVelocityUpdate();
void createVelocityTable();
void decelerateProcessing(const float, const float *);
void accelerateProcessing(const float, const float *);
void updateTargetVelocity();
void setRunMode(uint16_t);

float radius2Velocity(float);

bool isTargetDistance(float);

#endif /* INC_RUNNING_H_ */
