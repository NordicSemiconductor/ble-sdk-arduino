#ble-sdk-arduino

Bluetooth low energy SDK for Arduino (uses the nRF8001 from Nordic Semiconductor)
This has been tested using the Arduino UNO, Mega, Leaonardo boards and the nRF2740/nRF2741 module or the Bluetooth low energy shield from Redbearlab. The shield is available from seeedstudio and makershed.

##Contents
The BLE folder in \libraries\ contains the ported bluetooth library. This folder (BLE) should be extracted into the arduino libraries folder. This contains the ACI library. 

The demos folder contains example projects and should be placed outside the Arduino install folder.

When using the Bluetooth low energy shield v.1.1 or v.2012.07:
Plug the Bluetooth low energy shield to the Arduino. Set the "Default Handshaking" switch to ON.
The nRF8001 REQN is on Digital 9 of the Arduino. The nRF8001 RDYN is on Digital 8 of the Arduino.
The SPI lines are routed through the central ICSP connector of the Arduino.
To change the REQN and RDYN line to a different Arduino pin, set the "Default Handshaking" switch to OFF, wire the nRF8001 pins on the shield at J5 to the required Arduino pin.

When using the Bluetooth low energy shield v.2.0:
(To be added)

When using the nRF2740/nRF2741 modules directly wired to the Arduino:
When the Arduino uses a 5v microcontroller,you may have to use level converters or a resistive divider to get the voltage to 3.3v for the lines that are output from Arduino to the nRF8001.
The Arduino(3.3v-1.9v) or the Arduino DUE can be wired directly to the nRF8001 without any level converters or resistive dividers.

When using the nRF2740/nRF2741 modules with the nRF8001/nRF24L01+ shield adapter for Arduino:
Plug the nRF8001/nRF24L01+ shiled adapter for Arduino to the Arduino.
The nRF8001 RDYN is on Digital 3. The nRF8001 REQN is on Digital 10.
The SPI lines are available on Digital 11, 12, 13 and the central ICSP connector.
To change the REQN and RDYN line to a different Arduino pin, cut the track on the PCB connecting the lines and wire the nRF8001 pins on the shield adapter at P10 to the required Arduino pin.


Modifying existing nRF8001 configuration:
Make sure you always run the run_me_compile_xml_to_nRF8001_setup.bat with the nRFgo studio installed on a Windows PC to generate the setup required for the nRF8001 (services.h). You need to run this again whenever you change the configuration in nRFgo studio.

The nRFgo studio is a Windows program can be run on the OS X using playonmac (tested) and could also be run on Linux using playonlinux (not tested).

##Forum
[Nordic Developer Zone](http://devzone.nordicsemi.com/ "Go to nordic developer zone")

##Resources
[Arduino](http://arduino.cc/ "Go to Arduino.cc")  
[nRF8001](https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF8001 "Go to product")  
[RedBearLab BLE Shield from MakerShed](http://www.makershed.com/Bluetooth_Low_Energy_BLE_Shield_for_Arduino_p/mkrbl1.htm "Go to product")  
[RedBearLab BLE Shield from SeeedStudio](http://www.seeedstudio.com/depot/bluetooth-40-low-energy-ble-shield-p-1255.html "Go to product")  
