####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_is_pipe_available()

###Description
Use this function to check if a given pipe is available.  
* A TX pipe would be avalable when the peer has enabled it by writing to the Client Characteristic Configuration Descriptor.  
* A remote pipe can be enabled by calling lib_aci_open_remote_pipe().  

###Syntax
bool lib_aci_is_pipe_available(aci_state_t *aci_stat, uint8_t pipe);

###Parameters
* aci_stat: The structure that contains the current pipe available bitmap.
* pipe: Pipe to check

###Returns
    bool. True if the pipe is available, otherwise false.

###Events generated
[ACI_EVT_PIPE_STATUS](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051601 "Go to nRF8001 PS") is sent from the nRF8001 to the external application controller whenever there is a change in service pipe availability status.  

###Related functions
[lib_aci_is_pipe_closed]  
[lib_aci_open_remote_pipe]  
[lib_aci_close_remote_pipe]
