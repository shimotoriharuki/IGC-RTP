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

#define MAX_COUNTER_PERIOD 1679
#define MIN_COUNTER_PERIOD -1679

extern int16_t motor_L, motor_R;
extern uint16_t analog[LINESENSOR_ADC_NUM];

void motorSet(void);
void storeAdBuffer(void);
void getAnalogsensor(void);
void lineTrace(void);

#endif /* INC_LINECHASE_H_ */
