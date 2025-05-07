/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    bsp_timer.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 */
/* Includes */
#include "bsp_timer.h"

/* Prototypes */
void TIM1_GPIO_Init( void );
void TIM2_GPIO_Init( void );

/**
 * @brief  Initialize and start TIM1.
 *
 * Red LED: Use TIM1 with CH1 on at CCR1 (25%) and off at CCR2 (75%).
 * Use complementary outputs (CH1, CH1N) for 2 of opposite phase.
 *
 * TIM1 starts when TIM2 starts--TIM1 is slave to TIM2.
 *
 * @retval none
 */
void BSP_TIM1_Init( void )
{
    /*
     * Configure TIM1
     */

    /* Enable TIM1 clock */
    __HAL_RCC_TIM1_CLK_ENABLE( );

    /* CNT: Counter Register - reset */
    TIM1->CNT = 0x0000;

    /* Slave Mode Control Register
     * Set TIM1 as slave to TIM2 (ITR1). TIM1 starts on trigger of TIM2.
     *
     * SMS[3:0] = 0111 External Clock Mode - Rising edges of the selected trigger (TRGI) clock the counter
     * TS[4:0] = 00001 Trigger Selection = Internal Trigger 1 (ITR1) = TIM2
     */
    TIM1->SMCR = (0b0111 << TIM_SMCR_SMS_Pos) | (0b00001 << TIM_SMCR_TS_Pos)

    /* Timer period.
     * TIM1 clock mux is set to TPCLK, which is 64 MHz.
     * For a 1 ms period, set timer period to 64M MHz * 1 mS = 64,000.
     */
    TIM1->ARR = 64000;      // period is 1 ms
    TIM1->PSC = (1 - 1);    // Prescaler = 1
    TIM1->RCR = 0;          // repetition counter

    /* Capture/Compare Mode Register 1
     *
     * Set Output Compare Mode for CH1 as rise on CCR1 and fall on CCR2.
     * CH2 output is not used.
     *
     * OCxCE = 0: OCxRef is not affected by the ocref_clr_int signal
     * OC1M  = 1101: Combined PWM mode 2 - OC1REF has the same behavior as in PWM mode 2.
     *               OC1REFC is the logical AND between OC1REF and OC2REF.
     *               PWM mode 2 in upcounting, channel 1 is inactive as long as
     *               TIM1_CNT<TIM1_CCR1 else active.
     * OC2M  = 0110: PWM mode 1 - In upcounting, channel 2 is active as long as
     *               TIM1_CNT<TIM1_CCR2 else inactive.
     * OCxPE = 0: Preload register on CCRx disabled. CCRx can be written at any time.
     * OCxFE = 0: Output Compare fast enable is off
     * CCxS  = 00: CCx channel is configured as output
     **/
    TIM1->CCMR1 = (0b1101 << TIM_CCMR1_OC1M_Pos) | (0b0110 << TIM_CCMR1_OC2M_Pos);

    /* Capture/Compare Mode Register 2
     * CH3 & CH4 are unused.
     */
    TIM1->CCMR2 = 0x0000;

    /* Capture/compare registers
     * Set the rise (CCR1) and fall (CCR2) positions
     * */
    TIM1->CCR1 = 16000;  // 25% of period;
    TIM1->CCR2 = 48000;  // 75% of period;

    /* Disable interrupts  */
    TIM1->DIER = 0x0;

    /* Capture/Compare Enable Register */
    TIM1->CCER = TIM_CCER_CC1E;

    /* Enable Main Output Enable (MOE) and define off state on outputs  */
    TIM1->BDTR = ( TIM_BDTR_MOE | TIM_BDTR_OSSR | TIM_BDTR_OSSI );

    /* Generate an update event to reload registers now */
    TIM1->EGR = TIM_EGR_UG;

    /* Configure the GPIOs */
    TIM1_GPIO_Init( );

    /* Clear all prior interrupts (write 0 to clear) */
    TIM1->SR = 0x0000;

    /* Start the timer as an up count timer with auto-preload is not buffered */
    TIM1->CR1 = TIM_CR1_CEN;
}

