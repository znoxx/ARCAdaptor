/* Name: hid_funcs.c
 * Project: V-USB ARCADAPTOR
 * Author: http://znoxx.me (based on Andreas Oberdorfer V-USB MAME PANEL)
 * Creation Date: 2013-02-21
 * Copyright 2013 http://znoxx.me
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#include "eeprom/hid_input_mapping.h"

unsigned char NormalMapping[NUMBER_OF_INPUTS];
unsigned char ShiftMapping[NUMBER_OF_INPUTS];

unsigned char GetKeyNormalMap(unsigned char index)
{
    
    if (index < NUMBER_OF_INPUTS)
    {
        return NormalMapping[index];
    }
    return 0;
}

unsigned char GetKeyShiftMap(unsigned char index)
{
    if (index < NUMBER_OF_INPUTS)
    {
        return ShiftMapping[index];
    }
    return 0;
}
