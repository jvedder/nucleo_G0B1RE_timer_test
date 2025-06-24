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

/**
 *  Defines
 */

/* The APB clock for the timers (TPCLK) is 64 MHz. */
/* Set TIM ticks = 64MHz / 16 = 4MHz */
#define TIM_PRESCALER (16u)

/* TIM Period is 1 mS at 4 MHz (Caution:16-bit value) */
#define TIM_PERIOD     (4000u)

/* Distribute strobes on times over the 1 mS (4000 ticks) */
#define TIM_STROBE1_ON  ( 500u)
#define TIM_STROBE2_ON  (1500u)
#define TIM_STROBE3_ON  (2500u)
#define TIM_STROBE4_ON  (3500u)

#define TIM_STROBE5_ON  (   0u)
#define TIM_STROBE6_ON  ( 667u)
#define TIM_STROBE7_ON  (1333u)
#define TIM_STROBE8_ON  (2000u)

/* IR Pulse width is 25 uS per 1 mS (2.5%) */
#define TIM_IR_PULSE_WIDTH (100u)

/* RED Pulse width is 500 uS per 1 mS (50%) */
#define TIM_RED_PULSE_WIDTH (2000u)

/* Strobe Turn Off Times */
#define TIM_STROBE1_OFF  (TIM_STROBE1_ON + TIM_IR_PULSE_WIDTH)
#define TIM_STROBE2_OFF  (TIM_STROBE2_ON + TIM_IR_PULSE_WIDTH)
#define TIM_STROBE3_OFF  (TIM_STROBE3_ON + TIM_IR_PULSE_WIDTH)
#define TIM_STROBE4_OFF  (TIM_STROBE4_ON + TIM_IR_PULSE_WIDTH)

#define TIM_STROBE5_OFF  (TIM_STROBE5_ON + TIM_RED_PULSE_WIDTH)
#define TIM_STROBE6_OFF  (TIM_STROBE6_ON + TIM_RED_PULSE_WIDTH)
#define TIM_STROBE7_OFF  (TIM_STROBE7_ON + TIM_RED_PULSE_WIDTH)
#define TIM_STROBE8_OFF  (TIM_STROBE8_ON + TIM_RED_PULSE_WIDTH)

/* Types */
typedef enum OutputCount
{
    SINGLE, DUAL
} OutputCount_t;

/* Prototypes */
static void Timer_Init( TIM_TypeDef *tim, OutputCount_t out );
static void Timer_GPIO_Init( void );

/*
 * Public Methods
 */

/**
 * @brief  Configures (but does not start) the 5 timers used for
 * generating 8 strobes. The timers are (TIM1, TIM2, TIM3, TIM4,
 * and TIM15.
 *
 * @retval none
 */
void BSP_Timer_Init( void )
{
    __HAL_RCC_TIM1_CLK_ENABLE( );
    __HAL_RCC_TIM2_CLK_ENABLE( );
    __HAL_RCC_TIM3_CLK_ENABLE( );
    __HAL_RCC_TIM4_CLK_ENABLE( );
    __HAL_RCC_TIM15_CLK_ENABLE( );

    Timer_Init( TIM1, DUAL );
    TIM1->CCR1 = TIM_STROBE1_ON;
    TIM1->CCR2 = TIM_STROBE1_OFF;
    TIM1->CCR3 = TIM_STROBE2_ON;
    TIM1->CCR4 = TIM_STROBE2_OFF;

    Timer_Init( TIM2, DUAL );
    TIM2->CCR1 = TIM_STROBE3_ON;
    TIM2->CCR2 = TIM_STROBE3_OFF;
    TIM2->CCR3 = TIM_STROBE4_ON;
    TIM2->CCR4 = TIM_STROBE4_OFF;

    Timer_Init( TIM3, DUAL );
    TIM3->CCR1 = TIM_STROBE5_ON;
    TIM3->CCR2 = TIM_STROBE5_OFF;
    TIM3->CCR3 = TIM_STROBE6_ON;
    TIM3->CCR4 = TIM_STROBE6_OFF;

    Timer_Init( TIM4, SINGLE );
    TIM4->CCR1 = TIM_STROBE7_ON;
    TIM4->CCR2 = TIM_STROBE7_OFF;

    Timer_Init( TIM15, SINGLE );
    TIM15->CCR1 = TIM_STROBE8_ON;
    TIM15->CCR2 = TIM_STROBE8_OFF;
}

