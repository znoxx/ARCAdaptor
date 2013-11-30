/* Name: main.c
 * Project: V-USB Mame Panel
 * Author: Andreas Oberdorfer
 * Creation Date: 2009-09-19
 * Copyright 2009 - 2011 Andreas Oberdorfer
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#include "avr.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/eeprom.h> 

#include "usbdrv.h"
#include "hid_input.h"
#include "hid_eeprom_funcs.h"

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

enum HID_KeyModifierCodes
{
    KEY_LeftControl      = 0xE0,
    KEY_LeftShift,
    KEY_LeftAlt,
    KEY_LeftGUI,
    KEY_RightControl,
    KEY_RightShift,
    KEY_RightAlt,
    KEY_RightGUI
};

enum HID_ConsumerCodes
{
    CKEY_Mute       = 0xE2,
    CKEY_VolumeUp   = 0xE9,
    CKEY_VolumeDown = 0xEA,
};

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] =
{
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,             // USAGE (Keyboard)
    0xa1, 0x01,             // COLLECTION (Application)
    0x85, ID_Keyboard,      //   REPORT_ID (ID_Keyboard)
    0x05, 0x07,             //   USAGE_PAGE (Keyboard)
    0x19, KEY_LeftControl,  //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, KEY_RightGUI,     //   USAGE_MAXIMUM (Keyboard RightGUI)
    0x15, 0x00,             //   LOGICAL_MINIMUM (0)
    0x25, 0x01,             //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,             //   REPORT_SIZE (1)
    0x95, 0x08,             //   REPORT_COUNT (8)
    0x81, 0x02,             //   INPUT (Data,Var,Abs)
    0x95, 0x06,             //   REPORT_COUNT (6)
    0x75, 0x08,             //   REPORT_SIZE (8)
    0x25, 0x65,             //   LOGICAL_MAXIMUM (101)
    0x19, 0x00,             //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,             //   USAGE_MAXIMUM (101)
    0x81, 0x00,             //   INPUT (Data,Ary,Abs)
    0xc0,                   // END_COLLECTION

    0x05, 0x0C,             // USAGE_PAGE (Consumer Devices)
    0x09, 0x01,             // USAGE (Consumer Control)
    0xa1, 0x01,             // COLLECTION (Application)
    0x85, ID_Consumer,      //   REPORT_ID (ID_Consumer)
    0x15, 0x00,             //   LOGICAL_MINIMUM (0)
    0x25, 0x01,             //   LOGICAL_MAXIMUM (1)
    0x09, CKEY_VolumeUp,    //   USAGE (Volume Up)
    0x09, CKEY_VolumeDown,  //   USAGE (Volume Down)
    0x75, 0x01,             //   REPORT_SIZE (1)
    0x95, 0x02,             //   REPORT_COUNT (2)
    0x81, 0x02,             //   INPUT (Data,Var,Abs)
    0x09, CKEY_Mute,        //   USAGE (Mute)
    0x95, 0x01,             //   REPORT_COUNT (1)
    0x81, 0x06,             //   INPUT (Data,Var,Rel)
    0x95, 0x05,             //   REPORT_COUNT (5)
    0x81, 0x03,             //   INPUT (Cnst,Var,Abs)
    0xc0,                   // END_COLLECTION

#if NR_OF_JOYSTICKS >= 1
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,             // USAGE (Gamepad)
    0xa1, 0x01,             // COLLECTION (Application)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
    0x85, ID_Joystick1,     //     REPORT_ID (ID_Joystick1)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0xFF,             //     LOGICAL_MINIMUM (-1)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x75, 0x04,             //     REPORT_SIZE (4)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x95, 0x08,             //     REPORT_COUNT (8)
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x08,             //     USAGE_MAXIMUM (Button 8)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
#endif // NR_OF_JOYSTICKS >= 1

#if NR_OF_JOYSTICKS >= 2
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,             // USAGE (Gamepad)
    0xa1, 0x01,             // COLLECTION (Application)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
    0x85, ID_Joystick2,     //     REPORT_ID (ID_Joystick2)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0xFF,             //     LOGICAL_MINIMUM (-1)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x75, 0x04,             //     REPORT_SIZE (4)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x95, 0x08,             //     REPORT_COUNT (8)
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x08,             //     USAGE_MAXIMUM (Button 8)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
#endif // NR_OF_JOYSTICKS >= 2

#if NR_OF_JOYSTICKS >= 3
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,             // USAGE (Gamepad)
    0xa1, 0x01,             // COLLECTION (Application)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
    0x85, ID_Joystick3,     //     REPORT_ID (ID_Joystick3)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0xFF,             //     LOGICAL_MINIMUM (-1)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x75, 0x04,             //     REPORT_SIZE (4)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x95, 0x08,             //     REPORT_COUNT (8)
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x08,             //     USAGE_MAXIMUM (Button 8)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
#endif // NR_OF_JOYSTICKS >= 3

#if NR_OF_JOYSTICKS >= 4
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,             // USAGE (Gamepad)
    0xa1, 0x01,             // COLLECTION (Application)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
    0x85, ID_Joystick4,     //     REPORT_ID (ID_Joystick4)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0xFF,             //     LOGICAL_MINIMUM (-1)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x75, 0x04,             //     REPORT_SIZE (4)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x95, 0x08,             //     REPORT_COUNT (8)
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x08,             //     USAGE_MAXIMUM (Button 8)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
#endif // NR_OF_JOYSTICKS >= 4

#if USE_MOUSE_DEVICE == 1
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,             // USAGE (Mouse)
    0xa1, 0x01,             // COLLECTION (Application)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
    0x85, ID_Mouse,         //     REPORT_ID (ID_Mouse)
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,             //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,             //     REPORT_COUNT (3)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x95, 0x01,             //     REPORT_COUNT (1)
    0x75, 0x05,             //     REPORT_SIZE (5)
    0x81, 0x03,             //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,             //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0x81,             //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,             //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,             //     REPORT_SIZE (8)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x06,             //     INPUT (Data,Var,Rel)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
#endif  // USE_MOUSE_DEVICE == 1
};

static uchar idle_rate;  // in 4 ms units

uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t* rq = (void*)data;

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
    {   //  class request type
        if (rq->bRequest == USBRQ_HID_GET_REPORT)
        {   // wValue: ReportType (highbyte), ReportID (lowbyte)
            usbMsgPtr = ReportBuffer;
            return BuildReport(rq->wValue.bytes[0]);
        }
        else if(rq->bRequest == USBRQ_HID_GET_IDLE)
        {
            usbMsgPtr = &idle_rate;
            return 1;
        }
        else if(rq->bRequest == USBRQ_HID_SET_IDLE)
        {
            idle_rate = rq->wValue.bytes[1];
        }
    }
    else
    {
        // no vendor specific requests implemented
    }
    return 0;
}

/* ------------------------------------------------------------------------- */

