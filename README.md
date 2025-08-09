

# <img src="/img/bitlace.png" height=25/> Bit::lace ![hackatime](https://hackatime-badge.hackclub.com/U091LS2TL8M/bitlace)  
Bitlace is a DIY retro decoration featuring a monochrome MAX7219 8x8 dot display and an ESP32. You can draw on the display using the website, which is running inside a wifi hotspot made by the board. Tested on ESP32-C3 boards like SEEED XIAO and ESP32-C3 super mini. 

<img src="/img/irl_pic.jpg" />


## Usage
Interfacing with the device relies on a tactile button (Connected to ground, defined in settings).
Press it once to wake the device up for web interface access and programming. Press it again to put it to sleep, and show the last state with set brightness. 
Pressing the button for 2 seconds causes the device to completely turn off. Press it again and device will wake up back to the active state.       

Device's battery info relies on the ```Battery.h``` library. Pins for the battery and the resistance ratio is defined in the settings menu.      

When active, you can draw on it, save and load your drawing, set it up using the settings page and many more by going to the device's Wi-Fi hotspot and using the web interface. Web interface automatically opens as a captive portal, but i would recommend you to go to ```bitlace.local``` or ```192.168.4.1``` to use features like exports and imports for the gallery.
## Interface
<img src="/img/interface1.png" height=600/> <img src="/img/interface2.png" height=600/> <img src="/img/interface3.png" height=600/> <img src="/img/interface4.png" height=600/> <img src="/img/interface5.png" height=600/>
## Building
I built my device's hardware on a breadboard, but feel free to make a circuit board and PR me. I used the SEEED XIAO ESP32-C3 specifically because it has a built in battery controller and charger. I've also used a tactile button to switch between modes and turn off the device. I could make a schematic, but everything is very simple and customizable, so feel free to build this device to your taste and preferences. I've also uploaded my case 3D model in the ```/parts``` folder.     

To build the application, run ```build_page.sh``` and then use ```Build Filesystem Image``` and ```Upload Filesystem Image``` project tasks on PlatformIO. Then use ```Upload```. If your display starts showing the logo, it means that everything went smoothly.
## Settings 
Default settings are located in ```src/settings.h```. You can set up pins, AP credentials, display color, battery preferences, etc. You can also set up your device via the settings page in the web interface. Default AP credentials are ```bitlace-gluten``` and ```supersecretpassword```.
## Technologies
The main firmware, located in ```/src```, is written in C++ using the Arduino framework and libraries like ```U8G2```, ```ArduinoJson```, ```ESPAsyncWebServer```, and more. The frontend, located in ```front``` was written in HTML and TypeScript using ```Svelte``` and ```TailwindCSS```. Pretty heavy for an embedded board with only 4 megabytes of storage, but it works!
