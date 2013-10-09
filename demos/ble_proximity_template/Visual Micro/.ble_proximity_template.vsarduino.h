/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Uno, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328P__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

aci_status_code_t bond_data_restore(aci_state_t *aci_stat, uint8_t eeprom_status, bool *bonded_first_time_state);
void bond_data_store(aci_evt_t *evt);
bool bond_data_read_store(aci_state_t *aci_stat);
void aci_loop();
void alert_level_print(alert_level_t level);
void immediate_alert_hook(alert_level_t level);
void link_loss_alert_hook(alert_level_t level);
void setup(void);
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\ble_proximity_template.ino"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\aci.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\aci_cmds.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\aci_evts.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\alert_level_characteristic.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\immediate_alert.cpp"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\immediate_alert.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\lib_aci.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\link_loss.cpp"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\link_loss.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\services.h"
#include "C:\Users\rusk\Documents\GitHub\ble-sdk-arduino-fork\demos\ble_proximity_template\services_lock.h"
