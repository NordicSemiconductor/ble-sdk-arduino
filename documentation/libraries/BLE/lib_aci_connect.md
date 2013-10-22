####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_connect()

###Description
This function starts the nRF8001 radio advertising in connectable mode.
This function sends the ACI Connect command to the nRF8001 by placing the command in the ACI command queue in the BLE library.
A peer device can connect to the nRF8001 device during advertising in connectable mode.

###Syntax
    bool lib_aci_connect(uint16_t run_timeout, uint16_t adv_interval)

###Parameters
* run_timeout: Advertising time in seconds. Advertising will stop when a peer device connects to the nR8001 device or when the run_timeout occurs.
               When the run_timeout is 0 the advertisting will not stop (infinite timeout). Use a lib_aci_radio_reset() to stop advertising when run_timeout is set to 0.
               Accepted values: 0 to 16383.
* advertising_interval: Advertising interval (multiple of 0.625 milliseconds). Usually a smaller advertising interval will decrease the time needed for the peer device to connect.
                        Accepted values: 160 to 16384 (which corresponds to an interval from 100 ms to 10.24 s).

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.  
[ACI_EVT_CONNECTED](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051073 "Go to nRF8001 PS") is generated when a peer device connects to the nRF8001.  
[ACI_EVT_DISCONNECTED](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051284 "Go to nRF8001 PS") with aci_status ACI_STATUS_ERROR_ADVT_TIMEOUT is generated when no peer device connects to the nRF8001 device.  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_bond()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_bond.md "Go to function description")  
[lib_aci_open_adv_pipes()] link to these.  
[lib_aci_open_adv_pipe()]  
[lib_aci_open_remote_pipe()]  
[lib_aci_close_remote_pipe()] 
