#ble-sdk-arduino

Bluetooth low energy SDK for Arduino (uses the nRF8001 from [Nordic Semiconductor](https://www.nordicsemi.com/ "Go to Nordic semiconductors homepage")). 
This has been tested using the Arduino UNO, Mega and Leaonardo boards with the nRF2740/nRF2741 module or the Bluetooth low energy shield from RedBearLab. 
The shield is available from seeedstudio and makershed.

##Contents
The folder \src\ contains the ported bluetooth library (ACI library) and an example project folder \examples\.
This SDK should be extracted or import into the Arduino "libraries" folder.

* See [this](http://www.arduino.cc/en/Guide/Libraries) for more details about installing libraries.

####Start using the SDK
1. Download the SDK by clicking "Download ZIP" at the bottom of the right side menu.
2. In the arduino IDE, click 'Sketch' and choose 'Import library' and 'Add .ZIP Library...'
3. Choose the zip file just downloaded to import.

####When using the Bluetooth low energy shield v.1.1 or v.2012.07:
Plug the Bluetooth low energy shield onto the Arduino. Set the "Default Handshaking" switch to ON.
The nRF8001 REQN is on Digital 9 of the Arduino. The nRF8001 RDYN is on Digital 8 of the Arduino.
The SPI lines are routed through the central ICSP connector of the Arduino.
To change the REQN and RDYN line to a different Arduino pin, set the "Default Handshaking" switch to OFF, wire the nRF8001 pins on the shield at J5 to the required Arduino pin.

####When using the Bluetooth low energy shield v.2.0:
Plug the Bluetooth low energy shield to the Arduino.
The REQN and RDYN pins are selectable from pin 2 to 12. 
Select the Arduino pins to use for REQN and RDYN and put the jumpers to those pins. 
Reset of the Arduino is connected to the Reset of the nRF8001, so every time a sketch is downloaded from the Arduino IDE the nRF8001 is also reset.
The SPI lines are routed through the central ICSP connector of the Arduino.

####When using the nRF2740/nRF2741 modules directly wired to the Arduino:
When the Arduino uses a 5v microcontroller,you may have to use level converters or a resistive divider to get the voltage to 3.3v for the lines that are output from Arduino to the nRF8001.
The Arduino(3.3v-1.9v) or the Arduino DUE can be wired directly to the nRF8001 without any level converters or resistive dividers.

####When using the nRF2740/nRF2741 modules with the nRF8001/nRF24L01+ shield adapter for Arduino:
Plug the nRF8001/nRF24L01+ shield adapter for Arduino to the Arduino.
The nRF8001 RDYN is on Digital 3. The nRF8001 REQN is on Digital 10.
The SPI lines are available on Digital 11, 12, 13 and the central ICSP connector.
To change the REQN and RDYN line to a different Arduino pin, cut the track on the PCB connecting the lines and wire the nRF8001 pins on the shield adapter at P10 to the required Arduino pin.

####Configure the MCU to nRF8001 PIN connection
    aci_state.aci_pins.board_name = 
    //See board.h for details, Use REDBEARLAB_SHIELD_V1_1 or BOARD_DEFAULT
    
    aci_state.aci_pins.reqn_pin   = 
    //SS for Nordic adapter shield , 9 for REDBEARLAB_SHIELD_V1_1 and REDBEARLAB_SHIELD_V2
    
    aci_state.aci_pins.rdyn_pin   = 
    // 3 for Nordic adapter shield ,  8 for REDBEARLAB_SHIELD_V1_1 and REDBEARLAB_SHIELD_V2
    
    aci_state.aci_pins.mosi_pin   = MOSI;
    aci_state.aci_pins.miso_pin   = MISO;
    aci_state.aci_pins.sck_pin    = SCK;
    
    aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8; //This divides the input clock by 8 to get the SPI clock
      
    aci_state.aci_pins.reset_pin             = 
    //4 for Nordic adapter shield, UNUSED for REDBEARLAB_SHIELD_V1_1, 4 or 7 or UNUSED for REDBEARLAB_SHIELD_V2
    
    aci_state.aci_pins.active_pin            = UNUSED;
    aci_state.aci_pins.optional_chip_sel_pin = UNUSED;
      
    aci_state.aci_pins.interface_is_interrupt  = false;
    aci_state.aci_pins.interrupt_number	       = 1;

####Modifying existing nRF8001 configuration:
Make sure you always run the run_me_compile_xml_to_nRF8001_setup.bat with the nRFgo studio installed on a Windows PC to generate the setup required for the nRF8001 (services.h). 
You need to run this again whenever you change the configuration in nRFgo studio.  
  
The nRFgo studio is a Windows program that can be run on the OS X using playonmac (tested) and could also be run on Linux using playonlinux (not tested).

####Porting ACI Library
A brief explanation of how to port the ACI library code is available in [/documentation/libraries/BLE](./documentation/libraries/BLE/nRF8001-Porting-ACI-Library.md "Go to document") 

##Forum
[Nordic Developer Zone](http://devzone.nordicsemi.com/ "Go to nordic developer zone")

##Resources
[Arduino](http://arduino.cc/ "Go to Arduino.cc")  
[nRF8001](https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF8001 "Go to product")  
[RedBearLab BLE Shield from MakerShed](http://www.makershed.com/Bluetooth_Low_Energy_BLE_Shield_for_Arduino_p/mkrbl1.htm "Go to product")  
[RedBearLab BLE Shield from SeeedStudio](http://www.seeedstudio.com/depot/bluetooth-40-low-energy-ble-shield-v20-p-1631.html "Go to product")  
