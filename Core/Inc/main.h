/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LineChase.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_R_Pin GPIO_PIN_13
#define LED_R_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_14
#define LED_G_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_15
#define LED_B_GPIO_Port GPIOC
#define BATTERY_ADC_Pin GPIO_PIN_1
#define BATTERY_ADC_GPIO_Port GPIOC
#define SIDE_MARKER1_Pin GPIO_PIN_2
#define SIDE_MARKER1_GPIO_Port GPIOC
#define SIDE_MARKER2_Pin GPIO_PIN_3
#define SIDE_MARKER2_GPIO_Port GPIOC
#define DRONE_MOTOR_PWM1_Pin GPIO_PIN_10
#define DRONE_MOTOR_PWM1_GPIO_Port GPIOB
#define DRONE_MOTOR_PWM2_Pin GPIO_PIN_11
#define DRONE_MOTOR_PWM2_GPIO_Port GPIOB
#define DRONE_MOTOR_PWM4_Pin GPIO_PIN_14
#define DRONE_MOTOR_PWM4_GPIO_Port GPIOB
#define DRONE_MOTOR_PWM3_Pin GPIO_PIN_15
#define DRONE_MOTOR_PWM3_GPIO_Port GPIOB
#define DRIVE_MOTOR1_PWM2_Pin GPIO_PIN_6
#define DRIVE_MOTOR1_PWM2_GPIO_Port GPIOC
#define DRIVE_MOTOR1_PWM1_Pin GPIO_PIN_7
#define DRIVE_MOTOR1_PWM1_GPIO_Port GPIOC
#define DRIVE_MOTOR2_PWM2_Pin GPIO_PIN_8
#define DRIVE_MOTOR2_PWM2_GPIO_Port GPIOC
#define DRIVE_MOTOR2_PWM1_Pin GPIO_PIN_9
#define DRIVE_MOTOR2_PWM1_GPIO_Port GPIOC
#define SWITCH2_Pin GPIO_PIN_8
#define SWITCH2_GPIO_Port GPIOA
#define SWITCH1_Pin GPIO_PIN_12
#define SWITCH1_GPIO_Port GPIOA
#define FAN_MOTOR_PWM_Pin GPIO_PIN_15
#define FAN_MOTOR_PWM_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_2
#define SPI_CS_GPIO_Port GPIOD
#define ENCODER1_A_Pin GPIO_PIN_4
#define ENCODER1_A_GPIO_Port GPIOB
#define ENCODER1_B_Pin GPIO_PIN_5
#define ENCODER1_B_GPIO_Port GPIOB
#define ENCODER2_A_Pin GPIO_PIN_6
#define ENCODER2_A_GPIO_Port GPIOB
#define ENCODER2_B_Pin GPIO_PIN_7
#define ENCODER2_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