/**
 * @brief  Starts the 5 timers used for generating 8 strobes.
 * The timers are (TIM1, TIM2, TIM3, TIM4, and TIM15.
 *
 * @retval none
 */
void BSP_Timer_Start( void )
{
    /* enable the slave timers */
    TIM1->CR1 = TIM_CR1_CEN;
    TIM3->CR1 = TIM_CR1_CEN;
    TIM4->CR1 = TIM_CR1_CEN;
    TIM15->CR1 = TIM_CR1_CEN;

    /* Start the master timer. The Slaves should start synchronously */
    TIM2->CR1 = TIM_CR1_CEN;
}

/*
 * Private Methods
 */

static void Timer_Init( TIM_TypeDef *tim, OutputCount_t out )
{
    /* CNT: Counter Register */
    tim->CNT = 0x0000;

    /* TIM2 is master and the other 4 are slaves that start with TIM2 Enable. */
    if ( tim == TIM2 )
    {
        /* CR2: Control register 2 */
        /* MMS = 001: The CNT_EN output on TRGO */
        tim->CR2 = 0b001 << TIM_CR2_MMS_Pos;

        /* SMCR: Slave Mode Control Register */
        /* MSM = 1 Trigger is delayed to synch slave timers */
        tim->SMCR = 1 << TIM_SMCR_MSM_Pos;
    }
    else if ( tim == TIM15 )
    {

        /* SMCR: Slave Mode Control Register */
        /* Set as slave to TIM2 -- starts on trigger of TIM2. */
        /* SMS[3:0] = 0111 External Clock Mode - Rising edges of the selected trigger (TRGI) clock the counter */
        /* TS[4:0] = 00000 Trigger Selection = Internal Trigger 0 (ITR0) = TIM2 */
        tim->SMCR = ( 0b0111 << TIM_SMCR_SMS_Pos )
                | ( 0b00000 << TIM_SMCR_TS_Pos );
    }
    else
    {
        /* SMCR: Slave Mode Control Register */
        /* SMS[3:0] = 0111 External Clock Mode - Rising edges of the selected trigger (TRGI) clock the counter */
        /* TS[4:0] = 00001 Trigger Selection = Internal Trigger 1 (ITR1) = TIM2 */
        tim->SMCR = ( 0b0111 << TIM_SMCR_SMS_Pos )
                | ( 0b00001 << TIM_SMCR_TS_Pos );
    }

    /* Timer period */
    /* The APB clock for the timers (TPCLK) is 64 MHz. */
    /* For a 1 ms period, set timer period to 64M MHz * 1 mS = 64,000. */
    tim->ARR = TIM_PERIOD;
    tim->PSC = ( TIM_PRESCALER - 1 );
    tim->RCR = 0;   //repetition counter

    /* CCMR1: Capture/Compare Mode Register 1 */
    /* Set Output Compare Mode for CH1 as rise on CCR1 and fall on CCR2 */
    /* OC1M  = 1101: Combined PWM mode 2 */
    /* OC2M  = 0110: PWM mode 1 */
    tim->CCMR1 = ( 0b1101 << TIM_CCMR1_OC1M_Pos )
            | ( 0b0110 << TIM_CCMR1_OC2M_Pos );

    if ( out == DUAL )
    {
        /* CCMR2: Capture/Compare Mode Register 2 */
        /* Set Output Compare Mode for CH3 as rise on CCR1 and fall on CCR4 */
        /* OC3M  = 1101: Combined PWM mode 2 */
        /* OC4M  = 0110: PWM mode 1 */
        tim->CCMR2 = ( 0b1101 << TIM_CCMR2_OC3M_Pos )
                | ( 0b0110 << TIM_CCMR2_OC3M_Pos );
    }
    else
    {
        /* CCMR2: Capture/Compare Mode Register 2
         * CH3 & CH4 are unused.
         */
        tim->CCMR2 = 0x0000;
    }

    /* Capture/compare registers */
    /* Set the rise (CCR1) and fall (CCR2) positions */
    tim->CCR1 = 16000;  // 25% of period;
    tim->CCR2 = 48000;  // 75% of period;

    /* Disable interrupts  */
    tim->DIER = 0x0;

    if ( out == DUAL )
    {
        /* Capture/Compare Enable Register */
        /* Enable CH1 and CH3 outputs */
        tim->CCER = TIM_CCER_CC1E | TIM_CCER_CC3E;
    }
    else
    {
        /* Capture/Compare Enable Register */
        /* Enable only CH1 output */
        tim->CCER = TIM_CCER_CC1E;
    }

    /* Enable Main Output Enable (MOE) and define off state on outputs  */
    tim->BDTR = ( TIM_BDTR_MOE | TIM_BDTR_OSSR | TIM_BDTR_OSSI );

    /* Generate an update event to reload registers now */
    tim->EGR = TIM_EGR_UG;

    /* Configure the GPIOs */
    Timer_GPIO_Init( );

    /* Clear all prior interrupts (write 0 to clear) */
    tim->SR = 0x0000;

    /* Start the timer as an up count timer with auto-preload is not buffered */
    tim->CR1 = TIM_CR1_CEN;
}

