# EEPROM online editor for ARCAdaptor
This folder contains code for hosted EEPROM editor, used in ARCAdaptor projects

Requirements:

* Almost any web server, capable running perl CGI
* CGI.pm available in your Perl modules

Installation

* Edit eeprom.cgi and set correct Perl interperter path
* If your webserver allows running cgi-scripts from subfolder (not from /cgi-bin), just open http://your_host/path/to/data/eeprom.html - you should be done
* If your webserver _does not_ allow running cgi-scripts from particular place, put eeprom.cgi to cgi-bin folder and edit path in eeprom.html



