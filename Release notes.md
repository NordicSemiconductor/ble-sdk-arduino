#Release notes 0.9.1:

##Changes:
* Added DFU example. Note that a new bootloader is needed for this project

* Added porting document

##Fixes:
* Fixed an issue with lib_aci_close_remote_pipe

##Known issues:
1. Assert functionality has been removed and should be put back to the SDK.
Currently the asserts have been replaced with while(1)

4. The FIFO/Queue uses the "one slot" free method to detect empty and full conditions.
This wastes one extra element in the queue.
The algorithm can be optimized to reduce RAM usage.

5. Bonding info is stored in non-volatile memory on the Arduino after an ACI Timing Event and the Timing Event may not always arrive.
This issue is applicable for all projects that use pairing.

6. Documentation for using the Nordic adapter shield for nRF8001 with the nRF8001 Development kit and the Bluetooth low energy SDK for Arduino is incomplete.

7. Documentation for the Bluetooth low energy SDK for Arduino is still in progress.

9. Sending zero byte value from the hello world example causes nRF UART on iOS to crash.

10. Bootloader for DFU is not yet released, but it will be shortly.

#Release notes 0.9.0:

##Changes:
* Changed the interface for lib_aci_init() to include the lib_aci_debug_print() interface.

* Removed the lib_aci_debug_print()

* Changed interface for do_aci_setup()

* Created separate queue module

* Turned off debug serial output as default.

* Added platform specific code for Chipkit to some examples.

##Fixes:
* Added API for assert handling.

* Added defines for platform specific code to improve portability for ChipKIT

* ACI_QUEUE_SIZE is set to 4 as default.

* The code works with the Leonardo, 
  Note that the Leonardo is not reset when you start the serial monitor,
  so a delay is needed if you want to be able to see the output of the initial prints using Serial

* Rewrote nRF8001 Setup procedure, do_aci_setup().

* Fixed interrupt handling so the SDK works both for polling and interrupts

##Known issues:
1. Assert functionality has been removed and should be put back to the SDK.
Currently the asserts have been replaced with while(1)

4. The FIFO/Queue uses the "one slot" free method to detect empty and full conditions.
This wastes one extra element in the queue.
The algorithm can be optimized to reduce RAM usage.

5. Bonding info is stored in non-volatile memory on the Arduino after an ACI Timing Event and the Timing Event may not always arrive.
This issue is applicable for all projects that use pairing.

6. Documentation for using the Nordic adapter shield for nRF8001 with the nRF8001 Development kit and the Bluetooth low energy SDK for Arduino is incomplete.

7. Documentation for the Bluetooth low energy SDK for Arduino is still in progress.

9. Sending zero byte value from the hello world example causes nRF UART on iOS to crash.

#Release notes 0.8.1:

##Fixes:

1. Added documentation for ble_A_Hello_World_Program

2. Changed default PIN configuration for all examples

3. Minor changed to ble_A_Hello_World_Program and ble_urat_project_Template

4. Minor documentation changes 


#Release notes 0.8.0:

##Known issues:

1. Assert functionality has been removed and should be put back to the SDK.
Currently the asserts have been replaced with while(1)

2. Platform specific code to be placed in a #define to improve portability.
E.g. EIMSK. pgmspace etc.

3. The BLE module, when using interrupts, may have issues that could stop the libray from working when the FIFO/Queue becomes full.
Ensure that the queue size is at least 4 when using interrupts.
This is specified in hal_aci_tl.h 
'#define ACI_QUEUE_SIZE  4'. 
The BLE module does not have any known issues when polling.

4. The FIFO/Queue uses the "one slot" free method to detect empty and full conditions.
This wastes one extra element in the queue.
The algorithm can be optimized to reduce RAM usage.

5. Bonding info is stored in non-volatile memory on the Arduino after an ACI Timing Event and the Timing Event may not always arrive.
This issue is applicable for all projects that use pairing.

6. Documentation for using the Nordic adapter shield for nRF8001 with the nRF8001 Development kit and the Bluetooth low energy SDK for Arduino is incomplete.

7. Documentation for the Bluetooth low energy SDK for Arduino is still in progress.

8. Tested with Arduino Uno. There seems to be some issues with the Arduino Leonardo that needs to be investigated.
