
####BLE Library####

#lib_aci_bond()#

###Description###
This library starts the nRF8001 radio advertising in bond mode. This function sends the ACI Bond command to the nRF8001 by placing the command in the ACI command queue in the BLE library.
Bond data can be received by a peer that is scanning. Bond starts advertising with the intent of setting up a trusted relationship with a peer device

###Syntax###
    bool lib_aci_bond(uint16_t run_timeout, uint16_t adv_interval);

###Parameters###
    run_timeout: Advertising time in seconds. Advertising will stop when a peer device connects to the nR8001 device or when the run_timeout occurs.
                 Use a lib_aci_radio_reset() to stop advertising before the advertisment times out.
                 Accepted values: 1 to 180.
    advertising_interval: Advertising interval (multiple of 0.625 milliseconds). Usually a smaller advertising interval will decrease the time needed for the peer device to connect.
                          Accepted values: 160 to 16384 (which corresponds to an interval from 100 ms to 10.24 s).

###Returns###
    bool. True when the ACI command is successfully placed in the ACI command queue.

###Events generated###
    ACI_EVT_CMD_RSP is generated when the nRF8001 device receives the command.
    ACI_EVT_CONNECTED is generated when a peer device connects to the nRF8001
    ACI_EVT_BOND_STATUS with [Returned values](https://devzone.nordicsemi.com/nrf8001_ps_v1.2.pdf#G1051505 "Go to nRF8001 PS") and [Bond status codes](https://devzone.nordicsemi.com/nrf8001_ps_v1.2.pdf#G1053311 "Go to nRF8001 PS")
    ACI_EVT_DISCONNECTED is generated in case of a failed bonding procedure, [Returned values](https://devzone.nordicsemi.com/nrf8001_ps_v1.2.pdf#G1051356 "Go to nRF8001 PS")

    The lib_aci_get_event() is used to get the ACI events from the nRF8001 device.
