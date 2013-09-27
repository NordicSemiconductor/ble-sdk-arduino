
BLE Library

lib_aci_send_data()

Description

Sends data on a given pipe. This function sends a SendData ACI command with application data to the nRF8001. 


Syntax
    bool lib_aci_send_data(uint8_t pipe, uint8_t *value, uint8_t size)

    
Parameters
    pipe: Pipe number on which the data should be sent
    value: data that is to send 
    size: size of the data to send


Returns
    bool. True when the ACI command is successfully placed in the ACI command queue.


Events generated
    ACI_EVT_DATA_CREDIT is generated when the peer Bluetooth Low Energy device nRF8001 receives the data sent
    ACI_EVT_PIPE_ERROR is generated when the send data command fails
    
    
    The lib_aci_get_event() is used to get the ACI events from the nRF8001.


Example

Aruino UNO example:
    |   lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, uart_buffer, uart_buffer_len);
