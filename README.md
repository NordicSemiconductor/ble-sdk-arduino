#ble-sdk-arduino

Bluetooth low energy SDK for Arduino (uses the nRF8001 from Nordic Semiconductor)
This has been tested using the Arduino UNO board and the nRF2740/nRF2741 module and the redbearlab Arduino shield.

##Contents
The BLE folder in \libraries\ contains the ported bluetooth library. This folder (BLE) should be extracted into the arduino libraries folder. This contains the ACI library. 

The demos folder contains example projects and should be placed outside the Arduino install folder.

The I/O lines between the Arduino and the nRF8001 can be connected directly. Using a 5v Arduino directly with the nRF8001 will eventually destroy the nRF8001 over time and possibly lead to undefined behavior.

Note: The Arduino is usually a 5v chip, so depending on you board, you might have to use level converters or a resistive divider to get the voltage to 3.3v for the lines that are output from Arduino to the nRF8001.

Make sure you always run the run_me_compile_xml_to_nRF8001_setup.bat with the nRFgo studio installed on a Windows PC to generate the setup required for the nRF8001 (services.h). You need to run this again whenever you change the configuration in nRFgo studio.

##Forum
[Nordic Developer Zone](http://devzone.nordicsemi.com/ "Go to nordic developer zone")

##Resources
[Arduino](http://arduino.cc/ "Go to Arduino.cc")  
[nRF8001](https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF8001 "Go to product")  
[RedBearLab BLE Shield from MakerSHED](http://www.makershed.com/Bluetooth_Low_Energy_BLE_Shield_for_Arduino_p/mkrbl1.htm "Go to product")  
[RedBearLab BLE Shield from seeed](http://www.seeedstudio.com/depot/bluetooth-40-low-energy-ble-shield-p-1255.html "Go to product")  
