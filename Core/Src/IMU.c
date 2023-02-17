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
float theta_10mm;

uint8_t initGyro(){
	uint8_t who_i_am;
	who_i_am = IMU_init();
	HAL_Delay(500);

	return who_i_am;
}

void updateIMUValue(){
	read_gyro_data();
	zg_ = zg;

	static int16_t pre_zg;
	zg_ = (R_IMU)*(zg) + (1.0 - (R_IMU))* (pre_zg);	// ｑニブかったら消す

	pre_zg = zg_;

	float corrected_zg = zg_;
	omega = (corrected_zg / 16.4) * PI / 180;

	theta_10mm += omega * 0.001;
}

float getOmega(){
	return omega;
}

float getTheta10mm()
{
	return theta_10mm;
}

void clearTheta10mm()
{
	theta_10mm = 0;
}
