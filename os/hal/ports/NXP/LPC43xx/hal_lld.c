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

/**
 * @file    LPC43XX/hal_lld.c
 * @brief   NXP LPC43XX HAL Driver subsystem low level driver source.
 *
 * @addtogroup HAL
 * @{
 */

#include "osal.h"
#include "hal.h"
#include "chip.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
/* Structure for initial base clock states */
struct CLK_BASE_STATES {
        CHIP_CGU_BASE_CLK_T clk;        /* Base clock */
        CHIP_CGU_CLKIN_T clkin; /* Base clock source, see UM for allowable souorces per base clock */
        bool autoblock_enab;/* Set to true to enable autoblocking on frequency change */
        bool powerdn;           /* Set to true if the base clock is initially powered down */
};

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

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

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   LPC43xx early initialization here.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function should be invoked just after the system reset.
 *
 * @special
 */
void __early_init(void) {
	
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level HAL driver initialization.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function should be invoked just after the system reset.
 *
 * @notapi
 */
void hal_lld_init(void) {
}

/**
 * @brief   Platform early initialization.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function is meant to be invoked early during the system
 *          initialization, it is usually invoked from the file
 *          @p board.c.
 *
 * @special
 */
void platform_early_init(void) {
}

/** @} */