static void initIO(void)
{
    
    wdt_enable(WDTO_2S);

    InitPorts();
      
  
    usbInit();
    usbDeviceDisconnect();  // enforce re-enumeration, do this while interrupts are disabled
    uchar i = 0;
    while (--i)
    {   // fake USB disconnect for > 250 ms
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
}

int main(void)
{
    initIO();

    PumpFromEEPROM();
      
  
    uchar update_report = 0;
    uchar idle_counter = 0;
    uchar id = ID_Unknown;
    while (42)
    {   // main event loop
        wdt_reset();
        usbPoll();

        ScanInput();
        if (id == ID_Unknown)
        {
            id = NeedUpdate();
        }

        if (TIFR & (1 << TOV0))
        {   // 22 ms timer
            TIFR = 1 << TOV0;
            if (idle_rate != 0)
            {
                if (idle_counter > 4)
                {
                    idle_counter -= 5;   // 22 ms in units of 4 ms
                }
                else
                {
                    idle_counter = idle_rate;
                    update_report = 1;
                }
            }
        }

        if (((id != ID_Unknown) || update_report) && usbInterruptIsReady())
        {
            update_report = 0;
            usbSetInterrupt(ReportBuffer, BuildReport(id));
            id = ID_Unknown;
        }
    }
    return 0;
}
