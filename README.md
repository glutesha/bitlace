![img](/img/bitlace.png)
# BitLace
Bitlace is a DIY retro decoration featuring a monochrome MAX7219 8x8 dot display and an ESP32. You can draw on the display using the website, which is running inside a wifi hotspot made by the board. Tested on ESP32-C3 boards like SEEED XIAO and ESP32-C3 super mini. Very WIP.
## Interface
<img src="/img/interface1.jpg" height=600/> <img src="/img/interface2.png" height=600/>
## Building
To build the application, run ```build_page.sh``` and then use ```Build Filesystem Image``` and ```Upload Filesystem Image``` project tasks on PlatformIO. Then use ```Upload```. If your display starts showing the logo, it means that everything went smoothly.
## Settings 
Default settings are located in ```src/settings.h```. You can set up pins and display color here. Also, you can specify your AP credentials. You can also set up your device via the settings page in the web interface.
## Technologies
The main firmware, located in ```/src```, is written in C++ using the Arduino framework and libraries like ```U8G2```, ```ArduinoJson```, ```ESPAsyncWebServer```, and more. The frontend, located in ```front``` was written in HTML and TypeScript using ```Svelte``` and ```TailwindCSS```. Pretty heavy for an embedded board with only 4 megabytes of storage, but it works!
