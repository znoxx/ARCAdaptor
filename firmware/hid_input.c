/* Name: hid_input.c
 * Project: V-USB Mame Panel
 * Author: Andreas Oberdorfer
 * Creation Date: 2009-09-19
 * Copyright 2009 - 2011 Andreas Oberdorfer
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 */

#include "hid_input.h"
#include "eeprom/hid_input_mapping.h"

#include "avr.h"

typedef unsigned char uchar;

enum Debounce {DEBOUNCE = 5 };
static uchar InputState[NUMBER_OF_INPUTS];

#define IsKeyDown(index) (InputState[index] & 0x80)

static uchar IsKeyboardCode(uchar key)
{
    return (key >= KEY_A) && (key <= MOD_RightGUI);
}
static uchar IsModifierCode(uchar key)
{
    return (key >= MOD_LeftControl) && (key <= MOD_RightGUI);
}
static uchar IsConsumerCode(uchar key)
{
    return (key >= AC_VolumeUp) && (key <= AC_Mute);
}
#if NR_OF_JOYSTICKS >= 1
static uchar IsJoystickCode(uchar key, uchar joy)
{
    key -= (joy * NR_OF_EVENTS_PER_JOY);
    return (key >= J1_Left) && (key < (J1_Left + NR_OF_EVENTS_PER_JOY));
}
#endif  // NR_OF_JOYSTICKS >= 1

static uchar shift_key = 0;
static uchar shift_key_cleanup = 0;

static uchar GetKey(uchar index)
{
    if (shift_key != 0)
    {
        return GetKeyShiftMap(index);
    }
    return GetKeyNormalMap(index);
}

static uchar need_key_update = 0;
static uchar need_consumer_update = 0;

#if NR_OF_JOYSTICKS >= 1
static uchar need_joystick_update[NR_OF_JOYSTICKS];
static uchar last_joystick_update = ID_Joystick1;

static uchar NeedJoystickUpdate(void)
{
    uchar i;
    for (i = 0; i < NR_OF_JOYSTICKS; i++)
    {
        if (need_joystick_update[i])
        {
            return 1;
        }
    }
    return 0;
}
#else   // NR_OF_JOYSTICKS >= 1
#define NeedJoystickUpdate() 0
#endif  // NR_OF_JOYSTICKS >= 1

#if USE_MOUSE_DEVICE == 1
static uchar IsMouseButtonCode(uchar key)
{
    return (key >= MB_Left) && (key <= MB_Middle);
}

uchar need_mouse_update = 0;
uchar mouse_x_last_clk_state = 0;
uchar mouse_x_last_dir_state = 0;
char mouse_x_count = 0;
uchar mouse_y_last_clk_state = 0;
uchar mouse_y_last_dir_state = 0;
char mouse_y_count = 0;

#define MOUSE_X_DELTA 1
#define MOUSE_Y_DELTA 1

