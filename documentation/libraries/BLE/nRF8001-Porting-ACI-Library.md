####[BLE](https://github.com/NordicSemiconductor/ble-sdk-arduino/tree/master/documentation/libraries/BLE "Go to BLE folder")

#Porting the nRF8001 SDK for Arduino (0.9.0) to your chosen microcontroller 

The nRF8001 SDK for Arduino is portable C code that can be easily ported to a different microcontroller. 
A few parts of the SDK however must be re-implemented on the new microcontroller, 
these are the SPI/ACI interface, GPIO interface, delay and optionally the interrupt interface. 
All other code in the SDK can be ported to the new microcontroller.

##Getting the nRF8001 SDK for Arduino ready for porting:

Change the file names and make the required entry points for main() so it is easily portable to C based environments.

Change the .ino file to a .c file.

For example: ble_aci_transport_layer_verification.ino should be renamed to ble_aci_transport_layer_verification.c

Add the below code in the bottom of the .ino file (now a .c file)

    main() 
    {
       setup(); 
       while(1)
       {
         loop();
       }
    }

This code will remove the dependency of the setup() and loop() to the Arduino platform.

The nRF8001 SDK for Arduino contains both the interrupt and polling interfaces to work with the nRF8001.

The required interface is selected using the

aci_state.aci_pins.interface_is_interrupt = false;

Remove the interface from the SDK that will not be used in your target mcu

###Removing the interrupt interface: (Assuming this interface is not used in the target microcontroller)
Remove the function static void m_aci_isr(void) from the hal_aci_tl.cpp

Remove all instances of noInterrupts(); , interrupts(); , attachInterrupt and detachInterrupt.

Remove the below code in hal_aci_tl.cpp in the function 
bool hal_aci_tl_event_get(hal_aci_data_t *p_aci_data)

        if (was_full && a_pins_local_ptr->interface_is_interrupt)
              {
          /* Enable RDY line interrupt again */
          attachInterrupt(a_pins_local_ptr->interrupt_number, m_aci_isr, LOW);
        }

Remove the code below in hal_aci_tl.cpp in the function 
void hal_aci_tl_init(aci_pins_t *a_pins, bool debug)

      /* Attach the interrupt to the RDYN line as requested by the caller */
      if (a_pins->interface_is_interrupt)
      {
        // We use the LOW level of the RDYN line as the atmega328 can wakeup from sleep only on LOW
        attachInterrupt(a_pins->interrupt_number, m_aci_isr, LOW);
      }

Modify the code below in hal_aci_tl.cpp

    bool hal_aci_tl_event_peek(hal_aci_data_t *p_aci_data)
    {
      if (!a_pins_local_ptr->interface_is_interrupt)
      {
        m_aci_event_check();
      }

to

    bool hal_aci_tl_event_peek(hal_aci_data_t *p_aci_data)
    {
      m_aci_event_check();

Modify the code below in hal_aci_tl.cpp from

    bool hal_aci_tl_event_get(hal_aci_data_t *p_aci_data)
    {
      bool was_full;

      if (!a_pins_local_ptr->interface_is_interrupt && !aci_queue_is_full(&aci_rx_q))
      {
        m_aci_event_check();
      }

to

    bool hal_aci_tl_event_get(hal_aci_data_t *p_aci_data)
    {
      bool was_full;

      if (!aci_queue_is_full(&aci_rx_q))
      {
        m_aci_event_check();
      }

####Remove the below functions from aci_queue.cpp

bool aci_queue_dequeue_from_isr(aci_queue_t *aci_q, hal_aci_data_t *p_data)

bool aci_queue_enqueue_from_isr(aci_queue_t *aci_q, hal_aci_data_t *p_data)

bool aci_queue_is_empty_from_isr(aci_queue_t *aci_q)

bool aci_queue_is_full_from_isr(aci_queue_t *aci_q)

bool aci_queue_peek_from_isr(aci_queue_t *aci_q, hal_aci_data_t *p_data)

Now you are ready to port the portable portions of the SDK to the new mcu and re-implement the SPI,  GPIO and delay interfaces

##Re-implement GPIO, SPI and Delay

The GPIO interfaces that are used are digitalRead, digitalWrite and pinMode.

The pinMode supports INPUT, OUTPUT and INPUT_PULLUP options. You need to re-implement these functions. 
You can choose to support the existing function interfaces or use the intefaces as provided in your mcu's toolchain.

The delay() function  takes its parameter in milli seconds.

The nRF8001 is a SPI slave. The SPI for the nRF8001 is LSBit first and uses mode 0. The maximum supported clock for the nRF8001 SPI is 3MHz.

If the SPI in your mcu only supports MSBit you can use the REVERSE_BITS macro hal_aci_tl.cpp to convert the SPI traffic to LSBit.

SPI (nRF8001 signals data is available)

The nRF8001 signals that data is available by lowering the RDYN line.

The mcu must set the REQN line low.

The SPI master on the microcontroller runs the SPI clock for 2 bytes.

The m_aci_spi_transfer() function in hal_aci_tl.cpp then examines the length fields of the data on the SPI from the mcu to nRF8001 and nRF8001 and mcu.

The function will then continue clocking on the SPI for the larger of the length fields.

##Portable C code

The aci_queue functions in aci_queue.cpp are portable to any microcontroller that supports C. 
These functions implement a circular FIFO using indices.

The queue functions implemented are enqueue to add to the tail of the queue, 
dequeue to remove from the head of the queue and peek to peek into the queue.

The functions in the lib_aci.cpp are portable and are implemented in C.

The lib_aci.cpp functions in the Arduino SDK pack the nRF8001 Events and Commands on a byte boundary. 
If your mcu's toolchain does not support the ability to pack the messages on a byte boundary (or is not a 8 bit mcu), 
then use the decode functions in acilib.cpp to modify the lib_aci_event _get() function.

##Testing of the ACI transport

Use the ble_aci_transport_layer_verification project to verify your ACI driver for the nRF8001. 
The nRF8001 provides the ACI Echo command (available in the nRF8001 Test mode), 
to do a loopback test on the ACI interface. This will validate the nRF8001 ACI transport.

The ACI Echo command is sent with data and the nRF8001 responds with an ACI Echo Event which contains the data sent in the Echo command. 
This allows you to verify that the SPI connectivity is ok on the board. 
You can also vary the length of the Echo commands to send short packets followed by long packets 
so that the ability of the SPI to handle packets of different lengths in a duplex SPI connection is confirmed.

