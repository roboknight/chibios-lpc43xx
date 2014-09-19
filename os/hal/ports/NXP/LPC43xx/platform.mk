# List of all platform files.
PLATFORMSRC = ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c \
              ${CHIBIOS}/os/hal/ports/NXP/LPC43xx/hal_lld.c \
	      ${CHIBIOS}/os/hal/ports/NXP/LPC43xx/st_lld.c

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/ports/common/ARMCMx \
              ${CHIBIOS}/os/hal/ports/NXP/LPC43xx 
