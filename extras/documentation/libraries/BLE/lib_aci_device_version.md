####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#lib_aci_device_version()

###Description
This function is used to get the nRF8001 version and configuration information.
It will result in a CommandResponseEvent containing the Configuration ID, ACI protocol version and Setup ID for the chip.

###Syntax
    bool lib_aci_device_version(void);

###Parameters
    none

###Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated
[ACI_EVT_CMD_RSP](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1050945 "Go to nRF8001 PS") with [Response data](https://devzone.nordicsemi.com/documentation/ps/nRF8001_PS_v1.2.pdf#G1048410 "Go to nRF8001 PS") is generated when the nRF8001 device receives the command.  
  
The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.

###Related functions
