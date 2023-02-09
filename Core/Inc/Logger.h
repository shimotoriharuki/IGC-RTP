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

uint32_t writeAdd_1, writeAdd_2, writeAdd_3, writeAdd_4;
uint32_t readAdd_1, readAdd_2, readAdd_3, readAdd_4;

void saveDistance(float);
void saveTheta(float);
void saveCross(float);
void saveSide(float);
void loginit(void);
void erease(void);
void getDistance();
void getTheta();
void getCross();
void getSide();

const float *getDistanceArrayPointer();
const float *getTheteArrayPointer();
const float *getCrossArrayPointer();
const float *getSideArrayPointer();

#endif /* INC_LOGGER_H_ */
