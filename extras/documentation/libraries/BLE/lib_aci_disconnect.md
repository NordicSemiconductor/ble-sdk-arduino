####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_disconnect()

###Description
This function is used to disconnect from the central device.
It will update the pipe available bitmap immediately  when the disconnect command is placed in the command queue.
This is done to stop the application from sending additional  massages to the nRF8001.
If the application sends another massage before the bitmap is updated an ACI_EVT_PIPE_ERROR will be received from the nRF8001.

###Syntax
    bool lib_aci_disconnect(aci_state_t *aci_stat, aci_disconnect_reason_t reason);

###Parameters
* aci_stat: The structure that contains the current pipe available bitmap.  
* reason: Reason for disconnecting:  
  * 0x01 "Remote user terminated connection"  
  * 0x02 "Unacceptable connection timing"  

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.  
[ACI_EVT_DISCONNECTED](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1051284 "Go to nRF8001 PS") indicates the loss of a connection.  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_connect()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_connect.md "Go to function description")  
[lib_aci_bond()](https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/documentation/libraries/BLE/lib_aci_bond.md "Go to function description")  
