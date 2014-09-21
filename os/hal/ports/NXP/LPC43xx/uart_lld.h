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
 * @file    LPC43xx/uart_lld.h
 * @brief   UART Driver subsystem low level driver header.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup UART
 * @{
 */

#ifndef _UART_LLD_H_
#define _UART_LLD_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define UART_RB_SIZE 256

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef enum {
	B115200 = 115200,
	B57600  = 57600,
	B38400  = 38400,
	B19200  = 19200,
	B14400  = 14400,
	B9600   = 9600,
	B4800   = 4800,
	B2400   = 2400,
	B1200   = 1200
} BaudRate_T;

typedef struct {
	BaudRate_T rate;
	uint32_t   priority,
			   uart_options;
} UARTConfig;

/**
 * @brief   Structure representing an UART driver.
 */
typedef struct UARTDriver UARTDriver;

/**
 * @brief   Structure representing an UART driver.
 */
struct UARTDriver {
  /**
   * @brief Driver state.
   */
  uartstate_t               state;
  /**
   * @brief Transmitter state.
   */
  uarttxstate_t             txstate;
  /**
   * @brief Receiver state.
   */
  uartrxstate_t             rxstate;
  /**
   * @brief Current configuration data.
   */
  const UARTConfig          *config;
#if defined(UART_DRIVER_EXT_FIELDS)
  UART_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the USART registers block.
   */
  LPC_USART_T             	*usart;
  IRQn_Type					irqn;
  /**
   * @brief Default receive buffer while into @p UART_RX_IDLE state.
   */
  /* Transmit and receive buffers */
  uint8_t 					txbuff[UART_RB_SIZE], 
  							rxbuff[UART_RB_SIZE];
  /* Transmit and receive ring buffers */
  RINGBUFF_T		 		txring, 
  							rxring;

};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void uart_lld_init(void);
  void uart_lld_start(UARTDriver *);
  void uart_lld_stop(UARTDriver *);
  void uart_lld_start_send(UARTDriver *, size_t, const void *);
  size_t uart_lld_stop_send(UARTDriver *);
  void uart_lld_start_receive(UARTDriver *, size_t, void *);
  size_t uart_lld_stop_receive(UARTDriver *);
  
  extern ROMCONST UARTConfig uart_default_config;
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/

#endif /* _UART_LLD_H_ */

/** @} */
