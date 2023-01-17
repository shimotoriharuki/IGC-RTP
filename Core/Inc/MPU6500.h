/*
 * MPU6500.h
 *
 *  Created on: Jan 17, 2023
 *      Author: ryuku
 */

#ifndef INC_MPU6500_H_
#define INC_MPU6500_H_

#include <stdint.h>

uint8_t read_byte( uint8_t reg );

void write_byte( uint8_t reg, uint8_t val );

void mpu6500_init( void );

float mpu6500_read_gyro_z( void );

#endif /* INC_MPU6500_H_ */
