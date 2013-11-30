# Set the MCU value to the corresponding Atmega type
# MCU =  8 Make Atmega8 version
# MCU = 32 Make Atmega32 version
MCU = 8

COMPILE = avr-gcc -Wall -Os -I. -mmcu=atmega$(MCU)

OBJECTS = stub.o hid_eeprom.o

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0



# symbolic targets:
all:	eeprom

.c.o:
	$(COMPILE) -c $< -o $@



bootload: 
	avrdude -p m$(MCU) -c usbasp -D -U eeprom:w:arcadaptor$(MCU).eep

clean:
	rm -f stub.hex stub.lst stub.obj stub.cof stub.list stub.map stub.eep.hex stub.bin *.o arcadaptor$(MCU).eep

# file targets:
stub.bin:	$(OBJECTS)
	$(COMPILE) -o stub.bin $(OBJECTS)

eeprom:	stub.bin
	rm -f arcadaptor$(MCU).eep
	avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex stub.bin arcadaptor$(MCU).eep
	rm stub.bin


cpp:
	$(COMPILE) -E main.c
