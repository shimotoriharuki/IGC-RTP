/*
 * LineSensor.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_LINESENSOR_H_
#define INC_LINESENSOR_H_

#include "stm32f4xx_hal.h"

#define LINESENSOR_ADC_NUM 12

ADC_HandleTypeDef hadc1;

uint16_t adc_value[LINESENSOR_ADC_NUM];

extern int16_t sensor[LINESENSOR_ADC_NUM];

int16_t sensor0_buffer[10];
int16_t sensor1_buffer[10];
int16_t sensor2_buffer[10];
int16_t sensor3_buffer[10];
int16_t sensor4_buffer[10];
int16_t sensor5_buffer[10];
int16_t sensor6_buffer[10];
int16_t sensor7_buffer[10];
int16_t sensor8_buffer[10];
int16_t sensor9_buffer[10];
int16_t sensor10_buffer[10];
int16_t sensor11_buffer[10];

void adcInit(void);
void storeAnalogSensorBuffer(void);
void updateAnalogSensor(void);


#endif /* INC_LINESENSOR_H_ */
