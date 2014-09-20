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
 *  This is a pretty common construct in embedded threaded
 *  architectures, so lets just call it what it is: a workloop.
 */
#define WORKLOOP while(TRUE)

/*
 * Green LED blinker thread, times are in milliseconds.
 */
THD_WORKING_AREA(waBoardIsAlive, 128);
THD_FUNCTION(BoardIsAlive, arg) {

  (void)arg;
  WORKLOOP {
	palTogglePad(LED_PORT, GREEN_LED);
    chThdSleepMilliseconds(1000);
  }
}

/*
 *
 */
THD_WORKING_AREA(waSerial, 128);
THD_FUNCTION(SerialThread, arg) {

  (void)arg;
  WORKLOOP {
	palTogglePad(LED_PORT, BLUE_LED);
	chThdSleepMilliseconds(500);
  }
}

THD_TABLE_BEGIN
	THD_TABLE_ENTRY(waBoardIsAlive,"BoardAlive",BoardIsAlive,NULL)
	THD_TABLE_ENTRY(waSerial, "Serial", SerialThread, NULL)
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
  WORKLOOP {
  }
  return 0;
}
