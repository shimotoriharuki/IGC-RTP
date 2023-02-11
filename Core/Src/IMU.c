/*
 * IMU.c
 *
 *  Created on: 2023/02/11
 *      Author: ryuku
 */

#include "IMU.h"
#define PI 3.1415926535

int16_t xg_, yg_, zg_;
float omega;

void gyroinit(){
	uint8_t who_i_am;
	who_i_am = IMU_init();
	HAL_Delay(500);
}

void IMUupdateValue(){
	read_gyro_data();
	zg_ = zg;

	static int16_t pre_zg;
	zg_ = (R_IMU)*(zg) + (1.0 - (R_IMU))* (pre_zg);	// ｑニブかったら消す

	pre_zg = zg_;

	float corrected_zg = zg_;
	omega = -(corrected_zg / 16.4) * PI / 180;
}

float getOmega(){
	return omega * 0.01;
}
