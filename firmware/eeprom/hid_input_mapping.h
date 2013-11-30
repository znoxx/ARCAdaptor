/* Name: hid_input_mapping.h
 * Project: V-USB Mame Panel
 * Author: Andreas Oberdorfer
 * Creation Date: 2009-09-19
 * Copyright 2009 - 2011 Andreas Oberdorfer
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#ifndef __HID_INPUT_MAPPING_H__
#define __HID_INPUT_MAPPING_H__

#include "hid_keycodes.h"

enum NumberOfInputs
{
#if defined __AVR_ATmega8__

    SHIFT_SWITCH_INDEX = 12,

    NUMBER_OF_INPUTS   = 18

#elif defined __AVR_ATmega32__

    SHIFT_SWITCH_INDEX = 8,

#if USE_MOUSE_DEVICE == 1
    MOUSE_X_CLK_INDEX =  9,
    MOUSE_X_DIR_INDEX = 10,
    MOUSE_Y_CLK_INDEX = 11,
    MOUSE_Y_DIR_INDEX = 12,
#endif  // USE_MOUSE_DEVICE == 1

    NUMBER_OF_INPUTS  = 30

#endif  // defined __AVR_ATmega8/32__
};


#if defined __AVR_ATmega8__

// Atmega8 Shift switch off
extern unsigned char NormalMapping[NUMBER_OF_INPUTS];

// Atmega8 Shift switch on
extern unsigned char ShiftMapping[NUMBER_OF_INPUTS];
#elif defined __AVR_ATmega32__

// Atmega32 Shift switch off
extern unsigned char NormalMapping[NUMBER_OF_INPUTS];
// Atmega32 Shift switch on
unsigned char ShiftMapping[NUMBER_OF_INPUTS];

#endif  // defined __AVR_ATmega8/32__

unsigned char GetKeyNormalMap(unsigned char index);
unsigned char GetKeyShiftMap(unsigned char index);

#endif  // __HID_INPUT_MAPPING_H__