/**
 * @brief  Configures the GPIO outputs for TIM1, TIM2, TIM3, TIM4, and TIM15.
 *
 * @retval none
 */
static void Timer_GPIO_Init( void )
{
    /**
     * Timer GPIO Configuration
     * PA8  = STB1_TIM1_CH1
     * PA10 = STB2_TIM1_CH3
     * PB10 = STB4_TIM2_CH3
     * PB4  = STB5_TIM3_CH1
     * PB0  = STB6_TIM3_CH3
     * PB6  = STB7_TIM4_CH1
     * PC1  = STB8_TIM15_CH1
     */

    __HAL_RCC_GPIOA_CLK_ENABLE( );
    __HAL_RCC_GPIOB_CLK_ENABLE( );
    __HAL_RCC_GPIOC_CLK_ENABLE( );

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* PA8 = STB1_TIM_CH1, PA10 = STB2_TIM1_CH3 */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    /* PC4 = STB3_TIM2_CH1 */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM2;
    HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );

    /* PB10 = STB4_TIM2_CH3 */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM2;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

    /* PA4 = STB5_TIM3_CH1, PA0 = STB6_TIM3_CH3 */
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

    /* PB6 = STB7_TIM4_CH1 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM4;
    HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

    /* PC1 = STB8_TIM15_CH1 */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM15;
    HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
}

#if 0


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
    TIM1->SMCR = ( 0b0111 << TIM_SMCR_SMS_Pos ) | ( 0b00001 << TIM_SMCR_TS_Pos )

    /* Timer period.
     * TIM1 clock mux is set to TPCLK, which is 64 MHz.
     * For a 1 ms period, set timer period to 64M MHz * 1 mS = 64,000.
     */
    TIM1->ARR = 64000;      // period is 1 ms
    TIM1->PSC = ( 1 - 1 );    // Prescaler = 1
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
    TIM1->CCMR1 = ( 0b1101 << TIM_CCMR1_OC1M_Pos )
            | ( 0b0110 << TIM_CCMR1_OC2M_Pos );

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

#endif
