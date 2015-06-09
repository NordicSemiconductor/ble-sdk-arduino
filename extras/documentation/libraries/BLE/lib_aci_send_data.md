####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_send_data()

###Description
Sends data on a given pipe. This function queues a SendData ACI command with application data, in the ACI command queue.


###Syntax
    bool lib_aci_send_data(uint8_t pipe, uint8_t *value, uint8_t size)

    
###Parameters
* pipe: Pipe number on which the data should be sent
* value: data that is to send 
* size: size of the data to send

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_DATA_CREDIT](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1052699 "Go to nRF8001 PS") is generated when the peer Bluetooth Low Energy device nRF8001 receives the data sent  
[ACI_EVT_PIPE_ERROR](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1052798 "Go to nRF8001 PS") is generated when the send data command fails  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001.

###Related functions
setlocaldata  
senddataack  
requestdata  
senddatanack  
