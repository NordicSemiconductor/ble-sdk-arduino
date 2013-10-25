####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_read_dynamic_data()

###Description
The dynamic data will contain bonding addresses and keys, which would normally be lost after reseting the chip.
By writing the dynamic data back into the nRf8001 it is possible to re-establish a bond after a power failure or reset.
If you have enabled security on your device, it is recommended that the dynamic data is read from the chip and stored in Non-volatile memory by the application controller.  
  
This function is used to read the dynamic data from the nRF8001 by placing a ReadDynamicData command in the ACI command queue in the BLE library.
The nRf8001 will respond with a command response event containing a status code and response data (the dynamic data, 1..26 bytes).
The application is expected to call this function untill it receives a Command response with a ACI_STATUS_TRANSACTION_COMPLETE status code.
Note that this command response will contain the last part of the dynamic data.
The Command response event will have the status code ACI_STATUS_TRANSACTION_CONTINUE as long as there is dynamic data to be read from the nRF8001.  

###Syntax
    bool lib_aci_read_dynamic_data(void);

###Parameters
    none

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.   
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_write_dynamic_data()]  
[lib_aci_bond()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_bond.md "Go to function description")  
[lib_aci_open_adv_pipes()] link to these.  
[lib_aci_open_adv_pipe()]  
