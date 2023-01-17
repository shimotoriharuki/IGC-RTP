/*
 * MPU6050.c
 *
 *  Created on: Jan 17, 2023
 *      Author: ryuku
 */

#include "mpu6500.h"

volatile int16_t xa, ya, za;
volatile int16_t xg, yg, zg;

uint8_t read_byte( uint8_t reg ) {
	uint8_t ret,val;

		ret = reg | 0x80;
		CS_RESET;
		HAL_SPI_Transmit(&hspi3, &ret, 1, 100);
		HAL_SPI_Receive(&hspi3, &val, 1, 100);
		CS_SET;

	return val;
}

void write_byte( uint8_t reg, uint8_t val )  {
	uint8_t ret;

	ret = reg & 0x7F;
	CS_RESET;
	HAL_SPI_Transmit(&hspi3, &ret, 1, 100);
	HAL_SPI_Receive(&hspi3, &val, 1, 100);
	CS_SET;
}

uint8_t IMU_init() {
	uint8_t who_am_i, ret;

	who_am_i = read_byte( 0x75 );
	if ( who_am_i == 0x70 ) {
		ret = 1;
		write_byte(0x6B, 0x00);	//sleep mode解除
		HAL_Delay(100);
		write_byte(0x1A, 0x00);
		write_byte(0x1B, 0x18);
	}
	return ret;
}

void read_gyro_data() {
//	xg = ((int16_t)read_byte(0x33) << 8) | ((int16_t)read_byte(0x34));
//	yg = ((int16_t)read_byte(0x35) << 8) | ((int16_t)read_byte(0x36));
	zg = ((int16_t)read_byte(0x47) << 8) | ((int16_t)read_byte(0x48));
}

void read_accel_data() {
	xa = ((int16_t)read_byte(0x2D) << 8) | ((int16_t)read_byte(0x2E));
	ya = ((int16_t)read_byte(0x2F) << 8) | ((int16_t)read_byte(0x30));
	za = ((int16_t)read_byte(0x31) << 8) | ((int16_t)read_byte(0x32));
}
