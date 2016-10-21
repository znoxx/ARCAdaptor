## V-USB Joystick Example

This project is derived from the https://github.com/gblargg/vusb-joystick.
Since original ZX joystick  firmware is gone (http://narod.ru/disk/1762604000/ZX_USBJoy_20071020.zip.html) - this one will be a good illustration to connect simple joystick to ARCAdaptor USB.

### Changes introduced:
* Pins moved to PORTB completely to avoid conflicts with existing USB connection (PD0/PD2)
* Amount of buttons reduced to 2 (instead of 8), since, well it's not easy to find ZX joystick with more than 2 buttons :)
& USB stack updated to latest version.

#### Pinout of ARCAdaptor/ATMega connection 

Up - X1-3/PB4

Down - X1-1/PB5

Left - X2-13/PB2

Right - X2-15/PB3

Fire1 - X2-5/PB0

Fire2 - X2-11/PB1
