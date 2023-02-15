/*
 * VelocityCtrl.h
 *
 *  Created on: 2023/01/28
 *      Author: Haruki SHIMOTORI
 */

#ifndef INC_VELOCITYCTRL_H_
#define INC_VELOCITYCTRL_H_

#include "stm32f4xx_hal.h"
#include "Encoder.h"
#include "Motor.h"
#include "UserSelection.h"

void calculateVelocityControlFlip(void);
float getVelocityControlTerm(void);

float getCurrentVelocity(void);
void setTargetVelocity(float);

void startVelocityControl(void);
void stopVelocityControl(void);

void setClearFlagOfVelocityControlI();

#endif /* INC_VELOCITYCTRL_H_ */
