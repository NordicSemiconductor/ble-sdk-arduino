####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_broadcast()

###Description
This function starts the nRF8001 radio advertising in broadcast mode. 
This function sends the ACI Broadcast command to the nRF8001 by placing the command in the ACI command queue in the BLE library.
Broadcast data can be received by a peer that is scanning, but the peer cannot connect to a nRF8001 in broadcast mode.

###Syntax
    bool lib_aci_broadcast(const uint16_t timeout, const uint16_t adv_interval);

###Parameters
* timeout: Advertising time in seconds. Advertising will stop when a peer device connects to the nR8001 device or when the run_timeout occurs.
           When the timeout is 0 the advertisting will not stop (infinite timeout). Use a lib_aci_radio_reset() to stop advertising when timeout is set to 0.
           Accepted values: 0 to 16383.
* advertising_interval: Advertising interval (multiple of 0.625 milliseconds). Usually a smaller advertising interval will decrease the time needed for the peer device to connect.
                        Accepted values: 160 to 16384 (which corresponds to an interval from 100 ms to 10.24 s).

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.   
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_connect()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_connect.md "Go to function description")  
[lib_aci_bond()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_bond.md "Go to function description")  
[lib_aci_open_adv_pipes()] link to these.  
[lib_aci_open_adv_pipe()]  
    
