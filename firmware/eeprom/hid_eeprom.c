#include <avr/eeprom.h> 
#include "hid_keycodes.h"
#include "hid_input_mapping.h"

#if defined __AVR_ATmega8__
// Atmega8 Shift switch on
unsigned char EEMEM  eepShiftMapping[NUMBER_OF_INPUTS]=
{                       //  Pin Atmega  Function     XPIN
    AC_VolumeDown,      //  14  PB0     JOY2LEFT     X2S5
    KM_SHIFT_F7,        //  15  PB1     JOY2BUTTON2  X2S11
    KM_ALT_F4,          //  16  PB2     JOY2BUTTON3  X2S13
    AC_Mute,            //  17  PB3     JOY2START    X2S15
    KEY_DownArrow,      //  18  PB4     JOY1DOWN     X1S3
    KEY_UpArrow,        //  24  PC1     JOY1UP       X1S7
    KEY_LeftArrow,      //  23  PC0     JOY1LEFT     X1S5
    KEY_RightArrow,     //  17  PB5     JOY1RIGHT    X1S1
    KEY_Enter,          //  25  PC2     JOY1BUTTON1  X1S9
    KEY_Esc,            //  26  PC3     JOY1BUTTON2  X1S11
    KEY_Tab,            //  27  PC4     JOY1BUTTON3  X1S13
    KEY_P,              //  28  PC5     JOY1START    X1S15
    0,                  //   3  PD1     SHIFTSWITCH  shift X3S3
    KEY_5,              //   5  PD3     COINTRIGGER  X3S1
    KEY_PageDown,       //   6  PD4     JOY2DOWN     X2S3
    KEY_F7,             //  11  PD5     JOY2BUTTON1  X2S9
    AC_VolumeUp,        //  12  PD6     JOY2RIGHT    X2S7
    KEY_PageUp          //  13  PD7     JOY2UP       X2S1
};

// Atmega8 Shift switch off
unsigned char EEMEM eepNormalMapping[NUMBER_OF_INPUTS] =
{                       //  Pin Atmega  Function       XPIN
    J2_Left,            //  14  PB0     JOY2LEFT       X2N5
    J2_Button2,         //  15  PB1     JOY2BUTTON2    X2N11
    J2_Button3,         //  16  PB2     JOY2BUTTON3    X2N13
    KEY_2,              //  17  PB3     JOY2START      X2N15
    J1_Down,            //  18  PB4     JOY1DOWN       X1N3
    J1_Up,              //  24  PC1     JOY1UP         X1N7
    J1_Left,            //  23  PC0     JOY1LEFT       X1N5
    J1_Right,           //  17  PB5     JOY1RIGHT      X1N1
    J1_Button1,         //  25  PC2     JOY1BUTTON1    X1N9
    J1_Button2,         //  26  PC3     JOY1BUTTON2    X1N11
    J1_Button3,         //  27  PC4     JOY1BUTTON3    X1N13
    KEY_1,              //  28  PC5     JOY1START      X1N15
    0,                  //   3  PD1     SHIFTSWITCH    shift X3N3
    KEY_5,              //   5  PD3     COINTRIGGER    X3N1
    J2_Down,            //   6  PD4     JOY2DOWN       X2N3
    J2_Button1,         //  11  PD5     JOY2BUTTON1    X2N9
    J2_Right,           //  12  PD6     JOY2RIGHT      X2N7
    J2_Up               //  13  PD7     JOY2UP         X2N1
};

