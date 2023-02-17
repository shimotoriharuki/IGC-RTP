/*
 * Logger.h
 *
 *  Created on: 2023/02/09
 *      Author: ryuku
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include "main.h"
#include "math.h"
#include "Flash_F405.h"

uint32_t writeAdd_1, writeAdd_2, writeAdd_3, writeAdd_4, writeAdd_5;
uint32_t readAdd_1, readAdd_2, readAdd_3, readAdd_4, readAdd_5;

void saveDistance(float);
void saveTheta(float);
void saveCross(float);
void saveSide(float);
void saveDebug(float);
void initLog(void);
void ereaseLog(void);
void ereaseDebugLog(void);
uint16_t getDistanceLogSize();
uint16_t getCrossLogSize();
uint16_t getSideLogSize();
uint16_t getDebugLogSize();
void loadDistance();
void loadTheta();
void loadCross();
void loadSide();
void loadDebug();

float getDistanceLog(uint16_t);
float getThetaLog(uint16_t);
float getCrossLog(uint16_t);
float getSideLog(uint16_t);
float getDebugLog(uint16_t);

const float *getDistanceArrayPointer();
const float *getThetaArrayPointer();
const float *getCrossArrayPointer();
const float *getSideArrayPointer();

#endif /* INC_LOGGER_H_ */
