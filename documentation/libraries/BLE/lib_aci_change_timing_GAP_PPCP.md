####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_change_timing_GAP_PPCP()

###Description
This function is used to initiate a connection parameters update procedure using the connection parameters configured in nRFgo studio.
The update procedure is started by sending a Connection parameter  update request to the Central.  
* If the master rejects or accepts but doesn't change the connection parameters within 30 seconds, a timing event with the unchanged connection parameters is generated.  
* If the request is accepted and the master changes connection parameters, a timing event with the new connection parameters is generated.  
* If the master doesn't reply to the request within 60 seconds, the radio disconnects.  

###Syntax
    bool lib_aci_change_timing_GAP_PPCP(void);

###Parameters
    none

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.   
[ACI_EVT_TIMING](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1052567 "Go to nRF8001 PS") will return the current connection timing information when the parameters have changed.  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
[lib_aci_change_timing]()
