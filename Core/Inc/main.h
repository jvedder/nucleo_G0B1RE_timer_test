/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g0xx_hal.h"

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
#define BTN_USER_Pin GPIO_PIN_13
#define BTN_USER_GPIO_Port GPIOC

#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOB

#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOB

#define STLINK_TX_Pin GPIO_PIN_2
#define STLINK_TX_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_3
#define STLINK_RX_GPIO_Port GPIOA

#define STB1_TIM1_CH1_Pin GPIO_PIN_8
#define STB1_TIM1_CH1_GPIO_Port GPIOA

#define STB2_TIM1_CH3_Pin GPIO_PIN_10
#define STB2_TIM1_CH3_GPIO_Port GPIOA

#define STB3_TIM2_CH1_Pin GPIO_PIN_4
#define STB3_TIM2_CH1_GPIO_Port GPIOC

#define STB4_TIM2_CH3_Pin GPIO_PIN_10
#define STB4_TIM2_CH3_GPIO_Port GPIOB

#define STB5_TIM3_CH1_Pin GPIO_PIN_4
#define STB5_TIM3_CH1_GPIO_Port GPIOB

#define STB6_TIM3_CH3_Pin GPIO_PIN_0
#define STB6_TIM3_CH3_GPIO_Port GPIOB

#define STB7_TIM4_CH1_Pin GPIO_PIN_6
#define STB7_TIM4_CH1_GPIO_Port GPIOB

#define STB8_TIM15_CH1_Pin GPIO_PIN_1
#define STB8_TIM15_CH1_GPIO_Port GPIOC

#define MCO_OUT_Pin GPIO_PIN_15
#define MCO_OUT_GPIO_Port GPIOA

#define MCO_IN_Pin GPIO_PIN_0
#define MCO_IN_GPIO_Port GPIOF

#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA







/* USER CODE BEGIN Private defines */

/**
 * TIM1 Clock Definitions
 **/

/* TIM1 GPIOs Ports/Pins */
#define TIM1_CH1_GPIO_Port GPIOA
#define TIM1_CH1_Pin  GPIO_PIN_8
#define TIM1_CH2_GPIO_Port GPIOA
#define TIM1_CH2_Pin  GPIO_PIN_9
#define TIM1_CH3_GPIO_Port GPIOB
#define TIM1_CH3_Pin  GPIO_PIN_6
#define TIM1_CH4_GPIO_Port GPIOA
#define TIM1_CH4_Pin  GPIO_PIN_11


/**
 * TIM2 Clock Definitions
 **/

/* TIM1 GPIOs Ports/Pins */
#define TIM2_CHA_Pin GPIO_PIN_2
#define TIM2_CHA_GPIO_Port GPIOB
#define TIM2_CHB_Pin GPIO_PIN_3
#define TIM2_CHB_GPIO_Port GPIOB
#define TIM2_CHC_Pin GPIO_PIN_4
#define TIM2_CHC_GPIO_Port GPIOB
#define TIM2_CHD_Pin GPIO_PIN_5
#define TIM2_CHD_GPIO_Port GPIOB




/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
