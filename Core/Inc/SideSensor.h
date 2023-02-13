/*
 * SideSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_SIDESENSOR_H_
#define INC_SIDESENSOR_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

void updateStatusLeftExti();
void updateStatusRightExti();
void updateSideSensorStatus(void);
bool getSideSensorStatusL(void);
bool getSideSensorStatusR(void);

/*
void enableSideSensorIgnore(void);
void disableSideSensorIgnore(void);
uint8_t getSideSensorIgnoreFlag(void);
*/

#endif /* INC_SIDESENSOR_H_ */
