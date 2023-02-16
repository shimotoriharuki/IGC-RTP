/*
 * Logger.c
 *
 *  Created on: 2023/02/09
 *      Author: ryuku
 */

#include "Logger.h"

static float log_cross[200];
static float log_side[200];
static float log_debug[12000];
static float log_distance[6000];
static float log_theta[6000];
static uint16_t log_distance_cnt, log_theta_cnt, log_cross_cnt, log_side_cnt, log_debug_cnt;

void initLog(){
	writeAdd_1 = start_adress_sector7;
	writeAdd_2 = start_adress_sector8;
	writeAdd_3 = start_adress_sector9;
	writeAdd_4 = start_adress_sector10;
	writeAdd_5 = start_adress_sector11;
	readAdd_1 = start_adress_sector7;
	readAdd_2 = start_adress_sector8;
	readAdd_3 = start_adress_sector9;
	readAdd_4 = start_adress_sector10;
	readAdd_5 = start_adress_sector11;
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

void saveDebug(float value){
	FLASH_Write_Word_F(writeAdd_5, value);
	writeAdd_5+= 0x04;
}


void ereaseLog(){
	FLASH_EreaseSector(FLASH_SECTOR_7);
	FLASH_EreaseSector(FLASH_SECTOR_8);
	FLASH_EreaseSector(FLASH_SECTOR_9);
	FLASH_EreaseSector(FLASH_SECTOR_10);
	//FLASH_Erease11();
	FLASH_EreaseSector(FLASH_SECTOR_11);

	writeAdd_1 = start_adress_sector7;
	writeAdd_2 = start_adress_sector8;
	writeAdd_3 = start_adress_sector9;
	writeAdd_4 = start_adress_sector10;
	writeAdd_5= start_adress_sector11;
}

void ereaseDebugLog(){
	FLASH_EreaseSector(FLASH_SECTOR_11);

	writeAdd_5= start_adress_sector11;
}

uint16_t getDistanceLogSize(){
	return log_distance_cnt;
}

uint16_t getCrossLogSize(){
	return log_cross_cnt;
}

uint16_t getSideLogSize(){
	return log_side_cnt;
}

uint16_t getDebugLogSize(){
	return log_debug_cnt;
}


void loadDistance(){
	uint16_t i = 0;
	readAdd_1 = start_adress_sector7;
	log_distance_cnt = 0;

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

void loadTheta(){
	uint16_t i = 0;
	readAdd_2 = start_adress_sector8;
	log_theta_cnt = 0;

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

void loadCross(){
	uint16_t i = 0;
	readAdd_3 = start_adress_sector9;
	log_cross_cnt = 0;

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

void loadSide(){
	uint16_t i = 0;
	readAdd_4 = start_adress_sector10;
	log_side_cnt = 0;

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

void loadDebug(){
	uint16_t i = 0;
	readAdd_5= start_adress_sector11;
	log_debug_cnt = 0;

	while(1){
		log_debug[i] = *(float*)readAdd_5;
		if(isnan(log_debug[i]) != 0){
			break;
		}
		else{
			log_debug_cnt++;
		}
		readAdd_5 += 0x04;
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

float getDistanceLog(uint16_t idx){
	return log_distance[idx];
}

float getThetaLog(uint16_t idx){
	return log_theta[idx];
}

float getCrossLog(uint16_t idx){
	return log_cross[idx];
}

float getSideLog(uint16_t idx){
	return log_side[idx];
}

float getDebugLog(uint16_t idx){
	return log_debug[idx];
}
