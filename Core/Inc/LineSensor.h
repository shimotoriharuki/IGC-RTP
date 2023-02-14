/*
 * LineSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_LINESENSOR_H_
#define INC_LINESENSOR_H_

#define SENSOR_ALL_DARK 50
#define LINESENSOR_ADC_NUM 12

float sensor_coefficient[LINESENSOR_ADC_NUM];
float offset_values[LINESENSOR_ADC_NUM];

#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "LineChase.h"

#define LINESENSOR_ADC_NUM 12

int16_t sensor[LINESENSOR_ADC_NUM];

void initADC(void);
void storeAnalogSensorBuffer(void);
void updateAnalogSensor(void);
void sensorCalibration();


#endif /* INC_LINESENSOR_H_ */
