/*
 * Running.c
 *
 *  Created on: Jan 28, 2023
 *      Author: Haruki SHIMOTORI
 */

#include "Running.h"

uint8_t mon_is_crossline;

static uint8_t start_goal_line_cnt;

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

void running(void)
{
	uint8_t goal_flag = 0;
	uint16_t pattern = 0;

	startLineTrace();
	startVelocityControl();
	setTargetVelocity(0.5);
	//setMotor(300, 300);
	runningInit();

	while(goal_flag == 0){
		switch(pattern){
		  case 0:
			  if(start_goal_line_cnt == 1) pattern = 10;

			  break;

		  case 10:
			  HAL_Delay(0);
			  pattern = 20;

			  break;


		  case 20:
			  if(start_goal_line_cnt == 2){
				  HAL_Delay(100);
				  pattern = 30;
			  }

			  break;

		  case 30:
			  setTargetVelocity(0.0);
			  //goal_flag = 1;

			  break;
		};
	}
}

void runningFlip()
{
	static uint8_t cross_line_ignore_flag;
	static uint8_t side_line_ignore_flag;

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
