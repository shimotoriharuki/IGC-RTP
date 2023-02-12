/*
 * Running.c
 *
 *  Created on: Jan 28, 2023
 *      Author: Haruki SHIMOTORI
 */

#include "Running.h"

uint8_t mon_is_crossline;
uint16_t velocity_table_idx;
uint16_t mode;

float ref_distance;

static uint8_t start_goal_line_cnt;
static bool log_flag;
uint16_t cnt_log;

uint8_t isCrossLine()
{
	static uint16_t cnt = 0;
	//float sensor_edge_val_l = (sensor[0] + sensor[1]) / 2;
	//float sensor_edge_val_r = (sensor[10] + sensor[11]) / 2;
	float sensor_edge_val_l = sensor[0];
	float sensor_edge_val_r = sensor[11];
	static uint8_t flag = 0;

	//mon_ave_l = sensor_edge_val_l;
	//mon_ave_r = sensor_edge_val_r;

	//if(white_flag == false){
		//if(sensor_edge_val_l < 700 && sensor_edge_val_r < 700 && getCrossLineIgnoreDistance() >= 50){
		if(sensor_edge_val_l < 700 && sensor_edge_val_r < 700){
			cnt++;
		}
		else{
			cnt = 0;
		}

		if(cnt >= 3){
			flag = 1;
			//white_flag = true;
			//cnt = 0;

			//enableSideSensorIgnore();
			//clearCrossLineIgnoreDistance();
			//encoder_->clearSideLineIgnoreDistance();
			//encoder_->clearCrossLineIgnoreDistance();

			//stable_cnt_reset_flag_ = true; //Because the conditions do not differ between when you tremble and when you do not tremble
			//stable_flag_force_ = true;
			/*
			if(mode_selector_ == FIRST_RUNNING){
				store_check_cnt_ = 0;
				storeFirstRunCrossLineDistance();
			}
			else{
				store_check_cnt_ = 0;
				correctionTotalDistanceFromCrossLine();
				storeAccDecRunCrossLineDistance(); //for correction check
			}
			*/
		}
		else{
			flag = 0;
		}

	return flag;
}

void runMode(uint16_t num){
	mode = num;
}

void running(void)
{
	uint8_t goal_flag = 0;
	uint16_t pattern = 0;
	startLineTrace();
	startVelocityControl();
	runningInit();

	while(goal_flag == 0){
		switch(pattern){
		  case 0:
			  if(start_goal_line_cnt == 1) pattern = 10;
			  startVelocityPlay();
			  if(mode == 1) logStart();
			  break;

		  case 10:
			  HAL_Delay(0);
			  pattern = 20;
			  //if()
			  break;


		  case 20:
			  if(start_goal_line_cnt == 2){
				  HAL_Delay(100);
				  pattern = 30;
			  }

			  break;

		  case 30:
			  setTargetVelocity(0.0);
			  log_flag = false;
			  //goal_flag = 1;

			  break;
		};
	}
}

void updateTargetVelocity(){
	if(mode == 1) setTargetVelocity(0.5);
	if(mode == 2){
		if(getTotalDistance() >= ref_distance){
			ref_distance += getIdxDistance(velocity_table_idx);
			velocity_table_idx++;
		}
		if(velocity_table_idx >= getlogSize()){
			velocity_table_idx = getlogSize() - 1;
		}
		setTargetVelocity(velocity_table[velocity_table_idx]);
	}
}

void startVelocityPlay(){
	clearTotalDistance();
	velocity_table_idx = 0;
	ref_distance = 0;
}

void runningFlip()
{
	static uint8_t cross_line_ignore_flag;
	static uint8_t side_line_ignore_flag;

	updateTargetVelocity();

	if(isTargetDistance(10) == true){
		saveLog();
		clearDistance10mm();
	}

	if(isCrossLine() == 1 && cross_line_ignore_flag == 0){ //Cross line detect
		cross_line_ignore_flag = 1;
		side_line_ignore_flag = 1;
		clearCrossLineIgnoreDistance();
		clearSideLineIgnoreDistance();
	}
	else if(cross_line_ignore_flag == 1 && getCrossLineIgnoreDistance() >= 50){
		cross_line_ignore_flag = 0;
	}

	if(getSideSensorStatusR() == 1 && side_line_ignore_flag == 0){ //Right side line detect
		side_line_ignore_flag = 1;
		start_goal_line_cnt++;
		clearSideLineIgnoreDistance();
	}
	else if(side_line_ignore_flag == 1 && getSideLineIgnoreDistance() >= 150){
		side_line_ignore_flag = 0;
	}


}

void runningInit()
{
	clearCrossLineIgnoreDistance();
	clearSideLineIgnoreDistance();
}

bool isTargetDistance(float target){
	bool ret = false;
	if(getDistance10mm() >= target){
		ret = true;
	}
	return ret;
}

void saveLog(){
	if(log_flag == true){
		static float cnt;
		saveDistance(getDistance10mm());
		saveTheta(getOmega());
		cnt_log = cnt;
		cnt++;
	}
}

void logStart(){
	clearDistance10mm();
	log_flag = true;
}

void createVelocityTable(){
	const float *p_distance, *p_theta;
	p_distance = getDistanceArrayPointer();
	p_theta = getThetaArrayPointer();
	float temp_distance, temp_theta;

	uint16_t log_size = getlogSize();

	for(uint16_t i = 0; i < log_size; i++){
		temp_distance = p_distance[i];
		temp_theta = p_theta[i];

		if(temp_theta == 0) temp_theta = 0.00001;
		float radius = abs(temp_distance / temp_theta);
		if(radius >= 5000) radius = 5000;
		velocity_table[i] = radius2Velocity(radius);
	}
	decelerateProcessing(1, p_distance);
	accelerateProcessing(5, p_distance);
	velocity_table[0] = 1.2;
}

float radius2Velocity(float radius){
	float velocity;

	if(radius < 400) velocity = 1.2;
	else if(radius < 500) velocity = 1.5;
	else if(radius < 650) velocity = 1.8;
	else if(radius < 1500) velocity = 2.0;
	else if(radius < 2000) velocity = 2.5;
	else velocity = 2.5;

	return velocity;
}

void decelerateProcessing(const float am, const float *p_distance){
	uint16_t log_size = getlogSize();
	for(uint16_t i = log_size - 1; i >= 1; i--){
		float v_diff = velocity_table[i-1] - velocity_table[i];

		if(v_diff > 0){
			float t = p_distance[i]*1e-3 / v_diff;
			float a = v_diff / t;
			if(a > am){
				velocity_table[i-1] = velocity_table[i] + am * p_distance[i]*1e-3;
			}
		}
	}
}

void accelerateProcessing(const float am, const float *p_distance){
	uint16_t log_size = getlogSize();
	for(uint16_t i = 0; i <= log_size - 1; i++){
		float v_diff = velocity_table[i+1] - velocity_table[i];

		if(v_diff > 0){
			float t = p_distance[i]*1e-3 / v_diff;
			float a = v_diff / t;
			if(a > am){
				velocity_table[i+1] = velocity_table[i] + am * p_distance[i]*1e-3;
			}
		}
	}
}
