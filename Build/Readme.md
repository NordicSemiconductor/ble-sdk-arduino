# Documentation for using the Arduino Makefile

This Arduino makefile is based on the one from Sudar. For more details please refer

https://github.com/sudar/Arduino-Makefile

This is just a quick guide. In addition to the steps explained on Sudar's manual this readme file explains some recommended settings.

It is important to mention that this Makefile was tested on a Windows platform. The following are the extra steps recommended for using the Arduino Makefile.

*	[Install Cygwin](#install-cygwin)
*	[Install extra components for Cygwin](#Install-extra-components-for-cygwin)
*	[Create symbolic link for the Arduino Folder](#Create-symbolic-link-for-the-arduino-folder)
*	[Modify or create environmental variables](#Modify-or-create-environmental-variables)
*	[Make each BLE example](#Make-each-ble-example)
*	[Python scripts](#Python-scripts)

## Install Cygwin

In order to run this makefile on Windows it is recommended to install Cygwin as well as its Make utility.

----

## Install extra components for Cygwin

The extra tools that have to be installed into Cygwin for using this Makefile are:

*	make
*	perl
*	python 
*	perl package `Device::SerialPort`

For installing this extra tools please open again the Cygwin installer and when it asks you to select which packages to be installed select the ones mentioned above.

----

## Create symbolic link for the Arduino Folder

A symbolic link should be created for the Arduino folder in case your default installation folder has either spaces or special characters such as "(". For creating the symbolic link you have to use the command:

`mklink`

on the windows command prompt. This is very useful on Windows as sometimes the Make utility will have problems when dealing with the windows naming conventions for folders.

----

## Modify or create environmental variables

The variables that have to be set are mainly:

```Makefile
BOARD_TAG=mega2560
MONITOR_PORT=com3
ARDMK_DIR=/cygdrive/c/Users/"Your_user"/Arduino-Makefile
ARDUINO_DIR=../../../../../Arduino
```
The ARDMK_DIR variable is the location where this Makefile was downloaded.
AVR_TOOLS_DIR is optional. If you use the default tools from the Arduino folder you do not have to set this variable as the makefile will detect it. Its default value should be:
```Makefile
AVR_TOOLS_DIR=../../../../../Arduino/hardware/tools/avr
```
When you define this environmental variables it is important to set them to be relative. Otherwise the Makefile will not work properly.

----

## Make each BLE example

You can make each BLE example. To do this, first open the Cygwin console. Go to the folder where the example is located and type `make`.

In order to upload the just made file type `upload`. For further details go to the Sudar's manual description


----

## Python scripts

There are two python scripts within this folder that can make and upload all the BLE examples to the Arduino.

For using these two files, first go to the folder called `Build`. For making all the examples type `python BuildBLE.py` and for flashing all of them type `python FlashBLE.py`

----
