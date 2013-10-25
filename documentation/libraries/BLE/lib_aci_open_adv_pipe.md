####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_open_adv_pipe()

###Description
This function sends a command to the radio to set the input pipe to be placed in Advertisement Service Data.

This function sends a command to the radio that places the pipe in advertisement service data.
To start advertising service data, call this function before Connecting, Broadcasting or Bonding to peer.
The data that should be sent in the advertisement packets must be set using the lib_aci_set_local_data function.
This function can be called during advertising to enable/disable broadcast pipes.  

###Syntax
    bool lib_aci_open_adv_pipe(const uint8_t pipe);

###Parameters
* pipe The pipe that has to be placed in advertising service data.

###Returns
    True if the Open Adv Pipe message is sent successfully to the radio.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.   
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.


###Related functions
[lib_aci_open_adv_pipes()] link to these.
