/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

extern volatile uint32_t polarity_fault;
extern volatile uint32_t tim1_running;

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
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define STLINK_TX_Pin GPIO_PIN_2
#define STLINK_TX_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_3
#define STLINK_RX_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

#define TIM1_CH1_GPIO_Port GPIOA
#define TIM1_CH1_Pin  GPIO_PIN_8
#define TIM1_CH2_GPIO_Port GPIOA
#define TIM1_CH2_Pin  GPIO_PIN_9
#define TIM1_CH3_GPIO_Port GPIOB
#define TIM1_CH3_Pin  GPIO_PIN_6
#define TIM1_CH4_GPIO_Port GPIOC
#define TIM1_CH4_Pin  GPIO_PIN_11


#define TIM1_PERIOD		(64000)
#define TIM1_CCR1_RISE	(    0)
#define TIM1_CCR2_RISE	( 8000)
#define TIM1_CCR3_RISE	(16000)
#define TIM1_CCR4_RISE	(24000)
#define TIM1_CCR1_FALL	(TIM1_CCR1_RISE + 3200)
#define TIM1_CCR2_FALL	(TIM1_CCR2_RISE + 3200)
#define TIM1_CCR3_FALL	(TIM1_CCR3_RISE + 3200)
#define TIM1_CCR4_FALL	(TIM1_CCR4_RISE + 3200)


#define TIM1_CCR1_FAULT	(0x01)
#define TIM1_CCR2_FAULT	(0x02)
#define TIM1_CCR3_FAULT	(0x04)
#define TIM1_CCR4_FAULT	(0x08)


#define IS_GPIO_PIN_HIGH(PORT, PIN)  ( ((PORT)->IDR & (PIN)) == (PIN) )
#define IS_GPIO_PIN_LOW(PORT, PIN)   ( ((PORT)->IDR & (PIN)) == (0x0UL) )

void show_regs(uint32_t base, uint32_t len);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
