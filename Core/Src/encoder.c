/*
 * Rncoder.c
 *
 *  Created on: Jan 18, 2023
 *      Author: ryuku, Haruki SHIMOTORI
 */

#include <Encoder.h>

#define MAX_ENCODER_CNT 65535
#define CNT_OFFSET 32768

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

int16_t enc_l_cnt, enc_r_cnt, enc_l_total, enc_r_total;
int32_t enc_total, enc_mm_cnt;

void initEncoder(void)
{
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);	//encoder start
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);	//encoder start
	TIM3 -> CNT = CNT_OFFSET;
	TIM4 -> CNT = CNT_OFFSET;
}

void updateEncoderCnt(void)
{
	enc_l_cnt = TIM4 -> CNT - CNT_OFFSET;
	enc_r_cnt = CNT_OFFSET - TIM3 -> CNT;

	enc_l_total += enc_l_cnt;
	enc_r_total += enc_r_cnt;
	enc_total = (enc_l_total + enc_r_total) / 2;
	//15.73カウントで1ｍｍ
}

void resetEncoderCnt(void)
{
	TIM3 -> CNT = CNT_OFFSET;
	TIM4 -> CNT = CNT_OFFSET;
}
