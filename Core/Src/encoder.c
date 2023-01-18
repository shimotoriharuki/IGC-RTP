/*
 * encoder.c
 *
 *  Created on: Jan 18, 2023
 *      Author: ryuku
 */

#include "encoder.h"

int16_t enc_l_cnt, enc_r_cnt, enc_l_total, enc_r_total;

void getEncoder(void){

	enc_r_cnt = TIM3 -> CNT;
	enc_l_cnt = TIM4 -> CNT;

	TIM3 -> CNT = 0;
	TIM4 -> CNT = 0;

	enc_l_total = enc_l_total + enc_l_cnt;
	enc_r_total = enc_r_total - enc_r_cnt;
}
