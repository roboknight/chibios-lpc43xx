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
 * @file    LPC43xx/pal_lld.c
 * @brief   PAL Driver subsystem low level driver code.
 *
 * @addtogroup PAL
 * @{
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level PAL driver initialization.
 *
 * @notapi
 */
void pal_lld_init(const PALConfig *config) {
	PALConfig *i = (PALConfig *)config;
	uint8_t port = 0;

	while((i->data != END_CFG) && (i->direction != END_CFG)) {
		LPC_GPIO_PORT->CLR[port] = ~(i->data);
		LPC_GPIO_PORT->SET[port] = i->data;
		LPC_GPIO_PORT->DIR[port]  |= i->direction;
		i = (PALConfig *)&config[++port];
	}
}

/** @} */