#elif defined __AVR_ATmega32__
// Atmega32 Shift switch on
unsigned char EEMEM eepShiftMapping[NUMBER_OF_INPUTS]=
{                       //  Pin Atmega  Board   Function
    KEY_5,              //  40  PA0     X6-1    COINTRIGGER
    0,                  //  39  PA1     X4-8    none
    0,                  //  38  PA2     X4-7    none
    AC_Mute,            //  37  PA3     X4-6    JOY2START
    KEY_P,              //  36  PA4     X4-5    JOY1START
    0,                  //  35  PA5     X4-4    JOY1BUTTON8
    0,                  //  34  PA6     X4-3    JOY1BUTTON7
    0,                  //  33  PA7     X4-2    JOY1BUTTON6
    0,                  //   1  PB0     X9-2    SHIFTSWITCH
    0,                  //   2  PB1     X7-1    JOY2BUTTON8
    0,                  //   3  PB2     X7-2    JOY2BUTTON7
    0,                  //   4  PB3     X8-1    JOY2BUTTON6
    0,                  //   5  PB4     X8-2    JOY2BUTTON5
    0,                  //   6  PB5     X5-1    JOY2BUTTON4
    KM_ALT_F4,          //   7  PB6     X5-2    JOY2BUTTON3
    KM_SHIFT_F7,        //   8  PB7     X5-3    JOY2BUTTON2
    KEY_UpArrow,        //  22  PC0     X3-2    JOY1UP
    KEY_LeftArrow,      //  23  PC1     X3-3    JOY1LEFT
    KEY_RightArrow,     //  24  PC2     X3-4    JOY1RIGHT
    KEY_Enter,          //  25  PC3     X3-5    JOY1BUTTON1
    KEY_Esc,            //  26  PC4     X3-6    JOY1BUTTON2
    KEY_Tab,            //  27  PC5     X3-7    JOY1BUTTON3
    0,                  //  28  PC6     X3-8    JOY1BUTTON4
    0,                  //  29  PC7     X4-1    JOY1BUTTON5
    KEY_F7,             //  15  PD1     X5-4    JOY2BUTTON1
    AC_VolumeUp,        //  17  PD3     X5-5    JOY2RIGHT
    AC_VolumeDown,      //  18  PD4     X5-6    JOY2LEFT
    KEY_PageUp,         //  19  PD5     X5-7    JOY2UP
    KEY_PageDown,       //  20  PD6     X5-8    JOY2DOWN
    KEY_DownArrow       //  21  PD7     X3-1    JOY1DOWN
};

// Atmega32 Shift switch on
unsigned char EEMEM eepShiftMapping[NUMBER_OF_INPUTS]=
{                       //  Pin Atmega  Board   Function
    KEY_5,              //  40  PA0     X6-1    COINTRIGGER
    0,                  //  39  PA1     X4-8    none
    0,                  //  38  PA2     X4-7    none
    AC_Mute,            //  37  PA3     X4-6    JOY2START
    KEY_P,              //  36  PA4     X4-5    JOY1START
    0,                  //  35  PA5     X4-4    JOY1BUTTON8
    0,                  //  34  PA6     X4-3    JOY1BUTTON7
    0,                  //  33  PA7     X4-2    JOY1BUTTON6
    0,                  //   1  PB0     X9-2    SHIFTSWITCH
    0,                  //   2  PB1     X7-1    JOY2BUTTON8
    0,                  //   3  PB2     X7-2    JOY2BUTTON7
    0,                  //   4  PB3     X8-1    JOY2BUTTON6
    0,                  //   5  PB4     X8-2    JOY2BUTTON5
    0,                  //   6  PB5     X5-1    JOY2BUTTON4
    KM_ALT_F4,          //   7  PB6     X5-2    JOY2BUTTON3
    KM_SHIFT_F7,        //   8  PB7     X5-3    JOY2BUTTON2
    KEY_UpArrow,        //  22  PC0     X3-2    JOY1UP
    KEY_LeftArrow,      //  23  PC1     X3-3    JOY1LEFT
    KEY_RightArrow,     //  24  PC2     X3-4    JOY1RIGHT
    KEY_Enter,          //  25  PC3     X3-5    JOY1BUTTON1
    KEY_Esc,            //  26  PC4     X3-6    JOY1BUTTON2
    KEY_Tab,            //  27  PC5     X3-7    JOY1BUTTON3
    0,                  //  28  PC6     X3-8    JOY1BUTTON4
    0,                  //  29  PC7     X4-1    JOY1BUTTON5
    KEY_F7,             //  15  PD1     X5-4    JOY2BUTTON1
    AC_VolumeUp,        //  17  PD3     X5-5    JOY2RIGHT
    AC_VolumeDown,      //  18  PD4     X5-6    JOY2LEFT
    KEY_PageUp,         //  19  PD5     X5-7    JOY2UP
    KEY_PageDown,       //  20  PD6     X5-8    JOY2DOWN
    KEY_DownArrow       //  21  PD7     X3-1    JOY1DOWN
};

#endif  // defined __AVR_ATmega8/32__