static void MouseMoveX(uchar direction)
{
    if (direction)
    {
        if (mouse_x_count > -(127 - MOUSE_X_DELTA))
        {
            mouse_x_count -= MOUSE_X_DELTA;
        }
    }
    else
    {
        if (mouse_x_count < (127 - MOUSE_X_DELTA))
        {
            mouse_x_count += MOUSE_X_DELTA;
        }
    }
    need_mouse_update = 1;
}
static void MouseMoveY(uchar direction)
{
    if (direction)
    {
        if (mouse_y_count > -(127 - MOUSE_Y_DELTA))
        {
            mouse_y_count -= MOUSE_Y_DELTA;
        }
    }
    else
    {
        if (mouse_y_count < (127 - MOUSE_Y_DELTA))
        {
            mouse_y_count += MOUSE_Y_DELTA;
        }
    }
    need_mouse_update = 1;
}
static void CheckMouseUpdate(void)
{
    uchar mouse_clk_state = InputState[MOUSE_X_CLK_INDEX];
    uchar mouse_dir_state = InputState[MOUSE_X_DIR_INDEX];
    if (mouse_clk_state != mouse_x_last_clk_state)
    {
        if (mouse_dir_state == mouse_x_last_dir_state)
        {
            MouseMoveX(mouse_clk_state ^ mouse_dir_state);
        }
        mouse_x_last_clk_state = mouse_clk_state;
    }
    if (mouse_dir_state != mouse_x_last_dir_state)
    {
        if (mouse_clk_state == mouse_x_last_clk_state)
        {
            MouseMoveX(!(mouse_clk_state ^ mouse_dir_state));
        }
        mouse_x_last_dir_state = mouse_dir_state;
    }

    mouse_clk_state = InputState[MOUSE_Y_CLK_INDEX];
    mouse_dir_state = InputState[MOUSE_Y_DIR_INDEX];
    if (mouse_clk_state != mouse_y_last_clk_state)
    {
        if (mouse_dir_state == mouse_y_last_dir_state)
        {
            MouseMoveY(mouse_clk_state ^ mouse_dir_state);
        }
        mouse_y_last_clk_state = mouse_clk_state;
    }
    if (mouse_dir_state != mouse_y_last_dir_state)
    {
        if (mouse_clk_state == mouse_y_last_clk_state)
        {
            MouseMoveY(!(mouse_clk_state ^ mouse_dir_state));
        }
        mouse_y_last_dir_state = mouse_dir_state;
    }
}
#define NeedMouseUpdate() need_mouse_update
#else  // USE_MOUSE_DEVICE == 1
#define NeedMouseUpdate() 0
#endif  // USE_MOUSE_DEVICE == 1

void InitPorts(void)
{
#if NR_OF_JOYSTICKS >= 1
    uchar i;
    for (i = 0; i < NR_OF_JOYSTICKS; i++)
    {
        need_joystick_update[i] = 0;
    }
#endif  // NR_OF_JOYSTICKS >= 1

#ifdef __AVR_ATmega32__
    PORTA = 0xff;   // activate all pull-ups
    DDRA  = 0;      // all pins input
#endif // __AVR_ATmega32__
    PORTB = 0xff;   // activate all pull-ups
    DDRB  = 0;      // all pins input
    PORTC = 0xff;   // activate all pull-ups
    DDRC  = 0;      // all pins input
    PORTD = 0xfa;   // 1111 1010 bin: activate pull-ups except on USB lines
    DDRD  = 0;      // all pins input
}

static void SetNeedUpdate(uchar index)
{
    uchar key = GetKey(index);
    if (IsConsumerCode(key))
    {
        need_consumer_update = 1;
    }
    else if (IsKeyboardCode(key))
    {
        need_key_update = 1;
    }
#if USE_MOUSE_DEVICE == 1
    else if (IsMouseButtonCode(key))
    {
        need_mouse_update = 1;
    }
#endif  // USE_MOUSE_DEVICE == 1
#if NR_OF_JOYSTICKS >= 1
    else
    {
        uchar i;
        for (i = 0; i < NR_OF_JOYSTICKS; i++)
        {
            if (IsJoystickCode(key, i))
            {
                need_joystick_update[i] = 1;
                break;
            }
        }
    }
#endif  // NR_OF_JOYSTICKS >= 1
}

static void ShiftKeyCleanUp(void)
{
    if (shift_key_cleanup == 1)
    {
        uchar i;
        shift_key_cleanup = 2;
        for (i = 0; i < NUMBER_OF_INPUTS; i++)
        {
            if (i != SHIFT_SWITCH_INDEX)
            {
                if (InputState[i] != 0)
                {
                    if (GetKeyNormalMap(i) != GetKeyShiftMap(i))
                    {
                        SetNeedUpdate(i);
                        InputState[i] = 0;
                    }
                }
            }
        }
    }

    if (shift_key_cleanup == 2)
    {
        if (!need_consumer_update && !need_key_update &&
            !NeedJoystickUpdate() && !NeedMouseUpdate())
        {
            shift_key_cleanup = 0;
            shift_key = IsKeyDown(SHIFT_SWITCH_INDEX);
        }
    }
}

