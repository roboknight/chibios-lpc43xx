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
 * @file    LPC43xx/pal_lld.h
 * @brief   PAL Driver subsystem low level driver header.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup PAL
 * @{
 */

#ifndef _PAL_LLD_H_
#define _PAL_LLD_H_

#include "hal.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 *  List of available GPIO ports
 */
enum {
	GPIO_PORT0 = 0,
	GPIO_PORT1,
	GPIO_PORT2,
	GPIO_PORT3,
	GPIO_PORT4,
	GPIO_PORT5,
	GPIO_PORT6,
	GPIO_PORT7
};

/*
 * Maximal list of available pins on each port
 */
enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	PIN16,
	PIN17,
	PIN18,
	PIN19,
	PIN20,
	PIN21,
	PIN22,
	PIN23,
	PIN24,
	PIN25,
	PIN26,
	PIN27,
	PIN28,
	PIN29,
	PIN30,
	PIN31,
	PIN32
};

#define PAL_IOPORTS_WIDTH	32
#define END_CFG				0x4BADF00D

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef uint32_t ioportmask_t;
typedef uint32_t ioportid_t;
typedef uint32_t iomode_t;

typedef struct {
	uint32_t data,
			 direction;
} PALConfig;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define PAL_PORT_BIT(bit)	(1UL << (bit))
#define pal_lld_toggleport(port, pads)  LPC_GPIO_PORT->NOT[port] = pads
#define pal_lld_clearport(port, pads)   LPC_GPIO_PORT->CLR[port] = pads
#define pal_lld_setport(port, pads)     LPC_GPIO_PORT->SET[port] = pads

#define pal_lld_togglepad(port, pad)  LPC_GPIO_PORT->NOT[port] = PAL_PORT_BIT(pad)
#define pal_lld_clearpad(port, pad)   LPC_GPIO_PORT->CLR[port] = PAL_PORT_BIT(pad)
#define pal_lld_setpad(port, pad)     LPC_GPIO_PORT->SET[port] = PAL_PORT_BIT(pad)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  extern ROMCONST PALConfig pal_default_config[];
  
  void pal_lld_init(const PALConfig *);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/


#endif /* _PAL_LLD_H_ */

/** @} */
