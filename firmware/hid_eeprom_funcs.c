#include <avr/eeprom.h>
#include "hid_eeprom_funcs.h"
#include "eeprom/hid_input_mapping.h"


void PumpFromEEPROM()
{
    //copy shift mapping data
   eeprom_busy_wait();
   eeprom_read_block(ShiftMapping, eepShiftMapping, NUMBER_OF_INPUTS);
   eeprom_busy_wait();
   eeprom_read_block(NormalMapping, eepNormalMapping, NUMBER_OF_INPUTS);
     
}

