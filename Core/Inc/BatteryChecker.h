/*
 * BatteryChecker.h
 *
 *  Created on: 2023/02/12
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_BATTERYCHECKER_H_
#define INC_BATTERYCHECKER_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

void initBatteryChecker();
bool getBatteryVoltage();

#endif /* INC_BATTERYCHECKER_H_ */
