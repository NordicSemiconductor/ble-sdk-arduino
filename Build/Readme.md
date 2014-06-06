# Documentation for using the Arduino Makefile

This Arduino makefile is based on the one from Sudar. For more details please refer

https://github.com/sudar/Arduino-Makefile

or this other guide.

http://hardwarefun.com/tutorials/compiling-arduino-sketches-using-makefile

This is just a quick guide. In addition to the steps explained on Sudar's manual this readme file explains some recommended settings.

It is important to mention that this Makefile was tested on a Windows platform. The following are the extra steps recommended for using the Arduino Makefile.

*	[Install Cygwin](#install-cygwin)
*	[Install extra components for Cygwin](#Install-extra-components-for-cygwin)
*	[Create symbolic link for the Arduino Folder](#Create-symbolic-link-for-the-arduino-folder)
*	[Modify or create environmental variables](#Modify-or-create-environmental-variables)
*	[Modify each makefile from each example](#Modify-each-makefile-from-each-example)
*	[Make each BLE example](#Make-each-ble-example)
*	[Python scripts](#Python-scripts)

## Install Cygwin

In order to run this makefile on Windows it is recommended to install Cygwin as well as all its packages which are selected by defualt.

----

## Install extra components for Cygwin

For installing the extra tools required please open again the Cygwin installer and when it asks you to select which packages to be installed select the ones mentioned below. The extra tools that have to be installed into Cygwin for using this Makefile are:

*	**gcc**: Install gcc in case it was not selected as a default package. Gcc is under the package "D-Level". Also install all the options that say Make from the "Debug" package. If you type "gcc" in the search box you will find all of them.
*	**make**: This utility is under the package "D-Level". Also install all the options that say Make from the "Debug" package. If you type "Make" in the search box you will find all of them.
*	**perl**: This is a package itself, so just click next to its name to change the configuration from Default to Installed.
*	**python**: This is a package itself, so just click next to its name to change the configuration from Default to Installed. 
*	**perl module `Device::SerialPort`**: For installing this module there are two options, you can download it from this webpage :

http://search.cpan.org/~cook/Device-SerialPort-1.04/SerialPort.pm

or install it simply with the command:

  `cpan Device::SerialPort`

if you're on Ubuntu or Debian-like distributions:

    `sudo apt-get install libdevice-serialport-perl`

If you downloaded the package in order to install it first you have to unpack it, and then inside the folder it has you have to run the following commands:

	perl Makefile.PL
	make
	make test
	make install

This other github repository explains the use of this module in case you are interested on knowing more about how to use it.  

https://github.com/syxanash/Device-SerialPort-Arduino

----

## Create symbolic link for the Arduino Folder

A symbolic link should be created for the Arduino folder(Folder where the Arduino IDE and other tools are installed on your computer) in case your default installation folder has either spaces or special characters such as "(". For example, if your Arduino directory is in:

    c:\Program Files (x86)\Arduino

You will get problems with the special characters on the directory name. More details about this can be found in [issue #94](https://github.com/sudar/Arduino-Makefile/issues/94)

To create a symbolic link, you can use the command “mklink” on the windows command prompt, e.g.

    mklink /d c:\Arduino c:\Program Files (x86)\Arduino

After this the envorimental variables used should be:

    ARDUINO_DIR=../../../../../Arduino

Instead of:

    ARDUINO_DIR=../../../../../Program\ Files\ \(x86\)/Arduino


This is very useful on Windows as sometimes the `Make` utility on Cygwin will have problems when dealing with the windows naming conventions for folders.

----

## Modify or create environmental variables

In order for this Makefile to work, some enviromental variables have to set either on Windows or on Cygwin. For doing this on Windows from the Desktop, right-click My Computer and click Properties. Click Advanced System Settings link in the left column. In the System Properties window click the Environment Variables button. Now you can add new variables or modify the value of the old ones.

In Cygwin you have to execute the command `export` for defining a new enviromental variables and `unset` for deleting it. Further details can be found on:

http://cygwin.com/cygwin-ug-net/setup-env.html

All of this variables are recommended to be set on Windows. The variables that have to be set are mainly:

```Makefile
BOARD_TAG=mega2560
MONITOR_PORT=com3
ARDMK_DIR=/cygdrive/c/Users/"Your_user"/Arduino-Makefile
ARDUINO_DIR=../../../../../Arduino
```
The ARDMK_DIR variable is the location where this Makefile was downloaded. The value of this variable will change depending on the location in your computer where the Arduino Makefile was downloaded.

AVR_TOOLS_DIR is optional. If you use the default tools from the Arduino folder you do not have to set this variable as the makefile will detect it. Its default value should be:
```Makefile
AVR_TOOLS_DIR=../../../../../Arduino/hardware/tools/avr
```
When you define this environmental variables it is important to set them to be relative. Otherwise the Makefile will not work properly.

----

## Modify each makefile from each example

The Build process is the next. 

* Go to the folder example you want to compile and type `make`. 
* On each example there is a makefile that calls the main makefile located on this Build folder.
* The main Makefile will compile the example based on some information provided by the Makefile located on each example folder.

In case you want to compile and test all the examples, then:

* Go to the Build folder and type the mentioned python commands below in the [Python scripts](#Python-scripts).
* This python script will go sequentially through all the examples and compile each one.

In order to compile any of the two options mentioned above. You have to modify each make file for each example. This make file has variables which were defined previously and overwrites them. The makefile has comments and it is self-explanatory.

----

## Make each BLE example

You can make each BLE example. To do this, first open the Cygwin console. Go to the folder where the example is located and type `make`.

In order to upload the just made file type `upload`. For further details go to the Sudar's manual description


----

## Python scripts

There are two python scripts within this folder that can make and upload all the BLE examples to the Arduino.

For using these two files, first go to the folder called `Build`. For making all the examples type `python BuildBLE.py` and for flashing all of them type `python FlashBLE.py`

----
