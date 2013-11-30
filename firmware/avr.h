/* Name: avr.h
 * Project: V-USB Mame Panel
 * Author: Andreas Oberdorfer
 * Creation Date: 2009-09-19
 * Copyright 2009 - 2011 Andreas Oberdorfer
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#ifndef __AVR_H__
#define __AVR_H__

#define F_CPU 12000000L
#include <avr/io.h>

#if defined __AVR_ATmega8__

#  define NR_OF_JOYSTICKS 2
#  define USE_MOUSE_DEVICE 0

#elif defined __AVR_ATmega32__

#  define NR_OF_JOYSTICKS 2
#  define USE_MOUSE_DEVICE 0

#else   // defined __AVR_ATmega8/32__
#  error "unsupported MCU specified in makefile"
#endif  // defined __AVR_ATmega8/32__

#endif  // __AVR_H__
