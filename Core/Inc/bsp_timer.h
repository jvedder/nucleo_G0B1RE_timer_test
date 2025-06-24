/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    bsp_timer.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion */
#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "main.h"

void BSP_Timer_Init(void);
void BSP_Timer_Start(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_TIMER_H__ */

