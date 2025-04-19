![img](/img/bitlace.png)
# BitLace
Bitlace - is a simple drawing application for MAX7219 8x8 led display and ESP32. Just connect to a wifi access point and you are ready to draw!
Tested on ESP32-C3.
## Building
To build the application, run ```build_page.sh``` and then use ```Build Filesystem Image``` and ```Upload Filesystem Image``` project tasks on platformIO. Then upload the sketch.
## Settings 
Settings are located in ```src/settings.h```. You can setup pins and display color here. Also you can specify your AP credentials.

### By Glutesha Devices :D