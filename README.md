![](doc/img/project-logo.png)
# SignalK marine instruments based on Panlee SC01 Plus device

(AKA Poor man's boat instruments)


![](doc/img/screens-all.png)

The main aim of this project is to create cheap sets of sailing vessel :sailboat: instruments (indicators).
Cheap and available Panlee SC01-Plus is used as dispaly. It has relatively large TFT panel and quite powerfull ESP32 core.

Quick video demo of this display:

[![SC01 Plus instruments demo](https://img.youtube.com/vi/M-gK7Ye0CGY/0.jpg)](https://www.youtube.com/watch?v=M-gK7Ye0CGY)


Unfortunatelly this screen is not waterproof so it can't be used outside but only as an extra display inside the boat.

![Panlee SC01 Plus display](doc/img/sc01-plus.png)


This project is based on [SignalK SensESP](https://github.com/SignalK/SensESP) project, [LVGL](https://github.com/lvgl/lvgl) and [LovyanGFX](https://github.com/lovyan03/LovyanGFX) graphics libraries.

## How to flash to SC01 Plus.
1. Install [VS code](https://code.visualstudio.com/download).
2. Install [PlatformIO plugin](https://platformio.org/install/ide?install=vscode).
3. Clone repository.
4. in [main.cpp](src\main.cpp) lines 57-58 you can update display name prefix and password for captive portal (initial WiFi setup portal).
Device name will be combined from prefix followed by MAC address.
5. Unfortunatelly SC01Plus is not in the predefined boards list so few parameters are redefined over generic "um_tinys3" board definition in [platformio.ini](src\platformio.ini) file (and board most likely won't be added due to political shit from Espressif)
6. Go to PlatformIO plugin, select upload port and click on "Upload" task. Firmware will be compiled and flashed.

![](doc/img/platformio.png)

## How to Setup.
After flashing you will see spinner for few seconds along with "Factory reset" button.

![](doc/img/screen-splash-start.png)

If you set something wrong it is your chance after reboot to press this button and start configuration from scratch.

Next you will see this screen:

![](doc/img/screen-splash-howtoconnect.png)

It will tell you WiFi AP name and password. Use your mobile phone (laptop or tablet), connect to that AP using provided password.
After connection you will be redirecter to Captive portal (to set WiFi setting)

![](doc/img/captive-portal.png)

Here you should select your boar WiFi network where your SKServer is running (only 2.4GHz networks are supported by SC01).
Click "Configure WiFI", select your WiFi network (or enter SSID manually), set password and click "Save".
On that screen you can change network device name as well and it is better to keep it unique.
Please note, if you won't connect to WiFi within 3 mins device will ~~shit~~ reset itself and you'll have to start over.
Once password is saved you will be disconnected from portal and device will attempt to connect to selected network. 
If device is unable to connect to WiFi you can connect to captive portal again and set correct WiFi connection parameters.
In case of successfull connection status screen will show device IP address and SK Server connection status.

![](doc/img/screen-splash-connection-status.png)

Now we need to connect to SignalK server. There are two ways to connect:
1. Using mDNS service
2. Set connection details in Web interface.

* **mDNS service**

    If SKServer address is not defined in Web portal display will try to use mDNS service to find SK Server in your network.
To use this method you have to enable mdns chackbox in SK Server configuration "Server->Settings->Server Settings-> mdns ON"
It will take 5-10sec to discover server and establish connection. This method likely won't work if you are running SignalK Server
in Docker container (unless you open additional ports, but I have not tried it).

* Connection details in Web interface.

    Navigate to IP adress dispalyed on splash screen, f.e. http://10.0.0.27 (or whatever is dispalyed on splash screen, insecure http connection, not https)
You will see 3 tabs: Status, Configuration, Control

![](doc/img/web-interface-config.png)

Open Configuration tab, scroll to "System/Signal K Settings" section, set address, port and save settings. Device will restart.

After setting connection to SKServer display will "stuck" in "Authorizing with SignalK" status.
At this point you have to connect to your SignalK server, open "Security->Access request" where you will find device that is 
trying to connect. Select requred device (you've set unique names for all your devices, right?), select Read/Write as Permissions and "NEVER" as expiration.

![](doc/img/signalk-access-request.png)

If device authorized in SignalK but still show "Authorizing..." status you may try to power cycle display manually.

After sucessfull authorization with SignalK server device will show default "Wind" page and start to receve data.

![](doc/img/screen-wind.png)


## List of indicators and SignalK data pathes:

**Wind page**
| Indicator | SignalK data path |
| ----------- | ----------- |
|Turquoise dial| environment.wind.angleApparent|
|Yellow dial| environment.wind.angleTrueGround|
|AWS(kt)| environment.wind.speedApparent|
|TWS(kt)| environment.wind.speedTrue|
|TWD| environment.wind.directionTrue|
|AWA (turquoise)| environment.wind.angleApparent|
|TWA (yellow)| environment.wind.angleTrueGround|


**Tridate page**
| Indicator | SignalK data path |
| ----------- | ----------- |
|Heading (M)| navigation.courseOverGroundMagnetic
|Depth(m)| environment.depth.belowTransducer
|Speed(kt)| navigation.speedThroughWater


**Compass page**
| Indicator | SignalK data path |
| ----------- | ----------- |
|Compas dial rotation, 3 digits top label| navigation.courseOverGroundMagnetic|
|GPS Speed(kt)| navigation.speedOverGround|
|Depth(m)| environment.depth.belowTransducer|



## Connecting/programming/debugging.

For Flashing and debugging external "debug" board is used (it is just USB to RS232 converter with couple buttons). It is connected to device "debug" port.

![](doc/img/display-debugger-rs232.png)

Physically it is connecting to Serial0 (Tx0, Rx0) interface of the ESP chip. While onboard USB connector is creating virtual serial port.
All debug information (debugD or Serial.print) are sent to virtual "Serial" port alias (without number).
So if you want to connect to the display using external USB->RS232 board you have to set in "platformio.ini" file:

    -D ARDUINO_USB_MODE=0
    -D ARDUINO_USB_CDC_ON_BOOT=0

In this case virtual "Serial" port will be connected to physical Serial0 (Tx0, Rx0) interface.
If you are connecting to the board using onboard USB connector you need to set

    -D ARDUINO_USB_MODE=1
    -D ARDUINO_USB_CDC_ON_BOOT=1

In this case virtual "Serial" port will be connected to onboard USB interface.

You can flash using either connection method.
But there are some advantages using external "debug" board:
1. USB is connected permanently to your PC and when you restart board (press reset button) you'll start to receive output immidiately. If you 
 are connected via onboard USB after reset you will have to wait till your PC discover new USB device, install driver and create virtual COM port device, only then you can start serial monitor.
 So you will loose first 15-20 sec of logs. This can be partially solved by adding 10-20 sec delay as first command in setup() function.
2. If you are connecting and flashing via onboard USB then due to hardware limitation after flashing you have to reset device manually, programmatic reset does not work.
3. If you have flashed something incorrect to the device and it does not start anymore and you need to boot into bootloader and there is a "bootloader" button on "debug" board but in case of onboard USB you have to short 
"boot" pin to the ground on the debug connector during powering process.

During programming flash memory is erased not completely, SPIFFS partition is left intact. So if you have problem with changing WIFI AP name/password or SK Server connection you can either 
click "Factory reset" on startup screen, select Factory reset in WEB interface. This will delete all settings and passwords and bring device into the initial setup mode.
To clean device completely execute "Erase flash" task in PlatformIO (which is equel to command "esptool --chip esp32-s3 -p COM1 erase_flash") and flash again.



## Updaing graphics/Squareline

All UI files generated by [Squareline studio](https://squareline.io/downloads) are located in **/src/ui** subfolder.

How to update graphics:
1. Download and install Squareline sudio. Personal free license is enough to modify this simple content.
2. Open project from SquareLineProject subfolder.
3. Set these project settings
![](doc/img/squareline-project-settings.png)
4. Point **Project Export Root** and **UI Files Export Path** to some temporary location.
5. Make changes, save project.
6. Use menu Export -> Export UI files
7. Delete all files from **/src/ui** subfolder
8. Copy all files from temporary location set in #4 to **/src/ui** folder
9. Build and upload project

