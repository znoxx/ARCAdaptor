# Name: Makefile
# Project: V-USB ARCADAPTOR
# Author: http://znoxx.me (based on Andreas Oberdorfer V-USB MAME PANEL)
# Creation Date: 2013-02-21
# Tabsize: 4
# Copyright 2009 - 2012 http://znoxx.me
# License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)

# Set the MCU value to the corresponding Atmega type
# MCU =  8 Make Atmega8 version
# MCU = 32 Make Atmega32 version
MCU = 8

COMPILE = avr-gcc -Wall -Os -Iusbdrv -I. -mmcu=atmega$(MCU)

USBOBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o
EEPROMOBJECTS = eeprom/hid_eeprom.o
OBJECTS = $(USBOBJECTS) $(EEPROMOBJECTS) hid_eeprom_funcs.o hid_input.o hid_funcs.o main.o

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0



# symbolic targets:
all:	main.hex

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

# Fuse high byte:
# 0xc9 = 1 1 0 0   1 0 0 1 <-- BOOTRST (boot reset vector at 0x0000)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
#        | | | |   | +-------- BOOTSZ1
#        | | | |   + --------- EESAVE (don't preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (full output swing)
#        | | +---------------- SPIEN (allow serial programming)
#        | +------------------ WDTON (WDT not always on)
#        +-------------------- RSTDISBL (reset pin is enabled)
# Fuse low byte:
# 0x9f = 1 0 0 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ BODEN (BrownOut Detector enabled)
#        +-------------------- BODLEVEL (2.7V)

flashit:
	avrdude -p m$(MCU) -c usbtiny  -U flash:w:arcadaptor$(MCU).hex -U lfuse:w:0x9F:m -U hfuse:w:0xC9:m -U eeprom:w:arcadaptor$(MCU).eep -v

bootload: 
	avrdude -p m$(MCU) -c usbasp -D -U flash:w:arcadaptor$(MCU).hex -U eeprom:w:arcadaptor$(MCU).eep

clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s eeprom/*.o

# file targets:
main.bin:	$(OBJECTS)
	$(COMPILE) -o main.bin $(OBJECTS)

main.hex:	main.bin
	rm -f arcadaptor$(MCU).hex arcadaptor$(MCU).eep
	avr-objcopy -R .eeprom -j .text -j .data -O ihex main.bin arcadaptor$(MCU).hex
	avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex main.bin arcadaptor$(MCU).eep

cpp:
	$(COMPILE) -E main.c
