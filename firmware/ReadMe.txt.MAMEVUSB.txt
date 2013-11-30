This is the README file for V-USB Mame Panel.

Arcade Joystick Panel Controller for Mame
=========================================

This project implements a Mame panel which includes controls for:
- Mame Games by Joystick / Mouse devices
- Mame / OS user interface by Keyboard device
- OS Volume control by Consumer device

To double the number of inputs a "Shift switch" is used:
- Shift Switch off: Control Mame games by using Joystick / Mouse / Keyboard
- Shift Switch on:  Control additional Mame / Volume / OS functions

All functions are implemented as HID devices, no host drivers are needed.

There are 2 versions available:
- Atmega8 providing 18 inputs (2 x 17 functions)
- Atmega32 providing 30 inputs (2 x 29 functions)


Atmega8
=======

Filename: mamepanel8.hex

HID device list:

- 1x Keyboard device (Mame functions control)
- 1x Consumer device (OS volume control)
- 2x Joystick device (Games joystick control)

Control Functions:

    X4-2    SHIFTSWITCH     Off                     On
    -----------------------------------------------------------
    X2-1    JOY1DOWN        Joystick 1 Down         Keyboard Down Arrow
    X2-2    JOY1UP          Joystick 1 Up           Keyboard Up Arrow
    X2-3    JOY1LEFT        Joystick 1 Left         Keyboard Left Arrow
    X2-4    JOY1RIGHT       Joystick 1 Right        Keyboard Right Arrow
    X2-5    JOY1BUTTON1     Joystick 1 Button 1     Keyboard Enter Key
    X2-6    JOY1BUTTON2     Joystick 1 Button 2     Keyboard Escape Key
    X2-7    JOY1BUTTON3     Joystick 1 Button 3     Keyboard Tab Key
    X2-8    JOY1START       Keyboard Key 1          Keyboard P Key

    X3-1    JOY2DOWN        Joystick 2 Down         Keyboard Page Down
    X3-2    JOY2UP          Joystick 2 Up           Keyboard Page Up
    X3-3    JOY2LEFT        Joystick 2 Left         Volume Down
    X3-4    JOY2RIGHT       Joystick 2 Right        Volume Up
    X3-5    JOY2BUTTON1     Joystick 2 Button 1     Keyboard F7
    X3-6    JOY2BUTTON2     Joystick 2 Button 2     Keyboard Shift + F7
    X3-7    JOY2BUTTON3     Joystick 2 Button 3     Keyboard Alt + F4
    X3-8    JOY2START       Keyboard Key 2          Volume Mute

    X4-1    COINTRIGGER     Keyboard Key 5          Keyboard Key 5

    X4-3    GND


Atmega32
========

Filename: mamepanel32.hex

HID device list:

- 1x Keyboard device (Mame functions control)
- 1x Consumer device (OS volume control)
- 2x Joystick device (Games joystick control)

Control Functions:

    X9-2    SHIFTSWITCH     Off                     On
    -----------------------------------------------------------
    X3-1    JOY1DOWN        Joystick 1 Down         Keyboard Down Arrow
    X3-2    JOY1UP          Joystick 1 Up           Keyboard Up Arrow
    X3-3    JOY1LEFT        Joystick 1 Left         Keyboard Left Arrow
    X3-4    JOY1RIGHT       Joystick 1 Right        Keyboard Right Arrow
    X3-5    JOY1BUTTON1     Joystick 1 Button 1     Keyboard Enter Key
    X3-6    JOY1BUTTON2     Joystick 1 Button 2     Keyboard Escape Key
    X3-7    JOY1BUTTON3     Joystick 1 Button 3     Keyboard Tab Key
    X3-8    JOY1BUTTON4     Joystick 1 Button 4     no function

    X4-1    JOY1BUTTON5     Joystick 1 Button 5     no function
    X4-2    JOY1BUTTON6     Joystick 1 Button 6     no function
    X4-3    JOY1BUTTON7     Joystick 1 Button 7     no function
    X4-4    JOY1BUTTON8     Joystick 1 Button 8     no function
    X4-5    JOY1START       Keyboard Key 1          Keyboard P Key
    X4-6    JOY2START       Keyboard Key 2          Volume Mute
    X4-7    none
    X4-8    none

    X5-1    JOY2BUTTON4     Joystick 2 Button 4     no function
    X5-2    JOY2BUTTON3     Joystick 2 Button 3     Keyboard Alt + F4
    X5-3    JOY2BUTTON2     Joystick 2 Button 2     Keyboard Shift + F7
    X5-4    JOY2BUTTON1     Joystick 2 Button 1     Keyboard F7
    X5-5    JOY2RIGHT       Joystick 2 Right        Volume Up
    X5-6    JOY2LEFT        Joystick 2 Left         Volume Down
    X5-7    JOY2UP          Joystick 2 Up           Keyboard Page Up
    X5-8    JOY2DOWN        Joystick 2 Down         Keyboard Page Down

    X6-1    COINTRIGGER     Keyboard Key 5          Keyboard Key 5

    X7-1    JOY2BUTTON8     Joystick 2 Button 8     no function
    X7-2    JOY2BUTTON7     Joystick 2 Button 7     no function

    X8-1    JOY2BUTTON6     Joystick 2 Button 6     no function
    X8-2    JOY2BUTTON5     Joystick 2 Button 5     no function

    X6-2    GND
    X9-1    GND


