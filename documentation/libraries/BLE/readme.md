#BLE Library

This library enables communication between Nordic Semiconductor's nRF8001 <em>Bluetooth</em>&#174; low energy (BLE) chip and an Arduino board. The functionality of the library is based on the ACI commands and Events of nRF8001 as described in the nRF8001 Product Specification(http://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF8001) .
All Arduino boards have a SPI master interface with SS, MISO, MOSI, and SCK. The board communicates with nRF8001 through SS, MISO, MOSI, SCK, Pin 3, and Pin 4. SS is connected to the REQN of the nRF8001 device. Pin 3 is connected to the RDYN of the nRF8001 device and Pin 4 is connected to the RESET of the nRF8001 device. MISO, MOSI, and SCK are connected to MOSI, MISO, and SCK of the nRF8001 device. The RDYN line of the nRF8001 device is an interrupt from nRF8001, when nRF8001 has information for the Arduino.

If you use this library you cannot use Pins 3, 4 and 10 for digital input or output. Pins 11, 12, 13 can be shared with other SPI slave devices. The Arduino can use only one of the SPI slave devices at any given time. The Arduino should select the slave device by using the SS line of the slave device. The SS line of the nRF8001 device is the REQN line.

##Set up

You can download a copy of the BLE library and example applications from [here](http://developer.bluetooth.org/Forum/Pages/Forum.aspx?action=ViewTopics&fid=6)
You will also need an Arduino UNO, a [BLE shield from RedBearlab] (http://redbearlab.com/bleshield/) or an [nRF8001 Development kit](http://no.mouser.com/nordicsemiconductor), and jumper wires (female-female and male-male).

##Usage

The set up data for nRF8001 is visually created by nRFgo Studio and saved in an XML file. Use the run_me_compile_xml_to_nRF8001_setup.bat present in each of the template projects to convert the XML file to a services.h file that is used by the Arduino application.

Before calling any of the BLE library functions you must call lib_aci_init with valid set up parameters. The set up parameters are in the services.h.


    |  lib_aci_init(&aci_state);

      
    Example call:
      
      aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0]; // services_pipe_type_mapping pipes and type of pipes from services.h
      aci_state.aci_setup_info.number_of_pipes            = NUMBER_OF_PIPES;                // NUMBER_OF_PIPES in the setup created from services.h
      aci_state.aci_setup_info.setup_msgs                 = setup_msgs;                     // pointer to set up messages from services.h
      aci_state.aci_setup_info.num_setup_msgs             = NB_SETUP_MESSAGES;              // Number of Setup messages from services.h

      /** nRF8001 is reset here by toggling the RESET line connected to the nRF8001 device.    // Pin 4 of Arduino is connected to RESET on the nRF8001 device
       *  and initializes the data structures required to set up the nRF8001 device.
       */
      lib_aci_init(&aci_state);
      
The services_pipe_type_mapping, number_of_pipes, setup_msgs and num_setup_msgs must be set using the services.h generated from the XML file.
The functions for the BLE library is defined in lib_aci.h . Documentation for the functions in the BLE library can be found [here](in_progress).
 
 
##Troubleshooting:
 
 The messages sent and received between the nRF8001 device can be printed on the serial port of the Arduino and monitored using the Serial Monitor in the Arduino IDE.
 Use utility function <<To be done>> to enable printing on the serial port.
