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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for NGX LPC4330-Xplorer
 */

/*
 * Board identifiers.
 */
#define BOARD_NGX_LPC4330_XPLORER
#define BOARD_NAME "NGX LPC4330-XPLORER"

/*
 * Board frequencies.
 */
#define SYSOSCCLK               12000000

/*
 * Pin definitions.
 */
 
/* GPIO Port0 */
#define VAL_GPIO0DIR			0x00000000
#define VAL_GPIO0DATA			0x00000000

/* GPIO Port1 */
#define LED_PORT				GPIO_PORT1
#define GREEN_LED				PIN11
#define BLUE_LED				PIN12
/*
 *  Pins set in VAL_GPIO1DIR will be set to output.
 *  Otherwise, they will be set to input.
 */
#define VAL_GPIO1DIR			PAL_PORT_BIT(BLUE_LED)| \
								PAL_PORT_BIT(GREEN_LED)
#define	VAL_GPIO1DATA			0x00000000

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif

#endif
