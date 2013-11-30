#ifndef __HID_EEPROM_FUNCS_H__
#define __HID_EEPROM_FUNCS_H__

#include "eeprom/hid_input_mapping.h"

extern unsigned char eepShiftMapping[NUMBER_OF_INPUTS];
extern unsigned char eepNormalMapping[NUMBER_OF_INPUTS];


#if defined __AVR_ATmega8__
     #define  XPB0     0
     #define  XPB1     1
     #define  XPB2     2
     #define  XPB3     3
     #define  XPB4     4
     #define  XPB5     5
     #define  XPC0     6
     #define  XPC1     7
     #define  XPC2     8
     #define  XPC3     9
     #define  XPC4     10
     #define  XPC5     11
     #define  XPD1     12
     #define  XPD3     13
     #define  XPD4     14
     #define  XPD5     15
     #define  XPD6     16
     #define  XPD7     17
    #elif defined __AVR_ATmega32__
     #define  XPA0     0
     #define  XPA1     1
     #define  XPA2     2
     #define  XPA3     3
     #define  XPA4     4
     #define  XPA5     5
     #define  XPA6     6
     #define  XPA7     7
     #define  XPB0     8
     #define  XPB1     9
     #define  XPB2     10
     #define  XPB3     11
     #define  XPB4     12
     #define  XPB5     13
     #define  XPB6     14
     #define  XPB7     15
     #define  XPC0     16
     #define  XPC1     17
     #define  XPC2     18
     #define  XPC3     19
     #define  XPC4     20
     #define  XPC5     21
     #define  XPC6     22
     #define  XPC7     23
     #define  XPD1     24
     #define  XPD3     25
     #define  XPD4     26
     #define  XPD5     27
     #define  XPD6     28
     #define  XPD7     29
    #endif

void PumpFromEEPROM();
#endif //__HID_EEPROM_FUNCS_H__
