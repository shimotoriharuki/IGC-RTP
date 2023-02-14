/*
 * LineSensor.c
 *
 *  Created on: Jan 27, 2023
 *      Author: Haruki SHIMOTORI
 */

#include "LineSensor.h"

ADC_HandleTypeDef hadc1;

float max_values[LINESENSOR_ADC_NUM], max_values_buffer[LINESENSOR_ADC_NUM];
float min_values[LINESENSOR_ADC_NUM], min_values_buffer[LINESENSOR_ADC_NUM];

static uint16_t adc_value[LINESENSOR_ADC_NUM];

static int16_t sensor0_buffer[10];
static int16_t sensor1_buffer[10];
static int16_t sensor2_buffer[10];
static int16_t sensor3_buffer[10];
static int16_t sensor4_buffer[10];
static int16_t sensor5_buffer[10];
static int16_t sensor6_buffer[10];
static int16_t sensor7_buffer[10];
static int16_t sensor8_buffer[10];
static int16_t sensor9_buffer[10];
static int16_t sensor10_buffer[10];
static int16_t sensor11_buffer[10];

void initADC()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adc_value, LINESENSOR_ADC_NUM); //ADC start
	for(uint16_t i = 0; i < LINESENSOR_ADC_NUM; i++){
		max_values[i] = 2000;
	}
}

  void storeAnalogSensorBuffer(void)
{
	static uint8_t index;

	sensor0_buffer[index] = sensor_coefficient[0] * (adc_value[0] - offset_values[0]) ;
	sensor1_buffer[index] = sensor_coefficient[1] * (adc_value[1] - offset_values[1]) ;
	sensor2_buffer[index] = sensor_coefficient[2] * (adc_value[2] - offset_values[2]) ;
	sensor3_buffer[index] = sensor_coefficient[3] * (adc_value[3] - offset_values[3]) ;
	sensor4_buffer[index] = sensor_coefficient[4] * (adc_value[4] - offset_values[4]) ;
	sensor5_buffer[index] = sensor_coefficient[5] * (adc_value[5] - offset_values[5]) ;
	sensor6_buffer[index] = sensor_coefficient[6] * (adc_value[6] - offset_values[6]) ;
	sensor7_buffer[index] = sensor_coefficient[7] * (adc_value[7] - offset_values[7]) ;
	sensor8_buffer[index] = sensor_coefficient[8] * (adc_value[8] - offset_values[8]) ;
	sensor9_buffer[index] = sensor_coefficient[9] * (adc_value[9] - offset_values[9]) ;
	sensor10_buffer[index] = sensor_coefficient[10] * (adc_value[10] - offset_values[10]) ;
	sensor11_buffer[index] = sensor_coefficient[11] * (adc_value[11] - offset_values[11]) ;

	index++;
	if(index >= 10) index = 0;
}

