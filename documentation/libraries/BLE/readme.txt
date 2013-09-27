Bluetooth low energy API for Arduino (uses the nRF8001 from Nordic Semiconductor)
This has been tested using the Arduino UNO board and the nRF2740/nRF2741 module and the redbearlab Arduino shield.


Arduino UNO -> nRF2740 Wiring:
PIN3 -> RDYN
PIN4 -> RESET
PIN5 -> ACTIVE

PIN10 -> REQN/SS
PIN11 -> MOSI
PIN12 -> MISO
PIN13 -> SCK

3.3V -> VCC_nRF
GND  -> GND


On the nRF2740 board the connectors are 

1 - GND
2 - VCC_nRF
3 - ACTIVE
4 - Not in use
5 - SCK
6 - MOSI
7 - MISO
8 - RDYN
9 - REQN
10- RESET

The pin arrangement on the nRF2740

1 2
3 4
5 6
7 8
9 10

Contents:
BLE folder contains the ported bluetooth library. This folder (BLE) should be extracted into the arduino libraries folder. This contains the ACI library. 

BLE_arduino_demos should be placed outside the Arduino install folder.

The I/O lines between the Arduino and the nRF8001 can be connected directly. Using a 5v Arduino directly with the nRF8001 will eventually destroy the nRF8001 over time and possibly lead to undefined behavior.

Note: The Arduino is usually a 5v chip, so depending on you board, you might have to use level converters or a resistive divider to get the voltage to 3.3v for the lines that are output from Arduino to the nRF8001.

Make sure you always run the run_me_compile_xml_to_nRF8001_setup.bat with the nRFgo studio installed on a Windows PC to generate the setup required for the nRF8001 (services.h). You need to run this again whenever you change the configuration in the nRFgo studio.

Using the nRF8001 SDK for Arduino with the Redbear lab shield
=============================================================

Get the code for the nRF8001 SDK for Arduino from the developer.bluetooth.org
https://forumarchive.bluetooth.org/pages/forum.aspx?action=ViewPosts&fid=6&tid=63



Unzip and extract the files in the zip file of the latest release

Copy the BLE folder to the libraries folder in the Arduino installation

Copy the BLE_arduino_demos_latest to a folder outside the Arduino installation

-----

On the BLE shield connected to the Arduino UNO:

1. Put the default handshaking switch to off

2. Connect Pin 3 of the Arduino to the RDYN (on the shield) with a wire

3. Connect Pin 4 of the Arduino to the RESET_RF (on the shield) with a wire

4. Connect Pin 10 of the Arduino to REQN (on the shield) with a wire

-----

In hal_aci_tl.cpp in the BLE folder go to hal_aci_tl_init()

Remove:

digitalWrite(HAL_IO_RADIO_RESET, 1);

digitalWrite(HAL_IO_RADIO_RESET, 0);

digitalWrite(HAL_IO_RADIO_RESET, 1);

Add the below lines in the same location as the 3 removed lines :

digitalWrite(HAL_IO_RADIO_RESET, 1);

delay(100);

digitalWrite(HAL_IO_RADIO_RESET, 0);

-----

You can now use the ble_uart_project_template Arduino example with the nRF UART application in the Apple app store.

Click on the Serial monitor in the Arduino IDE to start the example.

You should be able to type messages on the iPhone and get them printed on the Arduino Serial Monitor

Note: The nRF UART works only on iPhone 4S and above, iPad 3 and above and iPad mini and above.

You can also use the lightBlue app in the Mac OS X app store and the iOS app store.
