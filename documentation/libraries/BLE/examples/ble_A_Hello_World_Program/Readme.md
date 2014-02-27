#ble_a_Hello_World_Program : Setup

The Hello_World_Program uses BLE to send a string, "Hello World, works", from the Arduino board to the peer Bluetooth low energy device.
The peer can be the nRF UART app running on iOS or Android or PC (See the Master Emulator -> Examples -> nRFUART, this is installed as part of the Master control panel Windows tool)

The Arduino IDE or equivalent and Arduino board are working. You can use the "Getting Started" pages on http://arduino.cc to get help and to troubleshoot.
Once you have confirmed that the Aduino board and IDE are working:
* Connect the nRF8001 to the Arduino (using either a shield or with direct wiring)
* Open the ble_a_Hello_World_Program sketch (.ino file) in the IDE or equivalent
* Verify that the pin connections are correct for the shield in the sketch.
This will vary depending on the shield that you use.  
  
<code>
    /*  
    Tell the ACI library, the MCU to nRF8001 pin connections.  
    The Active pin is optional and can be marked UNUSED  
    */  
    
    aci_state.aci_pins.board_name = //See board.h for details, Use REDBEARLAB_SHIELD_V1_1 or BOARD_DEFAULT
    aci_state.aci_pins.reqn_pin   = //SS for Nordic adapter shield , 9 for REDBEARLAB_SHIELD_V1_1 and REDBEARLAB_SHIELD_V2
    aci_state.aci_pins.rdyn_pin   = // 3 for Nordic adapter shield ,  8 for REDBEARLAB_SHIELD_V1_1 and REDBEARLAB_SHIELD_V2
    aci_state.aci_pins.mosi_pin   = MOSI;
    aci_state.aci_pins.miso_pin   = MISO;
    aci_state.aci_pins.sck_pin    = SCK;
    
    aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8; //This divides the input clock by 8 to get the SPI clock
      
    aci_state.aci_pins.reset_pin             = //4 for Nordic adapter shield, UNUSED for REDBEARLAB_SHIELD_V1_1, 4 or 7 or UNUSED for REDBEARLAB_SHIELD_V2
    aci_state.aci_pins.active_pin            = UNUSED;
    aci_state.aci_pins.optional_chip_sel_pin = UNUSED;
      
    aci_state.aci_pins.interface_is_interrupt  = false;
    aci_state.aci_pins.interrupt_number	       = 1;
</code>
* Click Upload in the Arduino IDE or equivalent to upload the sketch to the Arduino board.
Wait until the upload is successful.
* Open the Serial Monitor window using Tools -> Serial Monitor in the Arduino IDE
* Set the line ending option in the Serial Monitor to "New Line"
* Set the baud rate in the Serial Monitor to "115200 baud"

When the ble_a_Hello_World_Program runs successfully you will see:  
"  
Arduino setup  
Evt Device Started: Setup  
Evt Device Started: Standby  
Advertising started : Tap Connect on the nRF UART app  
"  
in the Serial Monitor.


##Troubleshooting:
If you only see "Arduino Setup" on the Serial Monitor, then verify that the pin connections on the shield or the nRF8001 module are correct.
Verify that all steps in the setup (see above) are done correctly.  
  
Note that the leonardo do not reset when you run the serial monitor, 
so you will not see the initial setup messages unless you add a delay in the code 
so you can open the serial monitor before the code is executed.

##Sending and Recieving data over BLE
Once the setup steps have been successfully completed. 
You can use the nRF UART iOS/Android app or the nRFUART PC Windows application. 
The nRFUART PC Windows application is installed when you install the Windows tool called 
master control panel (See Nordic Semiconductor -> Master Emulator -> <<Version number>> -> Example Code -> nRFUart )

Tap the Connect buttom on the nRF UART.
The text string "Hello World, works" is sent from the Arduino sketch over BLE using the nRF8001 and then printed in the nRF UART app.

You can now send and receive data using the Serial Monitor "Send" button and the nRF UART "Send" button.

##Using the Master Control Panel on the PC with the ble_a_Hello_World_Program

* Install the Master control panel, this Windows tool is available only on purchase of the nRF8001 Development kit
* Run the Master control panel
* Select the Master Emulator board from the pull down on the top left
* After the board has been identified by the software, click the "Device Discovery" button
* Click on the Device "Hello" -> then click Select Device.
* You will see a new screen
* Then click the "Service Discovery button"
* Wait for the Service Discovery to complete
* Click -> Enable Services to configure the BLE Service used for Hello World
* Click on the entry that says UART RX
* Then in the Value text box , type a value and then click "send update"
* This value is then sent over BLE , received by the Arduino and printed on the Serial Monitor

## Next steps
The ble_uart_project_template is the next program to be used to understand sending and receiving data over BLE.
The Hello World program is a clone of the ble_uart_project_template. 
The only addition is that the hello world program sends the "Hello World, works" as soon as the BLE is connected and configured.
