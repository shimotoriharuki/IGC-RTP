/*
 * SideSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_SIDESENSOR_H_
#define INC_SIDESENSOR_H_

#include "stm32f4xx_hal.h"

void updateSideSensorStatus(void);
uint8_t getSideSensorStatusL(void);
uint8_t getSideSensorStatusR(void);

/*
void enableSideSensorIgnore(void);
void disableSideSensorIgnore(void);
uint8_t getSideSensorIgnoreFlag(void);
*/

#endif /* INC_SIDESENSOR_H_ */
