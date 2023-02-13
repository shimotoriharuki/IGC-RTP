/*
 * LineSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_LINESENSOR_H_
#define INC_LINESENSOR_H_

#define SENSOR_ALL_DARK 50

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define LINESENSOR_ADC_NUM 12

int16_t sensor[LINESENSOR_ADC_NUM];

void initADC(void);
void storeAnalogSensorBuffer(void);
void updateAnalogSensor(void);


#endif /* INC_LINESENSOR_H_ */
