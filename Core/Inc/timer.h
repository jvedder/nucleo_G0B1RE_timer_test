/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion */
#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "main.h"

void TIM1_Init(void);
void TIM1_GPIO_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H__ */

