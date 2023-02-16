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


float velocity_table[6000];

bool isCrossLine();
bool isContinuousCurvature();

void setRunMode(uint16_t);
bool isTargetDistance(float);

void running();
void runningFlip();
void runningInit();

void saveLog();
void startLogging();
void stopLogging();

void startVelocityUpdate();
void stopVelocityUpdate();
void createVelocityTable();
float radius2Velocity(float);
void decelerateProcessing(const float, const float *);
void accelerateProcessing(const float, const float *);
void addDecelerationDistanceMergin(float *, int16_t);
void shiftVelocityTable(float *, int16_t);
void updateTargetVelocity();
float getVelocityTableValue(uint16_t);

void correctionTotalDistanceFromCrossLine();
void correctionTotalDistanceFromSideLine();

void setVelocityRange(float, float);
void setAccDec(float, float);

#endif /* INC_RUNNING_H_ */