/**
 * @brief  Initialize and start TIM2.
 *
 * NIR: Use TIM2 for 2 fast strobes each. The 2 strobes are on at
 * CCR1/CCR3 and off at CCR2/CCR4.
 *
 * @retval none
 */
void BSP_TIM2_Init( void )
{
    /* Enable TIM2 clock */
    __HAL_RCC_TIM2_CLK_ENABLE( );

    /* reset timer counter (not sure this is needed :-) */
    TIM2->CNT = 0x0000;

    /*set the timer period */
    TIM2->ARR = 64000000;  // Persiod = 1 sec witrh 64 MHz CLock
    TIM2->PSC = 0;  // PRESCALER = 1;
    TIM2->RCR = 0;

    /* Set Output Compare Toggle Mode for all 4 channels:
     *
     * OCxCE = 0: OCxRef is not affected by the ocref_clr_int signal
     * OCxM  = 0000: Frozen TIM_CNT = TIM_CCRx has no effect on outputs.
     * OCxPE = 0: Preload register on TIMx_CCRx disabled. TIMx_CCRx can be written at anytime.
     * OCxFE = 0: Output Compare fast enable is off
     * CCxS  = 00: CCx channel is configured as output
     **/
    TIM2->CCMR1 = 0x0000;
    TIM2->CCMR2 = 0x0000;

    /* Set the toggle positions */
    TIM2->CCR1 = TIM2_CCR1_TOGGLE;
    TIM2->CCR2 = TIM2_CCR2_TOGGLE;
    TIM2->CCR3 = TIM2_CCR3_TOGGLE;
    TIM2->CCR4 = TIM2_CCR4_TOGGLE;

    /* Enable CC1 thru CC4  interrupts  */
    TIM2->DIER = ( TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE
            | TIM_DIER_CC4IE );

    /* Disable CC1 thru CC4 outputs */
    TIM2->CCER = 0x0000;

    /* Enable Main Output Enable (MOE) and define off state on outputs  */
    TIM2->BDTR = ( TIM_BDTR_MOE | TIM_BDTR_OSSR | TIM_BDTR_OSSI );

    /* Generate an update event to reload registers now */
    TIM2->EGR = TIM_EGR_UG;

    /* Configure the GPIOs */
    TIM2_GPIO_Init( );

    /* Clear all prior interrupts (write 0 to clear) */
    TIM2->SR = 0x0000;

    /*
     * Set the Master Mode Selection  MMS[2:0]:
     * MMS[2:0] = 010: Update - The update event is selected as trigger
     * output (TRGO). For instance a master timer can then be used as a
     * prescaler for a slave timer.
     */
    TIM2->CR2 = 0x20;

    /* Start the timer as an up count timer with auto-preload is not buffered */
    TIM2->CR1 = TIM_CR1_CEN;
}

/* Configures the TIM1 GPIO outputs */
void TIM1_GPIO_Init( void )
{
    /**
     * TIM1 GPIO Configuration
     * PA8  = TIM1_CH1
     * PA9  = TIM1_CH2
     * PB6  = TIM1_CH3
     * PC11 = TIM1_CH4
     */
    GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };
    __HAL_RCC_GPIOA_CLK_ENABLE( );
    __HAL_RCC_GPIOB_CLK_ENABLE( );

    /* TIM_CH1, TIM1_CH2, TIM1_CH4 = PA8, PA9, PA11 */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    /* TIM_CH3 = PB6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );
}

/* Configures the TIM2 GPIO outputs */
void TIM2_GPIO_Init( void )
{
    GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE( );

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin( GPIOB,
    TIM2_CHA_Pin | TIM2_CHB_Pin | TIM2_CHC_Pin | TIM2_CHD_Pin, GPIO_PIN_RESET );

    /* TIM2_CHA, TIM2_CHB, TIM2_CHC, TIM2_CHD = PB2, PB3, PB4, PB5 */
    GPIO_InitStruct.Pin = TIM2_CHA_Pin | TIM2_CHB_Pin | TIM2_CHC_Pin
            | TIM2_CHD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );
}
