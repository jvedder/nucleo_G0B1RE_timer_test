/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 */
/* Includes */
#include <timer.h>

/**
 * @brief  Initialize and start TIM1.
 *
 * Initialize TIM1 registers, configure GPIO, enable TIM1 interrupts, and
 * start TIM1 to output staggered 100 us pulses on CH1 through CH4 every 2 ms.
 *
 * @retval none
 */
void TIM1_Init( void )
{
    /*
     * Configure TIM1
     */

    /* Initializes the peripherals clocks */

    /* Configure the TIM1 clock source */
    __HAL_RCC_TIM1_CONFIG( RCC_PERIPHCLK_TIM1 );

    /* Enable PLLQCLK output */
    __HAL_RCC_PLLCLKOUT_ENABLE( RCC_PLLQCLK );

    /* enable TIM1 clock */
    __HAL_RCC_TIM1_CLK_ENABLE( );

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority( TIM1_CC_IRQn, 0, 0 );
    HAL_NVIC_EnableIRQ( TIM1_CC_IRQn );

    /* Force a hard reset of TIM1 */
    __HAL_RCC_TIM1_FORCE_RESET( );
    HAL_Delay( 1 );
    __HAL_RCC_TIM1_RELEASE_RESET( );

    /* reset timer counter (not sure this is needed :-) */
    TIM1->CNT = 0x0000;

    /*set the timer period */
    TIM1->ARR = TIM1_PERIOD;
    TIM1->PSC = 1;
    TIM1->RCR = 0;

    /* Set Output Compare Toggle Mode for all 4 channels:
     *
     * OCxCE = 0: OCxRef is not affected by the ocref_clr_int signal
     * OCxM  = 0011: Toggle - OCxREF toggles when TIM_CNT=TIM_CCRx,
     * OCxPE = 0: Preload register on TIMx_CCRx disabled. TIMx_CCRx can be written at anytime.
     * OCxFE = 0: Output Compare fast enable is off
     * CCxS  = 00: CCx channel is configured as output
     **/
    TIM1->CCMR1 = 0x3030;
    TIM1->CCMR2 = 0x3030;

    /* Set the initial strobe positions */
    TIM1->CCR1 = TIM1_CCR1_RISE;
    TIM1->CCR2 = TIM1_CCR2_RISE;
    TIM1->CCR3 = TIM1_CCR3_RISE;
    TIM1->CCR4 = TIM1_CCR4_RISE;

    /* Enable CC1 thru CC4  interrupts  */
    TIM1->DIER = ( TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE
            | TIM_DIER_CC4IE );

    /* Enable CC1 thru CC4 outputs */
    TIM1->CCER =
            ( TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E );

    /* Enable Main Output Enable (MOE) and define off state on outputs  */
    TIM1->BDTR = ( TIM_BDTR_MOE | TIM_BDTR_OSSR | TIM_BDTR_OSSI );

    /* Generate an update event to reload registers now */
    TIM1->EGR = TIM_EGR_UG;

    /* Configure the TIM1 GPIOs */
    TIM1_GPIO_Init( );

    /* Clear all prior interrupts (write 0 to clear)*/
    TIM1->SR = 0x0000;

    /* Start the timer as an up count timer with auto-preload is not buffered */
    TIM1->CR1 = TIM_CR1_CEN;
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
    __HAL_RCC_GPIOC_CLK_ENABLE( );
    __HAL_RCC_GPIOA_CLK_ENABLE( );
    __HAL_RCC_GPIOB_CLK_ENABLE( );

    /* TIM_CH1 and TIM1_CH2 = PA8 and PA9 */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
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

    /* TIM1_CH1 = PC11 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
}
