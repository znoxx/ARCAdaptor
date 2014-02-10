This is based on the following project:
http://code.rancidbacon.com/ProjectLogArduinoUSB
https://code.google.com/p/vusb-for-arduino/

Changes introduced:
Pins for USB assigned to ARCAdatptor's ones.
V-USB stack updated to latest version
No need of separate object compilation, as stated in original README (thanks to Arduino 1.x)

Tested on MAC and partially on Windows.

TODO: Meaningfull comments.

10-Feb-2014: Added patch for HIDSerial (https://github.com/rayshobby/hid-serial https://rayshobby.net/?p=7363)
03-Feb-2014: Added sendBuffer method for usbKeyboard to support buffered output
