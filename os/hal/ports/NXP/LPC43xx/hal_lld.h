/*
    ChibiOS/RT - Copyright (C) 2014 Brandon Warhurst

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
 * @file    LPC43xx/hal_lld.h
 * @brief   NXP LPC43xx HAL subsystem low level driver header.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _HAL_LLD_H_
#define _HAL_LLD_H_

#include "nxp_registry.h"
#include "chip.h"
#include "isr_map_lld.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Provides a way to access all defines provided by this header.
 */
#define HAL(X) LPC43XX_##X

/**
 * @brief   Defines the support for realtime counters in the HAL.
 */
#define HAL_IMPLEMENTS_COUNTERS FALSE

/**
 * @name    Platform identification
 * @{
 */
#define PLATFORM_NAME           "NXP"
/** @} */

/**
 * @brief   Maximum system and core clock (f_SYS) frequency.
 */
#define LPC43XX_SYSCLK_MAX      48000000UL

/**
 * @brief   Maximum bus clock (f_BUS) frequency.
 */
#define LPC43XX_BUSCLK_MAX      24000000UL

/**
 * @name    Internal clock sources
 * @{
 */
#define LPC43XX_IRCLK_F         4000000     /**< Fast internal reference clock, factory trimmed. */
#define LPC43XX_IRCLK_S         32768       /**< Slow internal reference clock, factory trimmed. */
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */

/**
 * @brief   MCU system/core clock frequency.
 */
#if !defined(LPC43XX_SYSCLK_FREQUENCY) || defined(__DOXYGEN__)
#define LPC43XX_SYSCLK_FREQUENCY    LPC43XX_SYSCLK_MAX
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(LPC43XX_SYSCLK_FREQUENCY)
#error LPC43XX_SYSCLK_FREQUENCY must be defined
#endif

#if LPC43XX_SYSCLK_FREQUENCY <= 0 || LPC43XX_SYSCLK_FREQUENCY > LPC43XX_SYSCLK_MAX
#error LPC43XX_SYSCLK_FREQUENCY out of range
#endif

#if !defined(LPC43XX_BUSCLK_FREQUENCY)
#error LPC43XX_BUSCLK_FREQUENCY must be defined
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type representing a system clock frequency.
 */
typedef uint32_t halclock_t;

/**
 * @brief   Type of the realtime free counter value.
 */
typedef uint32_t halrtcnt_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the current value of the system free running counter.
 * @note    This service is implemented by returning the content of the
 *          DWT_CYCCNT register.
 *
 * @return              The value of the system free running counter of
 *                      type halrtcnt_t.
 *
 * @notapi
 */
#define hal_lld_get_counter_value()         0

/**
 * @brief   Realtime counter frequency.
 * @note    The DWT_CYCCNT register is incremented directly by the system
 *          clock so this function returns STM32_HCLK.
 *
 * @return              The realtime counter frequency of type halclock_t.
 *
 * @notapi
 */
#define hal_lld_get_counter_frequency()     0

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#include "nvic.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void lpc_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* _HAL_LLD_H_ */

/** @} */
