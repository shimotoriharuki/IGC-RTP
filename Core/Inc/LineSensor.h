/*
 * LineSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_LINESENSOR_H_
#define INC_LINESENSOR_H_

#define LINESENSOR_ADC_NUM 12


#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "LineChase.h"
#include "Switch.h"

#define LINESENSOR_ADC_NUM 12

float sensor_coefficient[LINESENSOR_ADC_NUM];
float offset_values[LINESENSOR_ADC_NUM];

int16_t sensor[LINESENSOR_ADC_NUM];

void initADC(void);
void storeAnalogSensorBuffer(void);
void updateAnalogSensor(void);
void sensorCalibration();
//void calibration();


#endif /* INC_LINESENSOR_H_ */
