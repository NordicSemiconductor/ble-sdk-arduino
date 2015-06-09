#BLE Library

This library enables communication between Nordic Semiconductor's nRF8001 <em>Bluetooth</em>&#174; low energy (BLE) chip and an Arduino board.The functionality of the library is based on the ACI commands and Events of nRF8001 as described in the nRF8001 Product Specification(http://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF8001).

The SPI master interface of the Arduino is used to communicate to the nRF8001 SPI slave. The library allows you to set the pins that are connected to the nRF8001. The optional nRF8001 pins that are not connected should be set to UNUSED. The library also allows you to set the clock divider for the SPI master. The nRF8001 supports a maximum SPI clock of
3 MHz. The library does not check for this limit and the user of the library must ensure that this is set correctly.

The libray can be used in polled mode or in interrupt mode. 

The Arduino pin connected to the RDYN line can be set a wakeup source for the Arduino. This is useful when the Arduino goes to sleep to save power. This should be done by the user of the library, as the library itself does not support this feature.

The RDYN line of the nRF8001 device is an signal from the nRF8001, when nRF8001 has information for the Arduino.

If you use this library you cannot use the pins used for REQN, RDYN and ACTIVE for other devices/actions. The SPI pins can be shared with other SPI slave devices. The Arduino can use only one of the SPI slave devices at any given time. The Arduino should select the slave device by using the SS line of the slave device. The SS line of the nRF8001 device is the REQN line.

The library includes workarounds for the Redbearlab v1.1 and v2012.07 Arduino shields (REDBEARLAB_SHIELD_V1_1) as these did not use the Reset line of the nRF8001. The Redbearlab v2.0 Arduino shield addresses this issue and does not require the work arounds. The work arounds are turned on by looking at the board_name.

##Set up

You need the BLE SDK for Arduino.
You will also need an Arduino board, a [BLE shield] (http://redbearlab.com/bleshield/) or an [nRF8001 Development kit](http://no.mouser.com/nordicsemiconductor), and jumper wires (female-female and male-male).

##Usage

The set up data for nRF8001 is visually created by nRFgo Studio and saved in an XML file. 
Use the run_me_compile_xml_to_nRF8001_setup.bat present in each of the template projects to convert the XML file to a services.h file that is used by the Arduino application.

Before calling any of the BLE library functions you must call lib_aci_init with valid set up parameters. 
The set up parameters are in the services.h.


    lib_aci_init(&aci_state);

      
    Example call:
     
        // services_pipe_type_mapping pipes and type of pipes from services.h / services_lock.h
        aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
          
        // NUMBER_OF_PIPES in the setup created from services.h / services_lock.h
        aci_state.aci_setup_info.number_of_pipes            = NUMBER_OF_PIPES;
          
        // pointer to set up messages from services.h / serivices_lock.h
        aci_state.aci_setup_info.setup_msgs                 = setup_msgs;
          
        // Number of Setup messages from services.h / services_lock.h
        aci_state.aci_setup_info.num_setup_msgs             = NB_SETUP_MESSAGES;

    	//Tell the ACI library, the MCU to nRF8001 pin connections
    	
    	aci_state.aci_pins.board_name = REDBEARLAB_SHIELD_V1_1; //Use BOARD_DEFAULT for other boards; //See board.h
    	aci_state.aci_pins.reqn_pin   = 9;
    	aci_state.aci_pins.rdyn_pin   = 8;
    	aci_state.aci_pins.mosi_pin   = MOSI;
    	aci_state.aci_pins.miso_pin   = MISO;
    	aci_state.aci_pins.sck_pin    = SCK;
    	
    	aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8;
    	  
    	aci_state.aci_pins.reset_pin             = 4;
    	aci_state.aci_pins.active_pin            = UNUSED;
    	aci_state.aci_pins.optional_chip_sel_pin = UNUSED;
    	  
    	aci_state.aci_pins.interface_is_interrupt	  = false;
    	aci_state.aci_pins.interrupt_number			  = UNUSED;
      

      /** nRF8001 is reset here by toggling the RESET line connected to the nRF8001 device.    
        // Pin 4 of Arduino is connected to RESET on the nRF8001 device
       *  and initializes the data structures required to set up the nRF8001 device.
       */
      lib_aci_init(&aci_state);
      
The services_pipe_type_mapping, number_of_pipes, setup_msgs and num_setup_msgs must be set using the services.h or services_lock.h generated 
from the nRFgo Studio. The services.h places the nRF8001 Setup in the RAM (volatile memoery) of the nRF8001 and the services_lock.h
places the nRF8001 Setup in the NVRAM (non-volatile memory) of the nRF8001.
The functions for the BLE library are defined in lib_aci.h. 
Documentation for the functions in the BLE library can be found [here](in_progress).
 
 
##Troubleshooting:
 
 The messages sent and received between the nRF8001 device can be printed on the serial port of the Arduino and monitored using the Serial Monitor in the Arduino IDE.
 Use utility function lib_aci_debug_print to enable printing on the serial port of the Arduino.
