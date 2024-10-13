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
#define MCO_IN_Pin GPIO_PIN_0
#define MCO_IN_GPIO_Port GPIOF
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

/* Set TIM1 ticks = 64MHz / 16 = 4MHz */
#define TIM1_PRESCALER (16u)
/* TIM1 Period is 1 mS (Caution:16-bit value) */
#define TIM1_PERIOD     (4000u)
/* Distribute strobes equally over first 1 mS (4000 ticks) */
#define TIM1_CCR1_RISE  ( 500)
#define TIM1_CCR2_RISE  (1500)
#define TIM1_CCR3_RISE  (2500)
#define TIM1_CCR4_RISE  (3500)
/* IR Pulse width is 25 uS */
#define TIM_IR_PULSE_WIDTH (100)

#define TIM1_CCR1_FALL  (TIM1_CCR1_RISE + TIM_IR_PULSE_WIDTH)
#define TIM1_CCR2_FALL  (TIM1_CCR2_RISE + TIM_IR_PULSE_WIDTH)
#define TIM1_CCR3_FALL  (TIM1_CCR3_RISE + TIM_IR_PULSE_WIDTH)
#define TIM1_CCR4_FALL  (TIM1_CCR4_RISE + TIM_IR_PULSE_WIDTH)

#define TIM1_CCR1_FAULT (0x01)
#define TIM1_CCR2_FAULT (0x02)
#define TIM1_CCR3_FAULT (0x04)
#define TIM1_CCR4_FAULT (0x08)

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

/* TIM2 is same as TIM1 */
#define TIM2_PRESCALER  TIM1_PRESCALER
#define TIM2_PERIOD     TIM1_PERIOD

#define TIM2_CCR1_TOGGLE  (   0)
#define TIM2_CCR2_TOGGLE  (1000)
#define TIM2_CCR3_TOGGLE  (2000)
#define TIM2_CCR4_TOGGLE  (3000)

#define TIM2_CCR1_FAULT (0x01)
#define TIM2_CCR2_FAULT (0x02)
#define TIM2_CCR3_FAULT (0x04)
#define TIM2_CCR4_FAULT (0x08)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
