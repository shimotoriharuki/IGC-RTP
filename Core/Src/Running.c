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
static bool logging_flag;
static bool velocity_update_flag;
uint16_t cnt_log;

static bool cross_line_ignore_flag;
static bool goal_judge_flag = false;

bool isCrossLine()
{
	static uint16_t cnt = 0;
	//float sensor_edge_val_l = (sensor[0] + sensor[1]) / 2;
	//float sensor_edge_val_r = (sensor[10] + sensor[11]) / 2;
	float sensor_edge_val_l = sensor[0];
	float sensor_edge_val_r = sensor[11];
	static bool flag = false;

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
			flag = true;
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
			flag = false;
		}

	return flag;
}

void setRunMode(uint16_t num){
	mode = num;
}

void running(void)
{
	uint8_t goal_flag = 0;
	uint16_t pattern = 0;

	startLineTrace();
	startVelocityControl();
	runningInit();

	setLED('B');
	while(goal_flag == 0){
		switch(pattern){
		  case 0:
			  setLED('R');

			  if(getSideSensorStatusR() == true){ //Right side line detect
				  start_goal_line_cnt++;

				  if(mode == 1) startLogging();
				  else if(mode == 2) startVelocityUpdate();

				  clearGoalJudgeDistance();
				  pattern = 5;
			  }

			  break;

		  case 5:
			  setLED('B');
			  if(getSideSensorStatusR() == false) pattern = 10;

		  case 10:
			  setLED('G');

			  //--- Goal marker Check ---//
			  if(getSideSensorStatusL() == true){ //Leght side line detect
				  goal_judge_flag = false;
				  clearGoalJudgeDistance();
			  }

			  if(goal_judge_flag == false && getSideSensorStatusR() == true && getGoalJudgeDistance() >=30){
				  goal_judge_flag = true;
				  clearGoalJudgeDistance();
			  }
			  else if(goal_judge_flag == true && getGoalJudgeDistance() >= 30){
				  start_goal_line_cnt++;
				  goal_judge_flag = false;

			  }


			  if(start_goal_line_cnt >= 2){
				  stopLogging();
				  stopVelocityUpdate();
				  pattern = 20;
			  }

			  break;

		  case 20:
			  setLED('B');

			  setTargetVelocity(0.0);
			  HAL_Delay(500);

			  stopVelocityControl();
			  stopLineTrace();
			  //setMotor(0, 0);

			  goal_flag = 1;

			  break;
		};
	}
}

void updateTargetVelocity(){
	if(velocity_update_flag == true){
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


void runningFlip()
{
	//static uint16_t side_l_cnt, side_r_cnt;

	updateTargetVelocity();

	if(isTargetDistance(10) == true){
		saveLog();
		clearDistance10mm();
		clearTheta10mm();
	}

	//--- Cross Line Process ---//
	if(isCrossLine() == 1 && cross_line_ignore_flag == false){ //Cross line detect
		cross_line_ignore_flag = true;
		//side_line_ignore_flag = true;
		clearCrossLineIgnoreDistance();
		clearSideLineIgnoreDistance();

		saveCross(getTotalDistance());
	}
	else if(cross_line_ignore_flag == true && getCrossLineIgnoreDistance() >= 50){
		cross_line_ignore_flag = false;
	}


	/*
	if(getSideSensorStatusR() == 1 && side_line_ignore_flag == false){ //Right side line detect
		side_line_ignore_flag = true;
		start_goal_line_cnt++;
		clearSideLineIgnoreDistance();
	}
	else if(side_line_ignore_flag == true && getSideLineIgnoreDistance() >= 150){
		side_line_ignore_flag = false;
	}
	*/


}

void runningInit()
{
	clearCrossLineIgnoreDistance();
	clearSideLineIgnoreDistance();
	start_goal_line_cnt = 0;
	cross_line_ignore_flag = false;
	goal_judge_flag = false;
}

bool isTargetDistance(float target){
	bool ret = false;
	if(getDistance10mm() >= target){
		ret = true;
	}
	return ret;
}

void saveLog(){
	if(logging_flag == true){
		saveDistance(getDistance10mm());
		saveTheta(getTheta10mm());
	}
}

void startLogging(){
	clearDistance10mm();
	clearTheta10mm();
	clearTotalDistance();
	logging_flag = true;
}

void stopLogging()
{
	logging_flag = false;
}

void startVelocityUpdate(){
	clearDistance10mm();
	clearTotalDistance();
	velocity_table_idx = 0;
	ref_distance = 0;
	velocity_update_flag = true;
}

void stopVelocityUpdate()
{
	velocity_update_flag = false;
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

	decelerateProcessing(10, p_distance);
	accelerateProcessing(10, p_distance);

	velocity_table[0] = 1.2;
}

float radius2Velocity(float radius){
	float velocity;

	if(mode == 2){
		if(radius < 1000) velocity = 0.5;
		else velocity = 1.0;
	}
	else if(mode == 3){
		if(radius < 400) velocity = 1.2;
		else if(radius < 500) velocity = 1.5;
		else if(radius < 650) velocity = 1.8;
		else if(radius < 1500) velocity = 2.0;
		else if(radius < 2000) velocity = 2.5;
		else velocity = 2.5;

	}

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
