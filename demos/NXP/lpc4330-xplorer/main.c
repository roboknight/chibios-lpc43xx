/*
    ChibiOS - Copyright (C) 2006-2014 Giovanni Di Sirio

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

#include "nil.h"
#include "hal.h"

/*
 * Blue LEDs blinker thread, times are in milliseconds.
 */
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg) {

  (void)arg;

  while (TRUE) {
	palTogglePad(LED_PORT, BLUE_LED);
//    palClearPort(IOPORT1, PAL_PORT_BIT(PA_LED2));
//    palSetPort(IOPORT1, PAL_PORT_BIT(PA_LED1) | PAL_PORT_BIT(PA_LED2));
    chThdSleepMilliseconds(800);
  }
}

/*
 * Yellow LED blinker thread, times are in milliseconds.
 */
THD_WORKING_AREA(waThread2, 128);
THD_FUNCTION(Thread2, arg) {

  (void)arg;
  while (TRUE) {
	palSetPad(LED_PORT, GREEN_LED);
    chThdSleepMilliseconds(200);
	palClearPad(LED_PORT, GREEN_LED);
    chThdSleepMilliseconds(300);
  }
}

THD_TABLE_BEGIN
	THD_TABLE_ENTRY(waThread1,"blinker1",Thread1,NULL)
	THD_TABLE_ENTRY(waThread2,"blinker2",Thread2,NULL)
THD_TABLE_END

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the buttons state and run test procedure
   * or print "Hello World!" on serial driver 1.
   */
  while (TRUE) {
  }
  return 0;
}
