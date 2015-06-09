####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_bond()

###Description
This function starts the nRF8001 radio advertising in bond mode. 
This function sends the ACI Bond command to the nRF8001 by placing the command in the ACI command queue in the BLE library.
Bond data can be received by a peer that is scanning. Bond starts advertising with the intent of setting up a trusted relationship with a peer device  
  
* lib_aci_bond is for providing encryption and security on the link by allowing encryption keys to be shared.  
* lib aci connect is used after a bond status of success is received to use the encryption keys on the link.  
  
Using a lib aci bond after a bond status success will delete the previous bond information.

###Syntax
    bool lib_aci_bond(uint16_t run_timeout, uint16_t adv_interval);

###Parameters
* run_timeout: Advertising time in seconds. Advertising will stop when a peer device connects to the nR8001 device or when the run_timeout occurs.
               Use a lib_aci_radio_reset() to stop advertising before the advertisment times out.
               Accepted values: 1 to 180.
* advertising_interval: Advertising interval (multiple of 0.625 milliseconds). Usually a smaller advertising interval will decrease the time needed for the peer device to connect.
                        Accepted values: 160 to 16384 (which corresponds to an interval from 100 ms to 10.24 s).

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.  
[ACI_EVT_CONNECTED](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051073 "Go to nRF8001 PS") is generated when a peer device connects to the nRF8001.  
[ACI_EVT_BOND_STATUS](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051403 "Go to nRF8001 PS") with [Bond status codes](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1053311 "Go to nRF8001 PS") is generated after the bondig procedure is executed.  
[ACI_EVT_DISCONNECTED](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051284 "Go to nRF8001 PS") is generated in case of a failed bonding procedure.  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_connect()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_connect.md "Go to function description")  
[lib_aci_open_adv_pipes()] link to these.  
[lib_aci_open_adv_pipe()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_open_adv_pipe.md "Go to function description")  
[lib_aci_bond_request()]  
[lib_aci_open_remote_pipe()]  
[lib_aci_close_remote_pipe()]  
