/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* TODO: Parameterize this repetitive code */

  /* If CH1 caused the interrupt */
  if (TIM1->SR & TIM_SR_CC1IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR1 == TIM1_CCR1_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR1 = TIM1_CCR1_FALL;

		  /* fault if GPIO pin did not rise */
		  if (IS_GPIO_PIN_LOW(TIM1_CH1_GPIO_Port, TIM1_CH1_Pin))
		  {
			  polarity_fault |= TIM1_CCR1_FAULT;
		  }
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR1 = TIM1_CCR1_RISE;

		  /* fault if GPIO pin did not fall */
		  if (IS_GPIO_PIN_HIGH(TIM1_CH1_GPIO_Port, TIM1_CH1_Pin))
		  {
			  polarity_fault |= TIM1_CCR1_FAULT;
		  }
	  }
	  /* clear CC1IF */
	  TIM1->SR = ~(TIM_SR_CC1IF);
  }

  /* If CH2 caused the interrupt */
  if (TIM1->SR & TIM_SR_CC2IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR2 == TIM1_CCR2_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR2 = TIM1_CCR2_FALL;

		  /* fault if GPIO pin did not rise */
		  if (IS_GPIO_PIN_LOW(TIM1_CH2_GPIO_Port, TIM1_CH2_Pin))
		  {
			  polarity_fault |= TIM1_CCR2_FAULT;
		  }
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR2 = TIM1_CCR2_RISE;

		  /* fault if GPIO pin did not fall */
		  if (IS_GPIO_PIN_HIGH(TIM1_CH2_GPIO_Port, TIM1_CH2_Pin))
		  {
			  polarity_fault |= TIM1_CCR2_FAULT;
		  }
	  }
	  /* clear CC2IF */
	  TIM1->SR = ~(TIM_SR_CC2IF);
  }

  /* If CH3 caused the interrupt */
  if (TIM1->SR & TIM_SR_CC3IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR3 == TIM1_CCR3_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR3 = TIM1_CCR3_FALL;

		  /* fault if GPIO pin did not rise */
		  if (IS_GPIO_PIN_LOW(TIM1_CH3_GPIO_Port, TIM1_CH3_Pin))
		  {
			  polarity_fault |= TIM1_CCR3_FAULT;
		  }
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR3 = TIM1_CCR3_RISE;

		  /* fault if GPIO pin did not fall */
		  if (IS_GPIO_PIN_HIGH(TIM1_CH3_GPIO_Port, TIM1_CH3_Pin))
		  {
			  polarity_fault |= TIM1_CCR3_FAULT;
		  }
	  }
	  /* clear CC3IF */
	  TIM1->SR = ~(TIM_SR_CC3IF);
  }

  /* If CH4 caused the interrupt */
  if (TIM1->SR & TIM_SR_CC4IF)
  {
	  /* Toggle the timer value */
	  /* toggle the timer value */
	  if (TIM1->CCR4 == TIM1_CCR4_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR4 = TIM1_CCR4_FALL;

		  /* fault if GPIO pin did not rise */
		  if (IS_GPIO_PIN_LOW(TIM1_CH4_GPIO_Port, TIM1_CH4_Pin))
	      {
			  polarity_fault |= TIM1_CCR4_FAULT;
	      }

	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR4 = TIM1_CCR4_RISE;

		  /* fault if GPIO pin did not fall */
		  if (IS_GPIO_PIN_HIGH(TIM1_CH4_GPIO_Port, TIM1_CH4_Pin))
		  {
			  polarity_fault |= TIM1_CCR4_FAULT;
		  }
	  }
	  /* clear CC4IF */
	  TIM1->SR = ~(TIM_SR_CC4IF);
  }


  /* USER CODE END TIM1_CC_IRQn 0 */
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
