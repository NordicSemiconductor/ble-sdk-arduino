####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_set_local_data()

###Description
Updates data on a pipe. This function sends a SetLocalData ACI command with application data to the nRF8001. 
This command can be used on "Set" Pipes. Use the nRFgo studio - nRF8001 configuration to add a "Set Pipe" to any Bluetooth Characteristic. 

###Syntax
    bool lib_aci_set_local_data(aci_state_t *aci_stat, uint8_t pipe, uint8_t *value, uint8_t size)

    
###Parameters
* aci_stat: Structure containg the ACI state information
* pipe: Pipe number on which should be updated
* value: data that is to send 
* size: size of the data to send


###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.


###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.
See the command status in the Command Response Event to verify that the command was successfully executed  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001.

###Related functions
senddata  
senddataack  
requestdata  
senddatanack  