Usage examples
==============

    Setup Game:
    - SHIFTSWITCH On
    - Push JOY1BUTTON3 to enter game menu
    - Use Joystick1 to choose menu items
      Use JOY1BUTTON1 to select menu item
      Use JOY1BUTTON2 to go back from menu item

    Pause Game:
    - SHIFTSWITCH On
    - Push JOY1START

    Exit Game:
    - SHIFTSWITCH On
    - Push JOY1BUTTON2

    Save games:
    - SHIFTSWITCH On
    - Push JOY2BUTTON2
    - SHIFTSWITCH Off
    - Push JOY1START or JOY2START

    Load games:
    - SHIFTSWITCH On
    - Push JOY2BUTTON1
    - SHIFTSWITCH Off
    - Push JOY1START or JOY2START

    Shutdown:
    - SHIFTSWITCH On
    - Push JOY2BUTTON3
    - Push JOY1BUTTON1

The control functions are optimized for MameUI32 on Windows.
Feel free to create new function mappings for other GUI/OS!


Configure compile time features
===============================

    Select Atmega 8 / 32 chip:
    - File: makefile -  set MCU to 8 or 32

    Select CPU clock
    - File: avr.h - set F_CPU define

    Select number of joysticks / enable mouse
    - File: avr.h - set NR_OF_JOYSTICKS / USE_MOUSE_DEVICE defines

    Select keyboard / joystick / mouse mapping
    - File: hid_input_mappping.c - change corresponding mapping table
      (see file hid_keycodes.h for available codes)
    - File: hid_input_mappping.h - change corresponding index enumeration


Fuse bits
=========
    Fuse high byte:
    0xc9 = 1 1 0 0   1 0 0 1 <-- BOOTRST (boot reset vector at 0x0000)
           ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
           | | | |   | +-------- BOOTSZ1
           | | | |   + --------- EESAVE (don't preserve EEPROM over chip erase)
           | | | +-------------- CKOPT (full output swing)
           | | +---------------- SPIEN (allow serial programming)
           | +------------------ WDTON (WDT not always on)
           +-------------------- RSTDISBL (reset pin is enabled)
    Fuse low byte:
    0x9f = 1 0 0 1   1 1 1 1
           ^ ^ \ /   \--+--/
           | |  |       +------- CKSEL 3..0 (external >8M crystal)
           | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
           | +------------------ BODEN (BrownOut Detector enabled)
           +-------------------- BODLEVEL (2.7V)


History
=======
    V1.0 2009/10/17
        Initial Version

    V1.1 2010/08/24
        Added support for up to 8 buttons per Joystick device

    V1.2 2011/12/16
        Atmega32 changed to 2 Joystick devices using 8 buttons, no mouse
        Updated to vusb-20100715

License
=======

The project is built with AVR USB driver by Objective Development, which is
published under a proprietary Open Source license. To conform with this
license, V-USB Mame Panel is distributed under the same license conditions.
See the file "License.txt" for details.

=======================================================
Copyright 2009 - 2011 Andreas Oberdorfer (andyo@gmx.at)