unsigned char NeedUpdate(void)
{
    ShiftKeyCleanUp();

#if NR_OF_JOYSTICKS >= 1
    if (NeedJoystickUpdate())
    {
        uchar i, x = last_joystick_update - ID_Joystick1;
        for (i = 0; i < NR_OF_JOYSTICKS; i++)
        {
            x++;
            if (x >= NR_OF_JOYSTICKS)
            {
                x = 0;
            }
            if (need_joystick_update[x])
            {
                last_joystick_update = ID_Joystick1 + x;
                need_joystick_update[x] = 0;
                return last_joystick_update;
            }
        }
    }
#endif  // NR_OF_JOYSTICKS >= 1

#if USE_MOUSE_DEVICE == 1
    if (need_mouse_update)
    {
        need_mouse_update = 0;
        return ID_Mouse;
    }
#endif  // USE_MOUSE_DEVICE == 1

    if (need_key_update)
    {
        need_key_update = 0;
        return ID_Keyboard;
    }
    if (need_consumer_update)
    {
        need_consumer_update = 0;
        return ID_Consumer;
    }
    return ID_Unknown;
}

static void SetInputCount(uchar index, uchar condition)
{
#if USE_MOUSE_DEVICE == 1
    if ((index == MOUSE_X_CLK_INDEX) || (index == MOUSE_X_DIR_INDEX) ||
        (index == MOUSE_Y_CLK_INDEX) || (index == MOUSE_Y_DIR_INDEX))
    {
        InputState[index] = condition;
        return;
    }
#endif  // USE_MOUSE_DEVICE == 1

    if (index >= NUMBER_OF_INPUTS)
    {
        return;
    }

    uchar changed = 0;
    uchar count = InputState[index];
    uchar state = count & 0x80;
    count &= 0x7f;
    if (condition)
    {
        if (count <= DEBOUNCE)
        {
            if ((count == DEBOUNCE) && !state)
            {
                changed = 1;
                state = 0x80;
            }
            count++;
        }
        else
        {
            return;
        }
    }
    else
    {
        if (count > 0)
        {
            if ((count == 1) && state)
            {
                changed = 1;
                state = 0;
            }
            count--;
        }
        else
        {
            return;
        }
    }
    InputState[index] = state | count;

    if (changed)
    {
        if (index == SHIFT_SWITCH_INDEX)
        {
            shift_key_cleanup = 1;
        }
        else
        {
            SetNeedUpdate(index);
        }
    }
}

void ScanInput(void)
{
    if (shift_key_cleanup)
    {
        return;
    }

    uchar i, x, mask;
    uchar index = 0;

#ifdef __AVR_ATmega32__
    x = PINA;
    mask = 1;
    for (i = 0; i < 8; i++)
    {
        SetInputCount(index++, (x & mask) == 0);
        mask <<= 1;
    }
#define MAX_IO_PINS 8
#else   // __AVR_ATmega32__
#define MAX_IO_PINS 6
#endif  // __AVR_ATmega32__

    x = PINB;
    mask = 1;
    for (i = 0; i < MAX_IO_PINS; i++)
    {
        SetInputCount(index++, (x & mask) == 0);
        mask <<= 1;
    }

    x = PINC;
    mask = 1;
    for (i = 0; i < MAX_IO_PINS; i++)
    {
        SetInputCount(index++, (x & mask) == 0);
        mask <<= 1;
    }

    x = PIND;
    SetInputCount(index++, (x & 0x02) == 0);
    mask = 1 << 3;
    for (i = 0; i < 5; i++)
    {
        SetInputCount(index++, (x & mask) == 0);
        mask <<= 1;
    }

#if USE_MOUSE_DEVICE == 1
    CheckMouseUpdate();
#endif  // USE_MOUSE_DEVICE == 1
}

uchar ReportBuffer[8];

static uchar ReportConsumer(void)
{
    uchar i;
    uchar consumer = 0;
    for (i = 0; i < NUMBER_OF_INPUTS; i++)
    {
        if (IsKeyDown(i))
        {
            uchar key = GetKey(i);
            if (IsConsumerCode(key))
            {
                consumer |= ConsumerBit(key);
            }
        }
    }
    ReportBuffer[0] = ID_Consumer;
    ReportBuffer[1] = consumer;
    return 2;
}

