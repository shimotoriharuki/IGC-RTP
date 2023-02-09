/*
 * Encoder.h
 *
 *  Created on: Jan 18, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx_hal.h"

void initEncoder(void);
void updateEncoderCnt(void);
void getEncoderCnt(int16_t *, int16_t *);

float getDistance10mm(void);
void clearDistance10mm(void);
float getCrossLineIgnoreDistance(void);
float getSideLineIgnoreDistance(void);

void clearCrossLineIgnoreDistance(void);
void clearSideLineIgnoreDistance(void);

void resetEncoderCnt(void);


#endif /* INC_ENCODER_H_ */
