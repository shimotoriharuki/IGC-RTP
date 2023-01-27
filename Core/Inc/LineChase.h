/*
 * LineChase.h
 *
 *  Created on: Jan 15, 2023
 *      Author: ryuku
 */

#ifndef INC_LINECHASE_H_
#define INC_LINECHASE_H_

#define LINESENSOR_ADC_NUM 12

#include "main.h"
#include "Motor.h"

//extern uint16_t analog[LINESENSOR_ADC_NUM];

extern uint8_t side_sensor_L, side_sensor_R;
extern int16_t speed_L, speed_R;


//void motorSet(void);
void storeAdBuffer(void);
void getAnalogsensor(void);
void lineTrace(void);
void updateSideSensorState(void);

#endif /* INC_LINECHASE_H_ */
