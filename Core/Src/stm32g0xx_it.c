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

  if (TIM1->SR & TIM_SR_CC1IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR1 == CCR1_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR1 = CCR1_FALL;

		  /* fault if GPIO PA8 did not rise */
		  if (IS_GPIO_PIN_LOW(GPIOA, 8)) polarity_fault = 1;
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR1 = CCR1_RISE;

		  /* fault if GPIO PA8 did not fall */
		  if (IS_GPIO_PIN_HIGH(GPIOA, 8)) polarity_fault = 1;
	  }
	  /* clear CC1IF */
	  TIM1->SR = ~(TIM_SR_CC1IF);
  }

  if (TIM1->SR & TIM_SR_CC2IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR2 == CCR2_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR2 = CCR2_FALL;

		  /* fault if GPIO PA9 did not rise */
		  if (IS_GPIO_PIN_LOW(GPIOA, 9)) polarity_fault = 2;
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR2 = CCR2_RISE;

		  /* fault if GPIO PA9 did not fall */
		  if (IS_GPIO_PIN_HIGH(GPIOA, 9)) polarity_fault = 2;
	  }
	  /* clear CC2IF */
	  TIM1->SR = ~(TIM_SR_CC2IF);
  }

  if (TIM1->SR & TIM_SR_CC3IF)
  {
	  /* toggle the timer value */
	  if (TIM1->CCR3 == CCR3_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR3 = CCR3_FALL;

		  /* fault if GPIO PB6 did not rise */
		  if (IS_GPIO_PIN_LOW(GPIOB, 6)) polarity_fault = 3;
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR3 = CCR3_RISE;

		  /* fault if GPIO PB6 did not fall */
		  if (IS_GPIO_PIN_HIGH(GPIOB, 6)) polarity_fault = 3;
	  }
	  /* clear CC3IF */
	  TIM1->SR = ~(TIM_SR_CC3IF);
  }

  if (TIM1->SR & TIM_SR_CC4IF)
  {
	  /* Toggle the timer value */
	  /* toggle the timer value */
	  if (TIM1->CCR4 == CCR4_RISE)
	  {
		  /* set up the falling edge time */
		  TIM1->CCR4 = CCR4_FALL;

		  /* fault if GPIO PC11 did not rise */
		  if (IS_GPIO_PIN_LOW(GPIOC, 11)) polarity_fault = 4;

		  /* DEBUG: record how long this took */
		  ccr4_rise_isr_time = TIM1->CNT;
	  }
	  else
	  {
		  /* set up the rising edge time */
		  TIM1->CCR4 = CCR4_RISE;

		  /* fault if GPIO PC11 did not fall */
		  if (IS_GPIO_PIN_HIGH(GPIOC, 11)) polarity_fault = 4;

		  /* DEBUG: record how long this took */
		  ccr4_fall_isr_time = TIM1->CNT;
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