static uchar ReportKeyboard(void)
{
    uchar i, r = 2;
    ReportBuffer[0] = ID_Keyboard;
    ReportBuffer[1] = 0;    // modifiers
    for (i = 0; i < NUMBER_OF_INPUTS; i++)
    {
        if (IsKeyDown(i))
        {
            uchar key = GetKey(i);
            if (IsKeyboardCode(key))
            {
                if (IsModifierCode(key))
                {
                    ReportBuffer[1] |= ModifierBit(key);
                }
                else
                {
                    if (r < sizeof(ReportBuffer))
                    {
                        switch (key)
                        {
                        case KM_ALT_F4:
                            ReportBuffer[1] |= ModifierBit(MOD_LeftAlt);
                            ReportBuffer[r] = KEY_F4;
                            break;
                        case KM_SHIFT_F7:
                            ReportBuffer[1] |= ModifierBit(MOD_LeftShift);
                            ReportBuffer[r] = KEY_F7;
                            break;
                        default:
                            ReportBuffer[r] = key;
                            break;
                        }
                        r++;
                    }
                }
            }
        }
    }
    for (; r < sizeof(ReportBuffer); r++)
    {
        ReportBuffer[r] = 0;
    }
    return sizeof(ReportBuffer);
}

#if NR_OF_JOYSTICKS >= 1
static uchar ReportJoystick(uchar id)
{
    uchar i;
    uchar joy_x = 0x00;
    uchar joy_y = 0x00;
    uchar joy_b = 0;

    ReportBuffer[0] = id;
    id = (id - ID_Joystick1) * NR_OF_EVENTS_PER_JOY;

    for (i = 0; i < NUMBER_OF_INPUTS; i++)
    {
        if (IsKeyDown(i))
        {
            uchar key = GetKey(i) - id;
            switch (key)
            {
            case J1_Left:
                joy_x = 0x0F;
                break;
            case J1_Right:
                joy_x = 0x01;
                break;

            case J1_Up:
                joy_y = 0xF0;
                break;
            case J1_Down:
                joy_y = 0x10;
                break;

            case J1_Button1:
            case J1_Button2:
            case J1_Button3:
            case J1_Button4:
            case J1_Button5:
            case J1_Button6:
            case J1_Button7:
            case J1_Button8:
                joy_b |= JoyButtonBit(key);
                break;

            default:
                break;
            }
        }
    }
    ReportBuffer[1] = joy_x | joy_y;
    ReportBuffer[2] = joy_b;
    return 3;
}
#endif  // NR_OF_JOYSTICKS >= 1

#if USE_MOUSE_DEVICE == 1
static uchar ReportMouse(void)
{
    uchar i;
    uchar buttons = 0;
    for (i = 0; i < NUMBER_OF_INPUTS; i++)
    {
        if (IsKeyDown(i))
        {
            uchar key = GetKey(i);
            if (IsMouseButtonCode(key))
            {
                buttons |= MouseButtonBit(key);
            }
        }
    }
    ReportBuffer[0] = ID_Mouse;
    ReportBuffer[1] = buttons;
    ReportBuffer[2] = mouse_x_count;
    ReportBuffer[3] = mouse_y_count;
    mouse_x_count = 0;
    mouse_y_count = 0;
    return 4;
}
#endif  // USE_MOUSE_DEVICE == 1

unsigned char BuildReport(unsigned char id)
{
    switch (id)
    {
    case ID_Keyboard:
        return ReportKeyboard();

    case ID_Consumer:
        return ReportConsumer();

#if NR_OF_JOYSTICKS >= 1
    case ID_Joystick4:
    case ID_Joystick3:
    case ID_Joystick2:
    case ID_Joystick1:
        return ReportJoystick(id);
#endif  // NR_OF_JOYSTICKS >= 1

#if USE_MOUSE_DEVICE == 1
    case ID_Mouse:
        return ReportMouse();
#endif  // USE_MOUSE_DEVICE == 1

    default:
        break;
    }
    return 0;
}
