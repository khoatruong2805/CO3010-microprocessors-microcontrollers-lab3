/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define REDns_Pin GPIO_PIN_1
#define REDns_GPIO_Port GPIOA
#define GREENns_Pin GPIO_PIN_2
#define GREENns_GPIO_Port GPIOA
#define YELLOWns_Pin GPIO_PIN_3
#define YELLOWns_GPIO_Port GPIOA
#define REDwe_Pin GPIO_PIN_4
#define REDwe_GPIO_Port GPIOA
#define GREENwe_Pin GPIO_PIN_5
#define GREENwe_GPIO_Port GPIOA
#define YELLOWwe_Pin GPIO_PIN_6
#define YELLOWwe_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_8
#define SEG0_GPIO_Port GPIOA
#define SEG1_Pin GPIO_PIN_9
#define SEG1_GPIO_Port GPIOA
#define SEG2_Pin GPIO_PIN_10
#define SEG2_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_11
#define SEG3_GPIO_Port GPIOA
#define SEG4_Pin GPIO_PIN_12
#define SEG4_GPIO_Port GPIOA
#define SEG5_Pin GPIO_PIN_13
#define SEG5_GPIO_Port GPIOA
#define SEG6_Pin GPIO_PIN_14
#define SEG6_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_0
#define EN0_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_1
#define EN1_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_2
#define EN2_GPIO_Port GPIOB
#define EN3_Pin GPIO_PIN_3
#define EN3_GPIO_Port GPIOB
#define BT0_Pin GPIO_PIN_5
#define BT0_GPIO_Port GPIOB
#define BT1_Pin GPIO_PIN_6
#define BT1_GPIO_Port GPIOB
#define BT2_Pin GPIO_PIN_7
#define BT2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
