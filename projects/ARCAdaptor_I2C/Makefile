# Name: Makefile
# Project: USB I2C
# Author: Christian Starkjohann, modified for I2C USB by Till Harbaum
# Creation Date: 2005-03-20
# Tabsize: 4
# Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
# License: Proprietary, free under certain conditions. See Documentation.
# This Revision: $Id: Makefile-avrusb.mega8,v 1.1 2006/12/03 21:28:59 harbaum Exp $



# temporary workaround for the �error: attempt to use poisoned "SIG_INTERRUPT0"�
DEFINES += -D__AVR_LIBC_DEPRECATED_ENABLE__=1

# need to define for <util/delay.h>
DEFINES += -DF_CPU=12000000UL

COMPILE = avr-gcc -Wall -O2 -Iusbdrv -I. -mmcu=atmega8 $(DEFINES)

OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o


# symbolic targets:
all:	firmware.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@



clean:
	rm -f firmware.hex firmware.lst firmware.obj firmware.cof firmware.list firmware.map firmware.eep.hex firmware.bin *.o usbdrv/*.o firmware.s usbdrv/oddebug.s usbdrv/usbdrv.s

# file targets:
firmware.bin:	$(OBJECTS)
	$(COMPILE) -o firmware.bin $(OBJECTS)

firmware.hex:	firmware.bin
	rm -f firmware.hex firmware.eep.hex
	avr-objcopy -j .text -j .data -O ihex firmware.bin firmware.hex
	./checksize firmware.bin 8192 960
# do the checksize script as our last action to allow successful compilation
# on Windows with WinAVR where the Unix commands will fail.



disasm:	firmware.bin
	avr-objdump -d firmware.bin

cpp:
	$(COMPILE) -E main.c
