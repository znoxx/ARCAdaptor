/* Name: hid_input.h
 * Project: V-USB Mame Panel
 * Author: Andreas Oberdorfer
 * Creation Date: 2009-09-19
 * Copyright 2009 - 2011 Andreas Oberdorfer
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#ifndef __HID_INPUT_H__
#define __HID_INPUT_H__

enum ReportIds
{
    ID_Unknown = 0,
    ID_Keyboard,
    ID_Consumer,
    ID_Joystick1,
    ID_Joystick2,
    ID_Joystick3,
    ID_Joystick4,
    ID_Mouse
};

void InitPorts(void);
void ScanInput(void);
unsigned char NeedUpdate(void);
unsigned char BuildReport(unsigned char id);
extern unsigned char ReportBuffer[];

#endif  // __HID_INPUT_H__
