/*
 * Running.c
 *
 *  Created on: Jan 28, 2023
 *      Author: Haruki SHIMOTORI
 */

#include "Running.h"

static float velocity_table[6000];

uint8_t mon_is_crossline;
uint16_t velocity_table_idx;
uint16_t mode;

float ref_distance;

static uint8_t start_goal_line_cnt;
static bool logging_flag;
static bool velocity_update_flag;
uint16_t cnt_log;

static bool cross_line_ignore_flag;
//static bool side_line_ignore_flag;
static bool goal_judge_flag = false;
static bool side_line_judge_flag = false;
static bool continuous_cnt_reset_flag = false;
static bool continuous_curve_flag = false;
static bool running_flag = false;

static uint16_t cross_line_idx;
static uint16_t side_line_idx;

static uint16_t correction_check_cnt_cross, correction_check_cnt_side;
static uint16_t continuous_curve_check_cnt;

static float min_velocity, max_velocity;
static float acceleration, deceleration;

float mon_diff_theta;

bool isCrossLine()
{
	static uint16_t cnt = 0;
	//float sensor_edge_val_l = (sensor[0] + sensor[1]) / 2;
	//float sensor_edge_val_r = (sensor[10] + sensor[11]) / 2;
	float sensor_edge_val_l = sensor[0];
	float sensor_edge_val_r = sensor[11];
	static bool flag = false;

	if(sensor_edge_val_l < 700 && sensor_edge_val_r < 700){
		cnt++;
	}
	else{
		cnt = 0;
	}

	if(cnt >= 3){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool isContinuousCurvature()
{
	static float pre_theta;
	static float continuous_cnt;
	bool continuous_flag = false;
	float diff_theta = fabs(pre_theta - getTheta10mm());

	if(continuous_cnt_reset_flag == true){
		continuous_cnt_reset_flag = false;
		continuous_cnt = 0;
	}

	if(diff_theta <= 0.005) continuous_cnt++;
	else continuous_cnt = 0;

	if(continuous_cnt >= 50) continuous_flag = true;

	if(continuous_cnt >= 1000) continuous_cnt = 1000;

	pre_theta = getTheta10mm();

	return continuous_flag;
}

void setRunMode(uint16_t num){
	mode = num;
}

bool isTargetDistance(float target){
	bool ret = false;
	if(getDistance10mm() >= target){
		ret = true;
	}
	return ret;
}

void running(void)
{
	uint8_t goal_flag = 0;
	uint16_t pattern = 0;

	runningInit();
	startLineTrace();
	startVelocityControl();
	setTargetVelocity(min_velocity);

	//setLED('B');
	while(goal_flag == 0){
		switch(pattern){
		  case 0:
			  //setLED('R');

			  if(getSideSensorStatusR() == true){ //Right side line detect
				  start_goal_line_cnt++;

				  if(mode == 1) startLogging();
				  else startVelocityUpdate();

				  clearGoalJudgeDistance();
				  clearSideLineJudgeDistance();
				  pattern = 5;
			  }

			  break;

		  case 5:
			  //setLED('B');
			  if(getSideSensorStatusR() == false) pattern = 10;

		  case 10:
			  //setLED('G');

			  //--- Goal marker Check ---//
			  if(getSideSensorStatusL() == true){ //Leght side line detect
				  goal_judge_flag = false;
				  clearGoalJudgeDistance();
			  }

			  if(goal_judge_flag == false && getSideSensorStatusR() == true && getGoalJudgeDistance() >= 120){
				  goal_judge_flag = true;
				  clearGoalJudgeDistance();
			  }
			  else if(goal_judge_flag == true && getGoalJudgeDistance() >= 120){
				  start_goal_line_cnt++;
				  goal_judge_flag = false;
				  clearGoalJudgeDistance();
			  }


			  if(start_goal_line_cnt >= 2){
				  stopLogging();
				  stopVelocityUpdate();
				  pattern = 20;
			  }


			  break;

		  case 20:
			  //setLED('B');

			  setTargetVelocity(0.0);
			  HAL_Delay(500);

			  stopVelocityControl();
			  stopLineTrace();

			  setDroneMotor(0, 0);

			  running_flag = false;
			  goal_flag = 1;

			  break;
		};

		if(getCouseOutFlag() == true){
			pattern = 20;
			stopLogging();
			stopVelocityUpdate();
		}

	}
}

void runningFlip()
{
	if(running_flag == true){
		updateTargetVelocity();

		if(isTargetDistance(10) == true){
			saveLog();
			if(isContinuousCurvature() == true){
				//continuous_curve_check_cnt = 0;
				continuous_curve_flag = true;
			}

			clearDistance10mm();
			clearTheta10mm();
		}

		//--- Cross Line Process ---//
		if(isCrossLine() == true && cross_line_ignore_flag == false){ //Cross line detect
			cross_line_ignore_flag = true;
			//side_line_ignore_flag = true;
			clearCrossLineIgnoreDistance();
			clearSideLineIgnoreDistance();

			if(mode == 1){
				correction_check_cnt_cross = 0;
				saveCross(getTotalDistance());
			}
			else{
				//correctionTotalDistanceFromCrossLine();
				//saveDebug(getTotalDistance());
			}
		}
		else if(cross_line_ignore_flag == true && getCrossLineIgnoreDistance() >= 50){ //50
			cross_line_ignore_flag = false;
		}

		//--- Side marker Process---//
		if(getSideSensorStatusR() == true){ //Right side line detect
			side_line_judge_flag = false;
			 clearSideLineJudgeDistance();
		}
		if(side_line_judge_flag== false && getSideSensorStatusL() == true && getSideLineJudgeDistance() >= 60){
			side_line_judge_flag= true;
			clearSideLineJudgeDistance();
		}
		else if(side_line_judge_flag == true && getSideLineJudgeDistance() >= 60){ //Detect side line
			 clearSideLineJudgeDistance();
			side_line_judge_flag= false;

			if(continuous_curve_flag == true){
				continuous_curve_flag = false;
				continuous_cnt_reset_flag = true;

				if(mode == 1){
					correction_check_cnt_side = 0;
					saveSide(getTotalDistance());
				}
				else{
					correctionTotalDistanceFromSideLine();
					//saveDebug(getTotalDistance());
				}
			}
		}


		// Debug LED //
		correction_check_cnt_cross++;
		if(correction_check_cnt_cross >= 10000) correction_check_cnt_cross = 10000;

		correction_check_cnt_side++;
		if(correction_check_cnt_side >= 10000) correction_check_cnt_side = 10000;

		continuous_curve_check_cnt++;
		if(continuous_curve_check_cnt >= 10000) continuous_curve_check_cnt = 10000;

		//if(correction_check_cnt_cross <= 150) setRGB('R');
		//else setRGB('r');
		//if(correction_check_cnt_side <= 150) setRGB('B');
		//else setRGB('b');
		if(continuous_curve_flag == true) setRGB('R');
		else setRGB('r');
	}

}

void runningInit()
{
	if(mode == 1){
		ereaseLog();
	}
	else{
		loadDistance();
		loadTheta();
		loadCross();
		loadSide();
		createVelocityTable();

		ereaseDebugLog();
	}

	clearCrossLineIgnoreDistance();
	clearSideLineIgnoreDistance();

	start_goal_line_cnt = 0;
	cross_line_ignore_flag = false;
	goal_judge_flag = false;
	side_line_judge_flag = false;
	continuous_cnt_reset_flag = true;
	continuous_curve_flag = false;
	running_flag = true;

	setDroneMotor(600, 600);
	HAL_Delay(500);
}

void saveLog(){
	if(logging_flag == true){
		saveDistance(getDistance10mm());
		saveTheta(getTheta10mm());
	}
	else if(velocity_update_flag == true){
		saveDebug(getTargetVelocity());
		saveDebug(getCurrentVelocity());
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

	cross_line_idx = 0;
	side_line_idx = 0;
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

	uint16_t log_size = getDistanceLogSize();

	uint16_t crossline_idx = 0;
	float total_distance = 0;
	for(uint16_t i = 0; i < log_size; i++){
		temp_distance = p_distance[i];
		temp_theta = p_theta[i];

		if(temp_theta == 0) temp_theta = 0.00001;
		float radius = fabs(temp_distance / temp_theta);
		if(radius >= 2000) radius = 2000;
		velocity_table[i] = radius2Velocity(radius);

		//Forced maximum speed on the crossline
		total_distance += temp_distance;
		float crossline_distance = getCrossLog(crossline_idx);
		if(crossline_distance + 60 >= total_distance && total_distance >= crossline_distance - 60){
			 velocity_table[i] = max_velocity;
		}

		if(total_distance >= crossline_distance + 60){
			crossline_idx++;
		}
	}
	for(uint16_t i = log_size; i < 6000; i++){
		velocity_table[i] = max_velocity;
	}

	addDecelerationDistanceMergin(velocity_table, 10);
	shiftVelocityTable(velocity_table, 5);

	decelerateProcessing(deceleration, p_distance);
	accelerateProcessing(acceleration, p_distance);

	velocity_table[0] = min_velocity;
}

float radius2Velocity(float radius){
	float velocity;

	if(mode == 2){
		velocity = radius * ((max_velocity - min_velocity) / 2000) + min_velocity;

		//if(radius < 1000) velocity = min_velocity;
		//else velocity = max_velocity;
	}
	else if(mode == 3){
		if(radius < 400) velocity = min_velocity;
		else if(radius < 500) velocity = 1.5;
		else if(radius < 650) velocity = 1.8;
		else if(radius < 1500) velocity = 2.0;
		else if(radius < 2000) velocity = 2.5;
		else velocity = max_velocity;

	}

	return velocity;
}

void decelerateProcessing(const float am, const float *p_distance){
	uint16_t log_size = getDistanceLogSize();
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
	uint16_t log_size = getDistanceLogSize();
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

void addDecelerationDistanceMergin(float *table, int16_t mergin_size)
{
	//setRGB('R');
	uint16_t idx = mergin_size;
	float pre_target_velocity = table[idx];

	while(idx <= 6000 - 1){
		if(pre_target_velocity > table[idx]){
			float low_velocity = table[idx];
			for(uint16_t i = idx - mergin_size; i < idx; i++){
				table[i] = low_velocity;
			}
			pre_target_velocity = table[idx];
		}

		pre_target_velocity = table[idx];

		idx++;
	}
	//setRGB('r');

}

void shiftVelocityTable(float *table, int16_t shitf_size)
{
	for(uint16_t i = shitf_size; i < 6000; i++){
		table[i - shitf_size] = table[i];
	}

	for(uint16_t i = 6000 - 1 - shitf_size; i < 6000; i++){
		table[i] = max_velocity;
	}


}

void updateTargetVelocity(){
	static float pre_target_velocity;

	if(velocity_update_flag == true){
		if(getTotalDistance() >= ref_distance){
			ref_distance += getDistanceLog(velocity_table_idx);
			velocity_table_idx++;
		}
		if(velocity_table_idx >= getDistanceLogSize()){
			velocity_table_idx = getDistanceLogSize() - 1;
		}

		setTargetVelocity(velocity_table[velocity_table_idx]);

		if(pre_target_velocity > velocity_table[velocity_table_idx]){
			setClearFlagOfVelocityControlI();
		}

		pre_target_velocity = velocity_table[velocity_table_idx];
	}
}

float getDebugVelocityTableValue(uint16_t idx)
{
	return velocity_table[idx];
}

void correctionTotalDistanceFromCrossLine()
{
	while(cross_line_idx <= getCrossLogSize()){
		float temp_crossline_distance = getCrossLog(cross_line_idx);
		float diff = fabs(temp_crossline_distance - getTotalDistance());
		if(diff <= 250){
			correction_check_cnt_cross = 0;
			setTotalDistance(temp_crossline_distance);
			cross_line_idx++;
			break;
		}
		cross_line_idx++;

		if(cross_line_idx >= getCrossLogSize()){
			cross_line_idx = getCrossLogSize() - 1;
			break;
		}
	}
}

void correctionTotalDistanceFromSideLine()
{
	while(side_line_idx <= getSideLogSize()){
		float temp_sideline_distance = getSideLog(side_line_idx);
		float diff = fabs(temp_sideline_distance - getTotalDistance());
		//if(diff <= 700){
		if(diff <= 250){
			correction_check_cnt_side = 0;
			setTotalDistance(temp_sideline_distance);
			side_line_idx++;
			break;
		}
		side_line_idx++;

		if(side_line_idx >= getSideLogSize()){
			side_line_idx = getSideLogSize() - 1;
			break;
		}
	}
}

void setVelocityRange(float min_vel, float max_vel)
{
	min_velocity = min_vel;
	max_velocity = max_vel;
}

void setAccDec(float acc, float dec)
{
	acceleration = acc;
	deceleration = dec;
}
