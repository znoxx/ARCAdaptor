This folder contains ARCAdaptor patch for HIDSerial Library.
https://rayshobby.net/?p=7363
https://github.com/rayshobby/hid-serial
Copy of master branch (10-Feb-2014) is included

To apply - download original HIDSerial and setup in Arduino IDE
Apply the patch - copy .patch file to library dir and run:
#patch --dry-run -p1 -i usbconfig.hidserial.patch
if everything is ok (no errors)
#patch  -p1 -i usbconfig.hidserial.patch

