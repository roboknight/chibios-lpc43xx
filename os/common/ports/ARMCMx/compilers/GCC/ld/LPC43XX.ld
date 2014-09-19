/*
 * (C) 2014 Brandon Warhurst
 */


/* LPC43xx
 * Memory setup
 */

MEMORY
{
  /* Define each memory region */
  /* Main memory regions */
  flash (rx) : ORIGIN = 0x14000000, LENGTH = 0x400000 /* 4096k */
  ram  (rwx) : ORIGIN = 0x10000000, LENGTH = 0x20000 /* 128k */

  /* Other memory regions that are available */
  RamLoc72 (rwx) : ORIGIN = 0x10080000, LENGTH = 0x12000 /* 72k */
  RamAHB32 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32k */
  RamAHB16 (rwx) : ORIGIN = 0x20008000, LENGTH = 0x4000 /* 16k */
  RamAHB_ETB16 (rwx) : ORIGIN = 0x2000c000, LENGTH = 0x4000 /* 16k */

}

include rules.ld
