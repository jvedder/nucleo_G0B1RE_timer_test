/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    bsp_TIM2.c
 * @brief   This file provides code for the configuration
 *          of the TIM2 instances.
 ******************************************************************************
 */
/* Includes */
#include <bsp_timer.h>

/* Prototypes */
void TIM1_GPIO_Init( void );

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

    /* CNT: Counter Register - reset */
    TIM2->CNT = 0x0000;

    /* Slave Mode Control Register
     * Delay TIM2 tigger out to synchronize timers 
	 * 
	 * MSM = 1 TRGI) is delayed to allow a perfect synchronization between 
	 * the current timer and its slaves (through TRGO
     */
    TIM2->SMCR = (0b1 << TIM_SMCR_MSM_Pos);
    /* Timer period.
     * TIM2 clock is 64 MHz.
     * For a 1 ms period, set timer period to 64M MHz * 1 mS = 64,000.
     */
    TIM2->ARR = 64000;      // period is 1 ms
    TIM2->PSC = (1 - 1);    // Prescaler = 1
    TIM2->RCR = 0;          // repetition counter

    /* Capture/Compare Mode Register 1
     *
     * Set Output Compare Mode for CH1 as rise on CCR1 and fall on CCR2.
     * CH2 output is not used.
     * OC1CE = 0: OC1Ref is not affected by the ETRF input
     * OC2CE = 0: OC2Ref is not affected by the ETRF input
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
    TIM2->CCMR1 = (0b1101 << TIM_CCMR1_OC1M_Pos) | (0b0110 << TIM_CCMR1_OC2M_Pos);
    TIM2->CCMR1 = 0x0000;
    /* Capture/compare registers
     * Set the rise (CCR1) and fall (CCR2) positions
     * */
    TIM2->CCR1 = 16000;  
    TIM2->CCR2 = 16000 + 640;  // 10uS pulse width
	TIM2->CCR3 = 48000;  
    TIM2->CCR4 = 48000 + 640;  // 10uS pulse width
	

    /* Disable interrupts  */
    TIM2->DIER = 0x0;

    /* Capture/Compare Enable Register */
    TIM2->CCER = TIM_CCER_CC1E;

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
