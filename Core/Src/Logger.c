/*
 * Logger.c
 *
 *  Created on: 2023/02/09
 *      Author: ryuku
 */

#include "Logger.h"

static float log_cross[200];
static float log_side[200];
static float log_distance[6000];
static float log_theta[6000];
static uint16_t log_distance_cnt, log_theta_cnt, log_cross_cnt, log_side_cnt;

void loginit(){
	writeAdd_1 = start_adress_sector7;
	writeAdd_2 = start_adress_sector8;
	writeAdd_3 = start_adress_sector9;
	writeAdd_4 = start_adress_sector10;
	readAdd_1 = start_adress_sector7;
	readAdd_2 = start_adress_sector8;
	readAdd_3 = start_adress_sector9;
	readAdd_4 = start_adress_sector10;
}

void saveDistance(float distance){
	FLASH_Write_Word_F(writeAdd_1, distance);
	writeAdd_1 += 0x04;
}

void saveTheta(float theta){
	FLASH_Write_Word_F(writeAdd_2, theta);
	writeAdd_2 += 0x04;
}

void saveCross(float cross){
	FLASH_Write_Word_F(writeAdd_3, cross);
	writeAdd_3 += 0x04;
}

void saveSide(float side){
	FLASH_Write_Word_F(writeAdd_4, side);
	writeAdd_4 += 0x04;
}

void erease(){
	FLASH_EreaseSector(FLASH_SECTOR_7);
	FLASH_EreaseSector(FLASH_SECTOR_8);
	FLASH_EreaseSector(FLASH_SECTOR_9);
	FLASH_EreaseSector(FLASH_SECTOR_10);
}

void getDistance(){
	uint16_t i = 0;
	while(1){
		log_distance[i] = *(float*)readAdd_1;
		if(isnan(log_distance[i]) != 0){
			break;
		}
		else{
			log_distance_cnt++;
		}
		readAdd_1 += 0x04;
		i++;
	}
}

void getTheta(){
	uint16_t i = 0;
	while(1){
		log_theta[i] = *(float*)readAdd_2;
		if(isnan(log_theta[i]) != 0){
			break;
		}
		else{
			log_theta_cnt++;
		}
		readAdd_2 += 0x04;
		i++;
	}
}

void getCross(){
	uint16_t i = 0;
	while(1){
		log_cross[i] = *(float*)readAdd_3;
		if(isnan(log_cross[i]) != 0){
			break;
		}
		else{
			log_cross_cnt++;
		}
		readAdd_3 += 0x04;
		i++;
	}
}

void getSide(){
	uint16_t i = 0;
	while(1){
		log_side[i] = *(float*)readAdd_4;
		if(isnan(log_side[i]) != 0){
			break;
		}
		else{
			log_side_cnt++;
		}
		readAdd_4 += 0x04;
		i++;
	}
}

const float *getDistanceArrayPointer(){
	return log_distance;
}

const float *getThetaArrayPointer(){
	return log_theta;
}

const float *getCrossArrayPointer(){
	return log_cross;
}

const float *getSideArrayPointer(){
	return log_side;
}
