# List of the ChibiOS/NIL Cortex-M0 STM32F0xx port files.
PORTSRC = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/crt0.c \
          $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/vectors.c \
          ${CHIBIOS}/os/nil/ports/ARMCMx/nilcore.c \
          ${CHIBIOS}/os/nil/ports/ARMCMx/nilcore_v7m.c
          
PORTASM = $(CHIBIOS)/os/nil/ports/ARMCMx/compilers/GCC/nilcoreasm_v7m.s

PORTINC = ${CHIBIOS}/os/ext/CMSIS/include \
          ${CHIBIOS}/os/ext/CMSIS/NXP \
          ${CHIBIOS}/os/common/ports/ARMCMx/devices/LPC43xx \
          ${CHIBIOS}/os/nil/ports/ARMCMx \
          ${CHIBIOS}/os/nil/ports/ARMCMx/compilers/GCC

PORTLD  = ${CHIBIOS}/os/common/ports/ARMCMx/compilers/GCC/ld
