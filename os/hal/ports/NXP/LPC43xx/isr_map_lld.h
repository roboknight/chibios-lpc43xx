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
 * @file    LPC43xx/isr_map_lld.h
 * @brief   ISR subsystem low level remap.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup ST
 * @{
 */

#ifndef _LPC43XX_ISR_MAP_H_
#define _LPC43XX_ISR_MAP_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Create the IRQ Handler device map.
 */

#define		_V(x)	Vector##x
#define		_H(y)	y##_HANDLER

#define		DAC_HANDLER				_V(40)
#define		M0APP_HANDLER			_V(44)
#define		DMA_HANDLER				_V(48)
#define		RESERVED1				_V(4C)
#define		RESERVED2				_V(50)
#define		ETHERNET_HANDLER		_V(54)
#define		SDIO_HANDLER			_V(58)
#define		LCD_HANDLER				_V(5C)
#define		USB0_HANDLER			_V(60)
#define		USB1_HANDLER			_V(64)
#define		SCT_HANDLER				_V(68)
#define		RITIMER_HANDLER			_V(6C)
#define		TIMER0_HANDLER			_V(70)
#define		TIMER1_HANDLER			_V(74)
#define		TIMER2_HANDLER			_V(78)
#define		TIMER3_HANDLER			_V(7C)
#define		MCPWM_HANDLER			_V(80)
#define		ADC0_HANDLER			_V(84)
#define		I2C0_HANDLER			_V(88)
#define		I2C1_HANDLER			_V(8C)
#define		SPI_HANDLER				_V(90)
#define		ADC1_HANDLER			_V(94)
#define		SSP0_HANDLER			_V(98)
#define		SSP1_HANDLER			_V(9C)
#define		USART0_HANDLER			_V(A0)
#define		USART1_HANDLER			_V(A4)
#define		USART2_HANDLER			_V(A8)
#define		USART3_HANDLER			_V(AC)
#define		I2S0_HANDLER			_V(B0)
#define		I2S1_HANDLER			_V(B4)
#define		RESERVED4_HANDLER		_V(B8)
#define		SGPIO_HANDLER			_V(BC)
#define		PIN0_HANDLER			_V(C0)
#define		PIN1_HANDLER			_V(C4)
#define		PIN2_HANDLER			_V(C8)
#define		PIN3_HANDLER			_V(CC)
#define		PIN4_HANDLER			_V(D0)
#define		PIN5_HANDLER			_V(D4)
#define		PIN6_HANDLER			_V(D8)
#define		PIN7_HANDLER			_V(DC)
#define		GINT0_HANDLER			_V(E0)
#define		GINT1_HANDLER			_V(E4)
#define		EVENTROUTER_HANDLER		_V(E8)
#define		C_CAN1_HANDLER			_V(EC)
#define		RESERVED6_HANDLER		_V(F0)
#define		ADCHS_HANDLER			_V(F4)
#define		ATIMER_HANDLER			_V(F8)
#define		RTC_HANDLER				_V(FC)
#define		RESERVED8_HANDLER		_V(100)
#define		WWDT_HANDLER			_V(104)
#define		M0SUB_HANDLER			_V(108)
#define		C_CAN0_HANDLER			_V(10C)
#define		QEI_HANDLER				_V(110)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/

#endif /* _LPC43XX_ISR_MAP_H_ */

/** @} */
