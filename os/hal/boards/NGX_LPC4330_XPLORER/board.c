/*
    ChibiOS/RT - Copyright (C) 2006-2014 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "hal.h"

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Structure for initial base clock states */
struct CLK_BASE_STATES {
        CHIP_CGU_BASE_CLK_T clk;        /* Base clock */
        CHIP_CGU_CLKIN_T clkin; /* Base clock source, see UM for allowable souorces per base clock */
        bool autoblock_enab;/* Set to true to enable autoblocking on frequency change */
        bool powerdn;           /* Set to true if the base clock is initially powered down */
};

/* Initial base clock states are mostly on */
STATIC const struct CLK_BASE_STATES InitClkStates[] = {
        {CLK_BASE_PHY_TX, CLKIN_ENET_TX, true, false},
#if defined(USE_RMII)
        {CLK_BASE_PHY_RX, CLKIN_ENET_TX, true, false},
#else
        {CLK_BASE_PHY_RX, CLKIN_ENET_RX, true, false},
#endif

        /* Clocks derived from dividers */
        {CLK_BASE_LCD, CLKIN_IDIVC, true, false},
        {CLK_BASE_USB1, CLKIN_IDIVD, true, true}
};

/* SPIFI high speed pin mode setup */
STATIC const PINMUX_GRP_T spifipinmuxing[] = {
        {0x3, 3,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},   /* SPIFI CLK */
        {0x3, 4,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},   /* SPIFI D3 */
        {0x3, 5,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},   /* SPIFI D2 */
        {0x3, 6,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},   /* SPIFI D1 */
        {0x3, 7,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},   /* SPIFI D0 */
        {0x3, 8,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}    /* SPIFI CS/SSEL */
};

STATIC const PINMUX_GRP_T pinmuxing[] = {
        /* RMII pin group */
        {0x1, 15,
         (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
        {0x0, 0,
         (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2)},
        {0x1, 16,
         (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC7)},
        {0x0, 1,  (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC6)},
        {0x1, 19,
         (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC0)},
        {0x1, 18, (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
        {0x1, 20, (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
        {0x1, 17,
         (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
        {0x2, 0,  (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC7)},
        /* Board LEDs */
        {0x2, 11, (SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC0)},
        {0x2, 12, (SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC0)},
        /*  I2S  */
        {0x3, 0,  (SCU_PINIO_FAST | SCU_MODE_FUNC2)},
        {0x6, 0,  (SCU_PINIO_FAST | SCU_MODE_FUNC4)},
        {0x7, 2,  (SCU_PINIO_FAST | SCU_MODE_FUNC2)},
        {0x6, 2,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},
        {0x7, 1,  (SCU_PINIO_FAST | SCU_MODE_FUNC2)},
        {0x6, 1,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},
};


const uint32_t OscRateIn = SYSOSCCLK;
const uint32_t ExtRateIn = 0;

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
ROMCONST PALConfig pal_default_config[] = {
  {VAL_GPIO0DATA, VAL_GPIO0DIR},
  {VAL_GPIO1DATA, VAL_GPIO1DIR},
  {END_CFG, END_CFG}			/* This is required */
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
__inline void __early_init(void) {

    /* Setup system level pin muxing */
    Chip_SCU_SetPinMuxing(pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));

    /* SPIFI pin setup is done prior to setting up system clocking */
    Chip_SCU_SetPinMuxing(spifipinmuxing, sizeof(spifipinmuxing) / sizeof(PINMUX_GRP_T));
}

/*
 * Board-specific initialization code.
 */
__inline void boardInit(void) {

	int i;

	Chip_SetupCoreClock(CLKIN_CRYSTAL, MAX_CLOCK_FREQ, true);

	/* Reset and enable 32Khz oscillator */
	LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
	LPC_CREG->CREG0 |= (1 << 1) | (1 << 0);

	/* Setup a divider E for main PLL clock switch SPIFI clock to that divider.
	   Divide rate is based on CPU speed and speed of SPI FLASH part. */
#if (MAX_CLOCK_FREQ > 180000000)
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 5);
#else
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 4);
#endif
	Chip_Clock_SetBaseClock(CLK_BASE_SPIFI, CLKIN_IDIVE, true, false);

	/* Setup system base clocks and initial states. This won't enable and
	   disable individual clocks, but sets up the base clock sources for
	   each individual peripheral clock. */
	for (i = 0; i < (sizeof(InitClkStates) / sizeof(InitClkStates[0])); i++) {
		Chip_Clock_SetBaseClock(InitClkStates[i].clk, InitClkStates[i].clkin,
								InitClkStates[i].autoblock_enab, InitClkStates[i].powerdn);
	}

	/*
	 * Start with all board devices disabled
	 */
	nvicDisableVector(WWDT_IRQn);
	nvicDisableVector(DAC_IRQn);
	nvicDisableVector(M0APP_IRQn);
	nvicDisableVector(DMA_IRQn);
	nvicDisableVector(ETHERNET_IRQn);
	nvicDisableVector(SDIO_IRQn);
	nvicDisableVector(LCD_IRQn);
	nvicDisableVector(USB0_IRQn);
	nvicDisableVector(USB1_IRQn);
	nvicDisableVector(SCT_IRQn);
	nvicDisableVector(RITIMER_IRQn);
	nvicDisableVector(TIMER0_IRQn);
	nvicDisableVector(TIMER1_IRQn);
	nvicDisableVector(TIMER2_IRQn);
	nvicDisableVector(TIMER3_IRQn);
	nvicDisableVector(MCPWM_IRQn);
	nvicDisableVector(ADC0_IRQn);
	nvicDisableVector(I2C0_IRQn);
	nvicDisableVector(I2C1_IRQn);
	nvicDisableVector(SPI_INT_IRQn);
	nvicDisableVector(ADC1_IRQn);
	nvicDisableVector(SSP0_IRQn);
	nvicDisableVector(SSP1_IRQn);
	nvicDisableVector(USART0_IRQn);
	nvicDisableVector(USART1_IRQn);
	nvicDisableVector(USART2_IRQn);
	nvicDisableVector(USART3_IRQn);
	nvicDisableVector(I2S0_IRQn);
	nvicDisableVector(I2S1_IRQn);
	nvicDisableVector(SGPIO_INT_IRQn);
	nvicDisableVector(PIN_INT0_IRQn);
	nvicDisableVector(PIN_INT1_IRQn);
	nvicDisableVector(PIN_INT2_IRQn);
	nvicDisableVector(PIN_INT3_IRQn);
	nvicDisableVector(PIN_INT4_IRQn);
	nvicDisableVector(PIN_INT6_IRQn);
	nvicDisableVector(PIN_INT7_IRQn);
	nvicDisableVector(GINT0_IRQn);
	nvicDisableVector(GINT1_IRQn);
	nvicDisableVector(EVENTROUTER_IRQn);
	nvicDisableVector(C_CAN1_IRQn);
	nvicDisableVector(ADCHS_IRQn);
	nvicDisableVector(ATIMER_IRQn);
	nvicDisableVector(RTC_IRQn);
	nvicDisableVector(M0SUB_IRQn);
	nvicDisableVector(C_CAN0_IRQn);
	nvicDisableVector(QEI_IRQn);
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED_PORT, BLUE_LED);
  	//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED_PORT, GREEN_LED);

	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 1, 11);
	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 1, 12);
}