void updateAnalogSensor(void) {
	sensor[0] = ( sensor0_buffer[0] + sensor0_buffer[1] + sensor0_buffer[2] + sensor0_buffer[3] + sensor0_buffer[4] + sensor0_buffer[5] + sensor0_buffer[6] + sensor0_buffer[7] + sensor0_buffer[8] + sensor0_buffer[9] ) / 10;
	sensor[1] = ( sensor1_buffer[0] + sensor1_buffer[1] + sensor1_buffer[2] + sensor1_buffer[3] + sensor1_buffer[4] + sensor1_buffer[5] + sensor1_buffer[6] + sensor1_buffer[7] + sensor1_buffer[8] + sensor1_buffer[9] ) / 10;
	sensor[2] = ( sensor2_buffer[0] + sensor2_buffer[1] + sensor2_buffer[2] + sensor2_buffer[3] + sensor2_buffer[4] + sensor2_buffer[5] + sensor2_buffer[6] + sensor2_buffer[7] + sensor2_buffer[8] + sensor2_buffer[9] ) / 10;
	sensor[3] = ( sensor3_buffer[0] + sensor3_buffer[1] + sensor3_buffer[2] + sensor3_buffer[3] + sensor3_buffer[4] + sensor3_buffer[5] + sensor3_buffer[6] + sensor3_buffer[7] + sensor3_buffer[8] + sensor3_buffer[9] ) / 10;
	sensor[4] = ( sensor4_buffer[0] + sensor4_buffer[1] + sensor4_buffer[2] + sensor4_buffer[3] + sensor4_buffer[4] + sensor4_buffer[5] + sensor4_buffer[6] + sensor4_buffer[7] + sensor4_buffer[8] + sensor4_buffer[9] ) / 10;
	sensor[5] = ( sensor5_buffer[0] + sensor5_buffer[1] + sensor5_buffer[2] + sensor5_buffer[3] + sensor5_buffer[4] + sensor5_buffer[5] + sensor5_buffer[6] + sensor5_buffer[7] + sensor5_buffer[8] + sensor5_buffer[9] ) / 10;
	sensor[6] = ( sensor6_buffer[0] + sensor6_buffer[1] + sensor6_buffer[2] + sensor6_buffer[3] + sensor6_buffer[4] + sensor6_buffer[5] + sensor6_buffer[6] + sensor6_buffer[7] + sensor6_buffer[8] + sensor6_buffer[9] ) / 10;
	sensor[7] = ( sensor7_buffer[0] + sensor7_buffer[1] + sensor7_buffer[2] + sensor7_buffer[3] + sensor7_buffer[4] + sensor7_buffer[5] + sensor7_buffer[6] + sensor7_buffer[7] + sensor7_buffer[8] + sensor7_buffer[9] ) / 10;
	sensor[8] = ( sensor8_buffer[0] + sensor8_buffer[1] + sensor8_buffer[2] + sensor8_buffer[3] + sensor8_buffer[4] + sensor8_buffer[5] + sensor8_buffer[6] + sensor8_buffer[7] + sensor8_buffer[8] + sensor8_buffer[9] ) / 10;
	sensor[9] = ( sensor9_buffer[0] + sensor9_buffer[1] + sensor9_buffer[2] + sensor9_buffer[3] + sensor9_buffer[4] + sensor9_buffer[5] + sensor9_buffer[6] + sensor9_buffer[7] + sensor9_buffer[8] + sensor9_buffer[9] ) / 10;
	sensor[10] = ( sensor10_buffer[0] + sensor10_buffer[1] + sensor10_buffer[2] + sensor10_buffer[3] + sensor10_buffer[4] + sensor10_buffer[5] + sensor10_buffer[6] + sensor10_buffer[7] + sensor10_buffer[8] + sensor10_buffer[9] ) / 10;
	sensor[11] = ( sensor11_buffer[0] + sensor11_buffer[1] + sensor11_buffer[2] + sensor11_buffer[3] + sensor11_buffer[4] + sensor11_buffer[5] + sensor11_buffer[6] + sensor11_buffer[7] + sensor11_buffer[8] + sensor11_buffer[9] ) / 10;
}

void sensorCalibration()
{
	for(uint16_t i = 0; i < LINESENSOR_ADC_NUM; i++){
		max_values_buffer[i] = adc_value[i];
		min_values_buffer[i] = adc_value[i];
		if(max_values_buffer[i] < max_values[i]){
			max_values[i] = adc_value[i];
		}
		else if(min_values_buffer[i] > min_values[i]){
			min_values[i] = adc_value[i];
		}
	}
}

void calibration()
{
	for(uint16_t i = 0; i < LINESENSOR_ADC_NUM; i++){
		sensor_coefficient[i] = 3000 / (min_values[i] - max_values[i]);
	}
	for(uint16_t i = 0; i < LINESENSOR_ADC_NUM; i++){
		offset_values[i] = max_values[i];
	}
}
