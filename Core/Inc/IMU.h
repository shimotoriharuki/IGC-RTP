/*
 * IMU.h
 *
 *  Created on: 2023/02/11
 *      Author: ryuku
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "MPU6500.h"
#include "math.h"

#define R_IMU 0.03//0.03 Lowpath filter constant. The smaller it is, the more effective/


void gyroinit();
void IMUupdateValue();
float getOmega();

#endif /* INC_IMU_H_ */