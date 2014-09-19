# List of all platform files.
NXP_SRCS       = adc_18xx_43xx.c \
		 aes_18xx_43xx.c \
		 atimer_18xx_43xx.c \
		 ccan_18xx_43xx.c \
		 chip_18xx_43xx.c \
		 clock_18xx_43xx.c \
		 dac_18xx_43xx.c \
		 eeprom_18xx_43xx.c \
		 emc_18xx_43xx.c \
		 enet_18xx_43xx.c \
		 evrt_18xx_43xx.c \
		 fpu_init.c \
		 gpdma_18xx_43xx.c \
		 gpio_18xx_43xx.c \
		 gpiogroup_18xx_43xx.c \
		 hsadc_18xx_43xx.c \
		 i2c_18xx_43xx.c \
		 i2cm_18xx_43xx.c \
		 i2s_18xx_43xx.c \
		 iap_18xx_43xx.c \
		 lcd_18xx_43xx.c \
		 otp_18xx_43xx.c \
		 pinint_18xx_43xx.c \
		 pmc_18xx_43xx.c \
		 rgu_18xx_43xx.c \
		 ring_buffer.c \
		 ritimer_18xx_43xx.c \
		 rtc_18xx_43xx.c \
		 sct_18xx_43xx.c \
		 sct_pwm_18xx_43xx.c \
		 scu_18xx_43xx.c \
		 sdif_18xx_43xx.c \
		 sdmmc_18xx_43xx.c \
		 spi_18xx_43xx.c \
		 ssp_18xx_43xx.c \
		 stopwatch_18xx_43xx.c \
		 sysinit_18xx_43xx.c \
		 timer_18xx_43xx.c \
		 uart_18xx_43xx.c \
		 wwdt_18xx_43xx.c

LLD_SRCS = 	 hal_lld.c \
	   	 st_lld.c

DRV_SRCS = $(NXP_SRCS) $(LLD_SRCS)

DRVSRC = $(patsubst %.c,${CHIBIOS}/os/hal/ports/NXP/LPC43xx/%.c,$(DRV_SRCS))

PLATFORMSRC = ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c \
	      $(DRVSRC)

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/ports/common/ARMCMx \
              ${CHIBIOS}/os/hal/ports/NXP/LPC43xx 
