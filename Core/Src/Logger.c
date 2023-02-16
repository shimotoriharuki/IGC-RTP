/*
 * Logger.c
 *
 *  Created on: 2023/02/09
 *      Author: ryuku
 */

#include "Logger.h"

static float log_cross[200];
static float log_side[200];
static float log_debug[200];
static float log_distance[6000];
static float log_theta[6000];
static float log_gain[100];
static float log_calibration[100];
static uint16_t log_distance_cnt, log_theta_cnt, log_cross_cnt, log_side_cnt, log_debug_cnt, log_gain_cnt, log_calibration_cnt;

void initLog(){
	writeAdd_1 = start_adress_sector7;
	writeAdd_2 = start_adress_sector8;
	writeAdd_3 = start_adress_sector9;
	writeAdd_4 = start_adress_sector10;
	writeAdd_5 = start_adress_sector11;
	//writeAdd_6 = start_adress_sector3;
	//writeAdd_7 = start_adress_sector4;
	readAdd_1 = start_adress_sector7;
	readAdd_2 = start_adress_sector8;
	readAdd_3 = start_adress_sector9;
	readAdd_4 = start_adress_sector10;
	readAdd_5 = start_adress_sector11;
	//readAdd_6 = start_adress_sector3;
	//readAdd_7 = start_adress_sector4;
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

void saveDebug(float cross){
	FLASH_Write_Word_F(writeAdd_5, cross);
	writeAdd_5+= 0x04;
}

void saveGain(float gain){
	FLASH_Write_Word_F(writeAdd_6, gain);
	writeAdd_6+= 0x04;
}

void saveCalibration(float calibration){
	FLASH_Write_Word_F(writeAdd_7, calibration);
	writeAdd_7+= 0x04;
}

void ereaseLog(){
	//FLASH_EreaseSector(FLASH_SECTOR_3);
	//FLASH_EreaseSector(FLASH_SECTOR_4);
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
	writeAdd_5 = start_adress_sector11;
	//writeAdd_6 = start_adress_sector3;
	//writeAdd_7 = start_adress_sector4;
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

uint16_t getGain(){
	return log_gain_cnt;
}

uint16_t getalibration(){
	return log_calibration_cnt;
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

void loadGain(){
	uint16_t i = 0;
	//readAdd_6= start_adress_sector3;
	log_gain_cnt = 0;

	while(1){
		//log_gain[i] = *(float*)readAdd_6;
		if(isnan(log_gain[i]) != 0){
			break;
		}
		else{
			log_gain_cnt++;
		}
		//readAdd_6 += 0x04;
		i++;
	}
}

void loadCalibration(){
	uint16_t i = 0;
	//readAdd_7= start_adress_sector4;
	log_calibration_cnt = 0;

	while(1){
		//log_calibration[i] = *(float*)readAdd_7;
		if(isnan(log_calibration[i]) != 0){
			break;
		}
		else{
			log_calibration_cnt++;
		}
		//readAdd_7 += 0x04;
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

float getCrossLog(uint16_t idx){
	return log_cross[idx];
}

float getSideLog(uint16_t idx){
	return log_side[idx];
}

float getGainLog(uint16_t idx){
	return log_gain[idx];
}

float getCalibrationLog(uint16_t idx){
	return log_calibration[idx];
}
