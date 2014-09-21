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
 * @file    LPC43xx/uart_lld.c
 * @brief   UART Driver subsystem low level driver code.
 *
 * @addtogroup UART
 * @{
 */

#include "hal.h"

#if HAL_USE_UART || defined(__DOXYGEN__)

#if !LPC43XX_UART_USE_USART0 && !LPC43XX_UART_USE_USART1 && \
    !LPC43XX_UART_USE_USART2 && !LPC43XX_UART_USE_USART3 
#error "LPC43XX_UART not chosen!"
#endif

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/
/** @brief USART0 UART driver identifier.*/
#if LPC43XX_UART_USE_USART0 || defined(__DOXYGEN__)
UARTDriver UARTD0;
#endif

/** @brief USART2 UART driver identifier.*/
#if LPC43XX_UART_USE_USART1 || defined(__DOXYGEN__)
UARTDriver UARTD1;
#endif

/** @brief USART3 UART driver identifier.*/
#if LPC43XX_UART_USE_USART2 || defined(__DOXYGEN__)
UARTDriver UARTD2;
#endif

#if LPC43XX_UART_USE_USART3 || defined(__DOXYGEN__)
UARTDriver UARTD3;
#endif

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   USART common service routine.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
static void serve_usart_irq(UARTDriver *uartp) {

  Chip_UART_IRQRBHandler(uartp->usart, &uartp->rxring, &uartp->txring);

}


/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/
#if LPC43XX_UART_USE_USART0 || defined(__DOXYGEN__)
#if !defined(USART0_HANDLER)
#error "USART0_HANDLER not defined"
#endif
/**
 * @brief   USART0 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(_H(USART0)) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD0);

  OSAL_IRQ_EPILOGUE();
}
#endif /* LPC43XX_UART_USE_USART0 */

#if LPC43XX_UART_USE_USART1 || defined(__DOXYGEN__)
#if !defined(_H(USART1))
#error "USART1_HANDLER not defined"
#endif
/**
 * @brief   USART1 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(_H(USART1)) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD1);

  OSAL_IRQ_EPILOGUE();
}
#endif /* LPC43XX_UART_USE_USART1 */

#if LPC43XX_UART_USE_USART2 || defined(__DOXYGEN__)
#if !defined(_H(USART2))
#error "USART2_HANDLER not defined"
#endif
/**
 * @brief   USART2 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(_H(USART2)) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD2);

  OSAL_IRQ_EPILOGUE();
}
#endif /* LPC43XX_UART_USE_USART2 */

#if LPC43XX_UART_USE_USART3 || defined(__DOXYGEN__)
#if !defined(_H(USART3))
#error "USART3_HANDLER not defined"
#endif
/**
 * @brief   USART3 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(_H(USART3)) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD3);

  OSAL_IRQ_EPILOGUE();
}
#endif /* LPC43XX_UART_USE_USART3 */
/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level UART driver start-up.
 *
 * @notapi
 */
void uart_lld_start(UARTDriver *uartp) {
	LPC_USART_T *port   = uartp->usart;
	IRQn_Type    irqn   = uartp->irqn;
	UARTConfig  *config = (UARTConfig *)uartp->config;

	Chip_UART_Init(port);
	Chip_UART_SetBaud(port, config->rate);
	Chip_UART_ConfigData(port, config->uart_options); 

	/* Reset FIFOs, Enable FIFOs and DMA mode in UART */
	Chip_UART_SetupFIFOS(port, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
						 		UART_FCR_TX_RS | /* UART_FCR_DMAMODE_SEL | */
						 		UART_FCR_TRG_LEV0));

	/* Enable UART Rx & line status interrupts */
	/*
	 * Do not enable transmit interrupt here, since it is handled by
	 * UART_Send() function, just to reset Tx Interrupt state for the
	 * first time
	 */
	Chip_UART_IntEnable(port, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */
	RingBuffer_Init(&uartp->rxring, uartp->rxbuff, 1, UART_RB_SIZE);
	RingBuffer_Init(&uartp->txring, uartp->txbuff, 1, UART_RB_SIZE);
    nvicEnableVector(irqn, uartp->config->priority);
}

/**
 * @brief   Low level UART driver stop.
 *
 * @notapi
 */
void uart_lld_stop(UARTDriver *uartp) {
  if (uartp->state == UART_READY) {
	Chip_UART_DeInit(uartp->usart);
	nvicDisableVector(uartp->irqn);
  }
}

/**
 * @brief   Low level UART driver initiate send.
 *
 * @notapi
 */
void uart_lld_start_send(UARTDriver *uartp, size_t n, const void *txbuf) {
	Chip_UART_SendRB(uartp->usart, &uartp->txring, txbuf, n);
}

/**
 * @brief   Low level UART driver stop send.
 *
 * @notapi
 */
size_t uart_lld_stop_send(UARTDriver *uartp) {
	(void)uartp;
	return 0;
}

/**
 * @brief   Low level UART driver initiate receive.
 *
 * @notapi
 */
void uart_lld_start_receive(UARTDriver *uartp, size_t n, void *rxbuf) {
	Chip_UART_ReadRB(uartp->usart, &uartp->rxring, rxbuf, n);
}

/**
 * @brief   Low level UART driver stop receiving.
 *
 * @notapi
 */
size_t uart_lld_stop_receive(UARTDriver *uartp) {
	/* Disable UART Rx & line status interrupts */
	Chip_UART_IntDisable(uartp->usart, (UART_IER_RBRINT | UART_IER_RLSINT));

	return 0;
}

/**
 * @brief   Low level UART driver initialization.
 *
 * @notapi
 */
void uart_lld_init(void) {

#if LPC43XX_UART_USE_USART0
	Chip_SCU_PinMuxSet(0x6, 4, (SCU_MODE_PULLDOWN | 
								SCU_MODE_FUNC2));   /* P6.4 : UART0_TXD */
	Chip_SCU_PinMuxSet(0x6, 5, (SCU_MODE_INACT | 
								SCU_MODE_INBUFF_EN | 
								SCU_MODE_ZIF_DIS | 
								SCU_MODE_FUNC2));   /* P6.5 : UART0_RXD */
	
	uartObjectInit(&UARTD0);
	UARTD0.usart	= LPC_USART0;
	UARTD0.irqn		= USART0_IRQn;
	UARTD0.config   = &uart_default_config;
#endif

}

#endif /* HAL_USE_UART */

/** @} */
